#include <Adafruit_MotorShield.h>
int left, right, thresholdl, thresholdr;
int ByteReceived;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();


// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor_l = AFMS.getMotor(3);
Adafruit_DCMotor *motor_r = AFMS.getMotor(4);


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
  uint8_t SPEED = 17;
  thresholdl = 850 ;
  thresholdr = 930;
  
  motor_r->setSpeed(SPEED+3);
  motor_l->setSpeed(SPEED);
  left=analogRead(A0); 
  right = analogRead(A1); 


//
 if (Serial.available() > 0)
 {
   ByteReceived = Serial.read();
   Serial.println((char)ByteReceived);
 }  


  if ((left < thresholdl) && (right < thresholdr)) {

    //Serial.println(left);
    motor_r->run(BACKWARD);
    motor_l->run(FORWARD);
    Serial.print("STRAIGHT, ");

    delay(60);
    
  }
  delay(10);

  
  if ((left < thresholdl) && (right > thresholdr)) {
    //if right side sense black tape
    //Serial.println(left);
    motor_r->setSpeed(SPEED+25);

    motor_r->run(RELEASE);
    motor_l->run(FORWARD);
//    Serial.print("TURNING RIGHT, ");

    delay(60);
    
  }
    delay(10);

    if ((left > thresholdl) && (right < thresholdr)) {
    //if LEFT side sense black tape

    //Serial.println(left);
    motor_l->setSpeed(SPEED+25);

    motor_r->run(BACKWARD);
    motor_l->run(RELEASE);
//    Serial.print("TURNING LEFT, ");

    delay(60);


  }


//
//  Serial.print(left);
//  Serial.print(",");
//  Serial.println(right);


//  myMotor->run(FORWARD);
//  myMotorn->run(BACKWARD);

   

}
