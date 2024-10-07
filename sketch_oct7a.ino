import speech_recognition as sr
import RPi.GPIO as GPIO

# Set up the GPIO pin for the light
LED_PIN = 17  # Change to the GPIO pin connected to your light
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, GPIO.LOW)  # Turn off light initially

# Function to recognize speech and control the light
def voice_control():
    recognizer = sr.Recognizer()
    microphone = sr.Microphone()
    
    with microphone as source:
        print("Adjusting for ambient noise, please wait...")
        recognizer.adjust_for_ambient_noise(source, duration=1)
        print("Listening for command...")
        audio = recognizer.listen(source)
    
    try:
        command = recognizer.recognize_google(audio).lower()
        print(f"You said: {command}")
        
        if "turn on the light" in command:
            GPIO.output(LED_PIN, GPIO.HIGH)
            print("Light turned ON")
        
        elif "turn off the light" in command:
            GPIO.output(LED_PIN, GPIO.LOW)
            print("Light turned OFF")
        
        else:
            print("Unrecognized command. Please try again.")
    
    except sr.UnknownValueError:
        print("Sorry, I could not understand the audio.")
    except sr.RequestError:
        print("Could not request results from Google Speech Recognition service.")

# Main function to execute the voice command control
if __name__ == "__main__":
    try:
        while True:
            voice_control()
    except KeyboardInterrupt:
        print("Program terminated.")
    finally:
        GPIO.cleanup()
