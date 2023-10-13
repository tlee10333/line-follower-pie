#include <Adafruit_MotorShield.h>
int left, right;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();


// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotorn = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor = AFMS.getMotor(4);


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");  

}

void loop() {
  uint8_t i;
  uint8_t SPEED = 30;
  myMotor->setSpeed(SPEED);
  myMotorn->setSpeed(SPEED);
  left=analogRead(A0); 
  right = analogRead(A1); 


  if ((left < 950) && (right < 860)) {

    //Serial.println(left);
    myMotor->run(BACKWARD);
    myMotorn->run(FORWARD);
    delay(10);
    
  }
  delay(10);

   myMotor->run(RELEASE);
    myMotorn->run(RELEASE);

  Serial.println(right);

//  myMotor->run(FORWARD);
//  myMotorn->run(BACKWARD);

   

}
