#!/usr/bin/ruby

require 'rubygems'
require 'gd2'
require 'periodical_runner'
require 'image_finder'
include Every

require 'benchmark'

require 'yaml'

THUMB_SIZE = 75


class Fixnum
  def to_two_digit_hex
    s = self.to_s(16)
    if s.length != 2
      s = '0' + s
      s = s[-2,2]
    end
    s
  end
end

def rgb_value(color)
  color.r.to_two_digit_hex + color.g.to_two_digit_hex + color.b.to_two_digit_hex
end


file = ARGV[0] || gets
name = File.basename file, '.*'

Dir.mkdir(name) unless File.directory?(name)

src_image = GD2::Image.import(file)
src_image.export(name + '/original.jpg')
src_image = src_image.to_indexed_color(256)

src_image.export(name + '/indexed_to_256.jpg')

color_database = name + '/image_database.marshal'

if File.exists?(color_database)
  colors = Marshal.load File.read(color_database)
else
  colors = Hash.new

  (0...src_image.height).each do |y|
    (0...src_image.width).each do |x|
      colors[rgb_value(src_image[x, y])] = nil
    end
  end

  puts "Found #{colors.size} distinct colors"


  fetch_times = Array.new


  PeriodicalRunner.new('2') do
    key = colors.find{ |k,v| v.nil? }
    break if key.nil?
    key = key.first
    puts "finding images for: #{key}"
    b = Benchmark.measure {
      colors[key] = ImageFinder.new(key)
    }
  
    fetch_times << b.real
    every 10 do
      average_time = fetch_times.inject{|sum,e| sum+e} / fetch_times.size
      puts "each request is taking #{average_time} seconds"
      reqs_left = colors.size - @i
      puts "this is #{@i} out of #{colors.size} so there are #{reqs_left} requests left to do"
      time_left = reqs_left * average_time
      puts "estimated time left: #{time_left} seconds or #{time_left / 60} minutes"
      fetch_times = Array.new if @i % 1000 == 0
    end
  end

  File.open(color_database, 'wb') { |file|
    file.write(Marshal.dump(colors))
  }
  
end

poster = GD2::Image.new(src_image.width*THUMB_SIZE, src_image.height*THUMB_SIZE)

fetch_times = Array.new
@i = 0

(0...src_image.height).each do |y|
  (0...src_image.width).each do |x|
    # this should now be the image
    print "getting an image for [#{x}, #{y}]: #{rgb_value(src_image[x, y])}: "
    
    b = Benchmark.measure do
      begin
        file = colors[rgb_value(src_image[x, y])].random_image
        puts file
        next if file.nil?
        i = GD2::Image.import(file)
      rescue GD2::LibraryError => e
        retry
      end
      # i.draw do |pen|
      #   pen.color = src_image[x,y]
      #   pen.fill
      # end
    
      poster.copy_from(i, x * THUMB_SIZE, y * THUMB_SIZE, 0, 0, THUMB_SIZE, THUMB_SIZE)
    end
    
  
    fetch_times << b.real
    every 10 do
      average_time = fetch_times.inject{|sum,e| sum+e} / fetch_times.size
      puts "each request is taking #{average_time} seconds"
      reqs_left = src_image.height * src_image.width - @i
      puts "this is #{@i} out of #{src_image.height * src_image.width} (#{(@i/(src_image.height * src_image.width).to_f * 100).to_i}%) so there are #{reqs_left} requests left to do"
      time_left = reqs_left * average_time
      puts "estimated time left: #{time_left.to_i} seconds or #{(time_left / 60).to_i} minutes"
      fetch_times = Array.new if @i % 1000 == 0
    end
  end
end

puts "done: writing to file #{name}/finished.jpg"
poster.export(name + '/finished.jpg')