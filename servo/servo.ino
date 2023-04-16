/*  0932 - Simple servo motor demo
 * 
 * This sketch shows you how to control two small 5V servo motors connected directly to the Arduino.
 * 
 * The sketch makes the arm of the servo motor to move in a 180 degree angle.
 * 
 * 
 * Components
 * ----------
 *  - Arduino Uno
 *  - One or two hobby servo motors
 *  - A small electrolitic capacitor
 *  
 *  Libraries
 *  ---------
 *  - Servo (comes with the Arduino IDE)
 *
 * Connections
 * -----------
 *  
 * For the motors:
 * Brown wire: Breadboard's "-" power rail.
 * Red wire: Breadboard's "+" power rail.
 * Yellow wire: One motor's to Arduino pin 9, and the other motor's to Arduino pin 10.
 * 
 * For the breadboard:
 * Connect the external power supply. The GND wire goes to the breadboard's "-" power rail. The 5V 
 * wire goes to breadboard's "+" power rail.
 * Connect a small electrolitic capacitor directly onto the power rail if you notice your servos
 * not working properly. Observe the polarity of the capacitor!
 * 
 *     
 *  More information
 *  ----------------
 *  For more information on the servo library, see https://www.arduino.cc/en/reference/servo
 *  
 *  Created on May 29 2017 by Peter Dalmaris
 * 
 */

#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                           // a maximum of eight servo objects can be created 
 
int pos = 0 ;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 

 
} 

 
void loop() 

{ 
  

// If you are using a normal 180-degree servo, try the following. 
// The code below sweeps the servo from 0 degrees to 180 degrees
// If you notice that your servo is "trashing" when it reaches the ends of its travel
// path, increase the low end by a little (say, make it 10 degrees) and decrease the 
// top end by a little (say, make it 170 degrees).

//myservo.write(120);
//delay(2000);

for (pos = 0; pos <= 150; pos += 1) { // goes from 0 degrees to 180 degrees
   
    myservo.write(pos);              // tell servo 1 to go to position in variable 'pos'
    delay(50);                       // waits 5ms for the servo to reach the position
}

delay(2000);

for (pos = 90; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
   
    myservo.write(pos);              // tell servo 1 to go to position in variable 'pos'
    delay(50);                       // waits 5ms for the servo to reach the position
}

delay(2000);


myservo.write(0);
delay(2000);


}


//myservo.write(180);
//delay(1000);
//
//myservo.write(30);
//delay(1000);
//
//for (pos = 150; pos >= 60; pos -= 1) { // goes from 0 degrees to 180 degrees
//   
//    myservo.write(pos);              // tell servo 1 to go to position in variable 'pos'
//    delay(50);                       // waits 5ms for the servo to reach the position
//}
//delay(1000);
//
//myservo.write(180);
//delay(1000);
//
//for (pos = 180; pos >= 30; pos -= 1) { // goes from 0 degrees to 180 degrees
//   
//    myservo.write(pos);              // tell servo 1 to go to position in variable 'pos'
//    delay(50);                       // waits 5ms for the servo to reach the position
//}
//delay(1000);
//
//for (pos = 30; pos <=90; pos+=1) {
//
//  myservo.write(pos);
//  delay(20);
//}
