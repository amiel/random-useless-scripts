#why do this, because its cool
class Symbol
  def to_proc
    Proc.new { |*args| args.shift.__send__(self, *args) }
  end
end

class Array
  def to_i
    collect &:to_i
  end
  def a_uniq
    sort.to_i.uniq - [0]
  end
end
