// Code for manipulating two servo motos with joystick in axis X and Y
// turning on LED light on arduino when joystick is pressed
// Servos are reseting after every turn on of device
// based on: https://maker.pro/arduino/tutorial/how-to-control-servo-motors-with-an-arduino-and-joystick
// and ; https://github.com/RobertWiktorNycz/arduinoJoystickReadings
// Description of Joystick configuration
// VCC - 5V
// GND - GROUND
// VRX - A0
// VRY - A1
// SW - PIN 2
// Description of servo
// Servo X:
// VCC - 5V
// GND - GROUND
// SIG - PIN 8
// Servo Y
// VCC - 5V
// GND - GROUND
// SIG - PIN 9
// Description of LED
// LED - PIN 13
// Enjoy :)
#include <Servo.h>
// Servo setup
Servo servoX;
Servo servoY;
int servoPositionX = 90;
int servoPositionY = 90;
// LED setup
int LEDPin = 13;
// Joystick mapping setup
int VRx = A0;
int VRy = A1;
int SW = 2;
int SIGX = 8;
int SIGY = 9;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

void setup() {
  // Servo
  servoX.attach(8);
  servoY.attach(9);
  servoX.write(servoPositionX);
  servoY.write(servoPositionY);
  // LED
  pinMode(LEDPin, OUTPUT);
  // Joystick
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  // Serial monitoring
  Serial.begin(9600);
}

void loop() {
  // Reading joystick states
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  // print out variables to to serial monitor for troubleshooting
  Serial.print(" X: ");
  Serial.print(xPosition);
  Serial.print(" Y: ");
  Serial.print(yPosition);
  Serial.print(" button: ");
  Serial.print(SW_state);
  Serial.print(" servoPositionX: ");
  Serial.print(servoPositionX);
  Serial.print(" initial_positionY: ");
  Serial.println(servoPositionY);
  if (xPosition > 600) { // if value of joystick in axis x goes to the right
    if (servoPositionX > 0) { // perform if servoPosition is within servo range (0 - 180 degrees)
      servoPositionX = servoPositionX - 1; // modify servoPosition value
      servoX.write(servoPositionX); // set new servo position
    }
  }
  else if (xPosition < 300) { // if value of joystick in axis x goes to the left
    if (servoPositionX < 180) { // perform if servoPosition is within servo range (0 - 180 degrees)
      servoPositionX = servoPositionX + 1; // modify servoPosition value
      servoX.write(servoPositionX); // set new servo position
    }
  }
  if (yPosition > 600) { // if value of joystick in axis y goes up
    if (servoPositionY > 0) { // perform if servoPosition is within servo range (0 - 180 degrees)
      servoPositionY = servoPositionY - 1; // modify servoPosition value
      servoY.write(servoPositionY); // set new servo position
    }
  }
  else if (yPosition < 300) { // if value of jostick in axis y go down
    if (servoPositionY < 180) { // perform if servoPosition is within servo range (0 - 180 degrees)
      servoPositionY = servoPositionY + 1; // modify servoPosition value
      servoY.write(servoPositionY); // set new servo position
    }
  }
  if (SW_state == 0) { // if joystick pressed turn on LED light on Arduino board
    digitalWrite(LEDPin, HIGH);
  } else {
    digitalWrite(LEDPin, LOW);
  }
}
