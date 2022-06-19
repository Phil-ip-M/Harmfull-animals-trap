#include "SR04.h"
#include <Servo.h>

//Define utltrasonic sensor connections
#define TRIG_PIN 12
#define ECHO_PIN 11 

// Define RGB LED's connections
#define BLUE 3
#define GREEN 5
#define RED 6

int cage_heigth = 29; // Cage's heigth in centimeters
int counter=0; // This interger variable is there to count how many time something passed in the field of your ultrasonic sensor
int delaytime2=4000; // This is the time that the system will wait before activating the servo motor when something is detected
// We can see this delay as a "confidence making" time. The nuisible animal's awarness will decrease and there is a lower probability
// that the animal reacts quick enough   

SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a; // The distance between the ultrasonic sensor and the nearest reflecting surface
Servo myservo;

// Colors values for RGB LED
int redValue;
int greenValue;
int blueValue;



void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  
  myservo.attach(9);// Connect pin 9 with the control line(the middle line of Servo) 
  myservo.write(00);// Move servos to center initial position
  
  delay(1000); // Delay to make sure everithing is well prametrized before enabeling detection
}

void loop() {
   a=sr04.Distance(); // Measure of the distance between ultrasonic sensor and nearest reflecting surface (cm)
   if (a < cage_heigth) {      // If the distance is lower than your cage's heigth, there is something in it
    counter=counter+1;
    if (counter==4){
      delaytime2=0;
    }
    delay(delaytime2);
    a=sr04.Distance();
    if (a < cage_heigth){  // Make sure the animal is still below the sensor
      myservo.write(180); // Pull the trigger of your trap
    
      loop(); {
      #define delayTime 1 // Fading time between colors
      
        redValue = 255; // Choose a value between 1 and 255 to change the color.
        greenValue = 0;
        blueValue = 0;
    
      
        for (int i = 0; i < 255; i += 1) // Fades out red bring blue full when i=255
          redValue -= 1;
          blueValue += 1;
          analogWrite(RED, redValue);
          analogWrite(BLUE, blueValue);
          delay(delayTime);
        }
      
      
        redValue = 0;
        greenValue = 0;
        blueValue = 255;
      
        for (int i = 0; i < 255; i += 1) // Fades out blue bring red full when i=255
        {
          blueValue -= 1;
          redValue += 1;
          analogWrite(BLUE, blueValue);
          analogWrite(RED, redValue);
          delay(delayTime);
        }
      }
    }
   delay(1);
}
 
