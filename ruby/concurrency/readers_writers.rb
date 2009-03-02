require 'monitor'

class ReadersWriters
  attr_accessor :writing, :readers, :shared_data, :oktoread, :oktowrite
  
  def initialize(data)
    @writing = false
    @readers = 0
    

    @shared_data = data
    @shared_data.extend(MonitorMixin)
    @oktoread = @shared_data.new_cond
    @oktowrite = @shared_data.new_cond
    
  end
  
  
  class Reader
    def initialize(shared)
      @shared = shared
    end
    
    def read
      startread
        print "read ->\n\t"
        sleep(rand/2)
        yield @shared.shared_data.dup
        print "read <-\n"
      endread
    end

    def startread
      @shared.shared_data.synchronize do
        if @shared.writing or @shared.oktowrite.count_waiters > 0
          @shared.oktoread.wait
        end
        @shared.readers += 1
        @shared.oktoread.signal
      end
    end
    
    def endread
      @shared.shared_data.synchronize do
        @shared.readers -= 1
        if @shared.readers == 0
          @shared.oktowrite.signal
        end
      end
    end

  end
  
  class Writer
    def initialize(shared)
      @shared = shared
    end
    
    def write
      startwrite
        puts "write ->"
        sleep(rand*5)
        yield @shared.shared_data
        puts "write <-"
      endwrite
    end
    
    def startwrite
      @shared.shared_data.synchronize do
        @shared.oktowrite.wait if @shared.readers > 0 or @shared.writing
        @shared.writing = true
      end
    end

    def endwrite
      @shared.shared_data.synchronize do
        @shared.writing = false
        if @shared.oktoread.count_waiters > 0
          @shared.oktoread.signal
        else
          @shared.oktowrite.signal
        end
      end
      
    end
  end
end


if $0 == __FILE__
  shared_data_and_stuff = ReadersWriters.new []

        
        # start 5 reader threads to read forever
        reader_threads = Array.new(5).collect do
          Thread.start do
            begin
              reader = ReadersWriters::Reader.new shared_data_and_stuff
              loop do
                sleep(rand*2)
                reader.read {|e| p e }
              end
            rescue Exception => e
              puts "#{e.class}: #{e.message}"
              puts e.backtrace.first
            end
          end
        end
        
        # start three writer threads to write 10 times each
        writer_threads = Array.new(3).collect do
          Thread.start do
            begin
              writer = ReadersWriters::Writer.new shared_data_and_stuff
              10.times do
                sleep(rand*4)
                writer.write {|e| e << rand(10) }
              end
            rescue Exception => e
              puts "#{e.class}: #{e.message}\n"
              puts e.backtrace.first
            end
          end
        end
          
        # report on threads and condition variables every 10 seconds 
        Thread.start do
          loop do
            sleep 10
            puts "reader threads: #{reader_threads.inspect}"
            puts "writer threads: #{writer_threads.inspect}"
            puts "oktoread  cond: #{shared_data_and_stuff.oktoread.inspect}"
            puts "oktowrite cond: #{shared_data_and_stuff.oktowrite.inspect}"
          end
        end
        
  # quit everything after all the writer threads are done
  writer_threads.each do |t|
    t.join
  end
end