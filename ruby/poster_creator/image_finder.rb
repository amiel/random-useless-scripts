require 'net/http'
require 'json'

    # http://labs.ideeinc.com/multicolr/#colors=d73224
    # http://labs.ideeinc.com/coloursearch/services/rest/?method=color.search&quantity=20&page=0&colors=d73224&imageset=flickr

class ImageFinder
  
  MULTICOLR_URL = 'http://labs.ideeinc.com/coloursearch/services/rest/?method=color.search&quantity=50&page=0&colors=%s&imageset=flickr'
  
  def initialize(rgb)
    uri_str = MULTICOLR_URL % rgb
    res = Net::HTTP.get_response(URI.parse(uri_str))
    @obj = JSON.load res.body
    
    @@already_used ||= Hash.new
  end
  
  def random_image
    @@already_used ||= Hash.new
    
    return nil if @obj['result'].nil?
    50.times do
      rand_image = @obj['result'][rand(@obj['result'].size)]
      @url = rand_image[1]
      if @@already_used[@url]
        # continue
      else
        @@already_used[@url] = true
        break
      end
    end
    
    uri = URI.parse(@url)
    filename = "tiles/#{File.basename uri.path}"
    
    
    unless File.exists?(filename)
      res = Net::HTTP.get_response(uri)
      File.open(filename, "wb") { |file|
        file.write(res.body)
      }
    end
    filename
  end
end