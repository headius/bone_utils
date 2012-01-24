class LED
  def initialize(index)
    @led = File.open("/sys/devices/platform/leds-gpio/leds/beaglebone::usr#{index}/brightness", 'w')
  end

  def on(length)
    @led.syswrite '1'
    sleep length
  end

  def off(length)
    @led.syswrite '0'
    sleep length
  end
end

class TextLED
  def on(length)
    puts '*' * (length * 40000)
    sleep length
  end

  def off(length)
    sleep length
  end
end

class SineBlinker
  def initialize(period, resolution, led)
    @period = period
    @resolution = resolution
    @led = led
  end

  def run
    loop do
      @led.off(@resolution)
      
      # calculate on time based on sin(current % PERIOD / PERIOD * 2pi)
      cur_sec = Time.now.to_f % @period
      radians = cur_sec / @period * 2 * Math::PI
      sin = Math.sin(radians)
      on_time = (sin + 1) * @resolution / 10.0
      
      @led.on(on_time)
    end
  end
end

#SineBlinker.new(2, 0.01, LED.new(3)).run
SineBlinker.new(2, 0.01, TextLED.new).run
