require 'singleton'
require 'monitor'


class Room
  def initialize(type, group_size)
    self.extend(MonitorMixin)
    
    @type = type
    @group_size = group_size
    
    @register = self.new_cond
    @wait_for_last_member = self.new_cond
    @entrance = :open
    @exit_door = :closed
    @waiting = 0
  end
  
  attr_reader :type
  
  def register
    synchronize do
      @register.wait_until { @entrance == :open }
      @waiting += 1
      if @waiting < @group_size
        wait_for_last_member
      else
        @waiting -= 1
        @entrance = :closed
        @exit_door = :open
        @wait_for_last_member.broadcast
      end
    end
  end
  
  def open_door
    synchronize do
      @entrance = :open
      @register.broadcast
    end
  end
  
  private
  def wait_for_last_member
    synchronize do
      @wait_for_last_member.wait_until { @exit_door == :open }
      @waiting -= 1
      if @waiting == 0
        @exit_door = :closed
        puts "WAKE SANTA, we got enough of us"
        Santa.wake self
      end
    end
  end
end

class Santa
  include Singleton
  
  def initialize
    self.extend MonitorMixin
    @groups = {}
  end
  
  class << self
    def register_group(group)
      instance.register_group(group)
    end

    def wake(group)
      instance.wake group
    end
  end
  
  def register_group(group)
    @groups[group.type] = {}
    @groups[group.type][:cond] = self.new_cond
    @groups[group.type][:group] = group
  end
  
  def wake(group)
    synchronize do
      case group.type
      when :reindeer
        @groups[group.type][:group].each do |r|
          
        end
      when :elf
      end
    end
  end
end

class Group < Array
  attr_accessor :type
  def initialize(type, size, &blk)
    @type = type
    super(size, &blk)
  end
end

def on_vacation
  sleep rand(10)
end

if __FILE__ == $0
  N_REINDEER = 9
  N_ELVES = 10
  ELF_GROUP_SIZE = 3
  
  reindeer_room = Room.new :reindeer, N_REINDEER
  elf_room = Room.new :elf, ELF_GROUP_SIZE
  
  reindeer = Group.new :reindeer, N_REINDEER do
    Thread.start do
      loop do
        on_vacation
        reindeer_room.register
        puts "YAY, I'm a reindeer, and got through to santa"
      end
    end
  end
  
  # elves = Group.new :elf, N_ELVES
  
  reindeer.each do |r|
    r.join
  end
  
  
end