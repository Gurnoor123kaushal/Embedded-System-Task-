import RPi.GPIO as GPIO
from tkinter import Tk, Scale, HORIZONTAL
from time import sleep

# GPIO setup
GPIO.setmode(GPIO.BCM)
red_pin = 17  # Choose the GPIO pins for the LEDs
green_pin = 27
blue_pin = 22
GPIO.setup(red_pin, GPIO.OUT)
GPIO.setup(green_pin, GPIO.OUT)
GPIO.setup(blue_pin, GPIO.OUT)

# PWM setup
red_pwm = GPIO.PWM(red_pin, 100)  # PWM frequency of 100Hz
green_pwm = GPIO.PWM(green_pin, 100)
blue_pwm = GPIO.PWM(blue_pin, 100)
red_pwm.start(0)
green_pwm.start(0)
blue_pwm.start(0)

# Function to adjust PWM duty cycle based on slider value
def set_red_intensity(val):
    red_pwm.ChangeDutyCycle(int(val))

def set_green_intensity(val):
    green_pwm.ChangeDutyCycle(int(val))

def set_blue_intensity(val):
    blue_pwm.ChangeDutyCycle(int(val))

# Tkinter GUI
root = Tk()
root.title("LED Intensity Control")

# Sliders for each LED color
red_slider = Scale(root, from_=0, to=100, orient=HORIZONTAL, label="Red Intensity", command=set_red_intensity)
red_slider.pack()

green_slider = Scale(root, from_=0, to=100, orient=HORIZONTAL, label="Green Intensity", command=set_green_intensity)
green_slider.pack()

blue_slider = Scale(root, from_=0, to=100, orient=HORIZONTAL, label="Blue Intensity", command=set_blue_intensity)
blue_slider.pack()

root.mainloop()

# Cleanup
GPIO.cleanup()
