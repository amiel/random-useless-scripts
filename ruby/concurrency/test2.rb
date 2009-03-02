require 'monitor'


class Room
  
  def initialize
    self.extend MonitorMixin
    
    @register = self.new_cond
    @wait_for_last_member = self.new_cond
    @entrance = :open
    @exit_door = :closed
    @waiting = 0
  end
  
  
  def synched_func
    synchronize do
      call_another_function_that_also_does_synchronize
    end
  end
  
  def call_another_function_that_also_does_synchronize
    synchronize do
      puts 'blah'
    end
  end
  
end