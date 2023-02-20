#include <Servo.h>

Servo noddingServo;  // Servo for nodding movement
Servo shakingServo;  // Servo for nodding movement


int BUTTON_PIN = 2;
int ALWAYS_NO_PIN = 9;
int ALWAYS_YES_PIN = 10;

int decision = 0;
int initNoddingPos = 1800;    // variable to store the servo position. In my build I needed to use Microseconds for finer control
int initShakingPos = 90;    // variable to store the servo position
int pos;
int noddingMovement = 2;
int shakingMovement = 60;

void initNoddingServo() {
  noddingServo.attach(7);
  noddingServo.writeMicroseconds(initNoddingPos);
  delay(30);  
}

void initShakingServo() {
  shakingServo.attach(4);
  shakingServo.write(initShakingPos);
  delay(30);  
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(ALWAYS_YES_PIN, INPUT_PULLUP);
  pinMode(ALWAYS_NO_PIN, INPUT_PULLUP);
}

void encourage() {
  initNoddingServo();
  
  noddingServo.writeMicroseconds(1750);
  delay(500);    
  noddingServo.writeMicroseconds(1850);
  delay(500);       
  noddingServo.writeMicroseconds(1750);
  delay(500);    
  noddingServo.writeMicroseconds(1850);
  delay(500);       

  initNoddingServo();
  noddingServo.detach();
}

void discourage() {
  initShakingServo();   

  for (pos = initShakingPos; pos <= initShakingPos + shakingMovement; pos += 2) { // goes from one position to the other
    shakingServo.write(pos);         // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = initShakingPos + shakingMovement; pos >= initShakingPos - shakingMovement; pos -= 2) { 
    shakingServo.write(pos);
    delay(15);
  }
  for (pos = initShakingPos - shakingMovement; pos <= initShakingPos; pos += 2) {
    shakingServo.write(pos);
    delay(15);
  }
  for (pos = initShakingPos; pos <= initShakingPos + shakingMovement; pos += 2) {
    shakingServo.write(pos);
    delay(15);
  }
  for (pos = initShakingPos + shakingMovement; pos >= initShakingPos; pos -= 2) {
    shakingServo.write(pos);
    delay(15);
  }

  initShakingServo();
  shakingServo.detach();
}


void loop() {

  if (digitalRead(BUTTON_PIN) == LOW) {
    if (digitalRead(ALWAYS_NO_PIN) == LOW) { 
      discourage();
    } else if (digitalRead(ALWAYS_YES_PIN ) == LOW) {
      encourage();
    } else {
      decision = millis();
      if ((decision % 2) == 0) {
        discourage();
      } else {
        encourage();
      }
    }
  }

  delay(10);
}
