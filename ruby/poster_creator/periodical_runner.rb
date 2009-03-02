
class Time
  def to_nice_s
    strftime '%a %b %d %I:%M%p'
  end
end

module Every
  def every(amount)
    @i ||=0
    yield @i if @i % amount == 0
    @i += 1
  end
end


class PeriodicalRunner
  include Every
  
  def random_sleeper(time)
    # s = 10 * rand(12)
    case time
    when Proc
      s = time.call
    when String
      s = eval time
    else
      s = time
    end
    s.downto(0) do |i|
      print "  #{i} of #{s}, waiting...\r"
      $stdout.flush
      sleep 0.1
    end
  end



  def print_header
    every 10 do |i|
      puts "#{'*'*11} #{Time.now.to_nice_s} :: attempt ##{i} #{'*'*11}"
    end
  end
  
  
  
  def initialize(time)
    while true
      print_header
      yield if block_given?
      random_sleeper time
    end
  rescue Interrupt
    puts
    puts 'interupted'
  end

end