from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont

from lib_tft24T import TFT24T
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

import spidev
from time import sleep

#For LCD SCREEN:
DC = 18
RST = 23

# Create TFT LCD/TOUCH object:
TFT = TFT24T(spidev.SpiDev(), GPIO, landscape=False)

# Initialize display.
TFT.initLCD(DC, RST)
# If rst is omitted then tie rst pin to +3.3V
# If led is omitted then tie led pin to +3.3V

# Get the PIL Draw object to start drawing on the display buffer.
draw = TFT.draw()

while 1:
    TFT.clear((255, 0, 0))
    # Alternatively can clear to a black screen by simply calling:
    TFT.clear()
    print('Loading image...')
    image = Image.open('cat.jpg')
    # Resize the image and rotate it so it's 240x320 pixels.
    image = image.rotate(90,0,1).resize((240, 320))
    # Draw the image on the display hardware.
    print('Drawing image')
    TFT.display(image)
    sleep(3)
    print ("Test a long para of text, auto-wrapped into screen lines.")
    TFT.clear()
    font=ImageFont.truetype('FreeSans.ttf', 18)
    text1 = """Lorem ipsum dolor sit amet, consectetur adipiscing elit. In quis justo quis tortor pellentesque malesuada. Donec eleifend lorem vel blandit condimentum. Vivamus risus sapien, iaculis id dictum ut, porta quis. """
    draw.textwrapped((0,0), text1, 38, 20, font, "lightblue")
    TFT.display()
    sleep(1)

    TFT.clear((90,90,255))
    print ("show a font in giant letters")
    font = ImageFont.truetype('FreeSerifItalic.ttf', 40)
    draw.textrotated((100,10), 'TEST DERP',90 ,font=font, fill="RED")

    TFT.display()
    sleep(2)