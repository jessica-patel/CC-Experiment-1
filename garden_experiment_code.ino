/* 
This code was written for the purpose of creating movement for paper flowers.
This is a part of Experiment 1 in the Creation & Computation course.
Group members: Jessica Patel, Madhu Priya, Ecem Ozturk

This code takes inspiration from the Sweep example in the Arduino IDE.
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

// creating servo objects to control servos that show different movements
Servo openservo;  
Servo spinservo;
Servo swayservo;

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600); // tells Serial Monitor to begin collecting data
}

void loop() {
  int ldrPin = A6; // Light sensor (LDR) connected to analog pin A6
  int ldrValue = analogRead(ldrPin); // Read the analog value from the LDR
  int threshold = 900; // Ambient lighting = 900, Flashlight = 1000, covered = 500
  
  if (ldrValue > threshold) // if light is detected, start the servos
  {
    openservo.attach(2); // attaches servos on pin D2, D3 and D4
    spinservo.attach(3);
    swayservo.attach(4);

    while (ldrValue > threshold) // while loop to get the servos to keep motion while light is shone
    {
    
      for (pos = 0; pos <= 180; pos += 1) // goes from 0 degrees to 180 degrees in steps of 1 degree
      {
        openservo.write(pos); // tell servo to go to position in variable 'pos'
        spinservo.write(pos);
        swayservo.write(pos);
        Serial.println("moving forward");
        delay(15); // waits 15 ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 1) // goes from 180 degrees to 0 degrees
      {
        openservo.write(pos);
        spinservo.write(abs(pos-180));
        swayservo.write(pos);
        Serial.println("moving backward");
        delay(15);
      }

      ldrValue = analogRead(ldrPin);
    }
    
  } else if (ldrValue <= threshold) { // If no light is detected, stop the servo
    openservo.detach(); // detach to stop the servos from moving
    spinservo.detach();
    swayservo.detach();
    Serial.println("covered");
  } else {
    openservo.write(90); // else statement for for loop to work
    spinservo.write(90);
    swayservo.write(90);
  }

  delay(5); // Add a small delay for smooth servo movement
}
