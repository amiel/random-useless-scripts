require 'monitor'

shared_data = Array.new
shared_data.extend MonitorMixin
a_cond = shared_data.new_cond

puts "a_cond waiters = #{a_cond.count_waiters}"


Thread.start do
  loop do
    shared_data.synchronize do
      puts 'before cond'
      a_cond.wait
      puts 'after cond'
      sleep 1
    end
  end
end


sleep 2
shared_data.synchronize do
  puts "a_cond waiters = #{a_cond.count_waiters}"
  a_cond.signal
  a_cond.signal
end

sleep 20