#include <Adafruit_MotorShield.h>
int left, right, thresholdl, thresholdr;
int ByteReceived;
int SPEED;
String input; 
String command;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();


// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *motor_l = AFMS.getMotor(3);
Adafruit_DCMotor *motor_r = AFMS.getMotor(4);


void setup() {  
  uint8_t i;

  SPEED = 30;
  thresholdl = 800 ;
  thresholdr = 800;
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

  
  motor_r->setSpeed(SPEED);
  motor_l->setSpeed(SPEED+15);
  left=analogRead(A0); 
  right = analogRead(A1); 


//Interface
 if (Serial.available() > 0)
 {
   ByteReceived = Serial.read();

//   //If enter was pressed on the serial command line
   if (ByteReceived == 10){
    command = input;
    input = "";

    //Change the right threshold. format is r999
   if (command.substring(0,1) == "r"){
     thresholdr = command.substring(1,4).toInt();    
   }
// Change the left threshold parameter. format is l999
   if (command.substring(0,1) == "l"){
     thresholdl = command.substring(1,4).toInt();
    }

    command = "";
  } else {
  input =  input + (char)ByteReceived;
  }



 }  
//



  if ((left < thresholdl) && (right < thresholdr)) {

    //Serial.println(left);
    motor_r->run(BACKWARD);
    motor_l->run(FORWARD);
   
  }
  delay(80);

  
  if ((left < thresholdl) && (right > thresholdr)) {
    //if right side sense black tape (Turn right)
    motor_r->setSpeed(SPEED);
    motor_r->run(RELEASE);
    motor_l->run(FORWARD);

    delay(80);
    
  }
    if ((left > thresholdl) && (right < thresholdr)) {
    //if LEFT side sense black tape (Turn left)

    //Serial.println(left);
    motor_l->setSpeed(SPEED+5);

    motor_r->run(BACKWARD);
    motor_l->run(RELEASE);

    delay(80);


  }

      Serial.print(left);
    Serial.print(",");
    Serial.println(right); 




   

}
