import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)  
GPIO.setup(3, GPIO.OUT)
        GPIO.output(3, True)  # Turn on
        time.sleep(1)
        GPIO.output(3, False)  # Turn off
        time.sleep(1)

