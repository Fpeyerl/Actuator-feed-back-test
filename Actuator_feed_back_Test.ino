//include <elapsedMillis.h>
//elapsedMillis timeElapsed;

int brMoveToLimit(int);
//int stMoveToLimit(int);
//void stDriveActuator(int Direction, int Speed);
void brDriveActuator(int Direction, int Speed);

#define EXTEND -1
#define RETRACT 1
#define STOP 0
#define MARGIN 20   //counts

//uses DROK dual H-bridge driver board
int brIN3 = 7;         //in3
int brIN4 = 8;         //in4
int brENB = 6;         //enable pin (pwm) 
int brSensorPin = A1;   //brake fb
int brSensorVal;        //brake fb value 0 - 1023 

int Speed = 7;       
int buffer = 20;         //dead zone around center position

int brMinReading;     //actual maximum fb value 0-1023
int brMaxReading;     //actual minimum fb value 0-1023
int forwardValue;
int backValue;

void setup() {
  
  pinMode(brIN3, OUTPUT);        //these two pins control direction of actuator
  pinMode(brIN4, OUTPUT);        //for the brake actuator
  pinMode(brENB, OUTPUT);
  pinMode(brSensorPin, INPUT);   //fb pin from brake actuator
  digitalWrite(brENB, LOW);      //initially turn off brake actuator
  Serial.begin(9600);
  
 
 // Serial.println(brMinReading);
  
  //brMinReading = brMoveToLimit(RETRACT); //get brake drive actuator retract limit
  //brCenter=(brMaxReading-brMinReading)/2;
  
}

void loop(){
  
  Serial.println("Extending act.");
  brMoveToLimit(EXTEND);  //get brake drive actuator extend limit
  delay(3000);  //delay so we can read the screen
  
  
  Serial.println("Retracting act.");
  brMoveToLimit(RETRACT);  //get brake drive actuator extend limit
  delay(3000);  //delay so we can read the screen
  
}

/* finds the limit of the actuator feedback signal  
 inputs: Direction values: EXTEND -1   RETRACT  1   */
int brMoveToLimit(int Direction){
  
  int prevReading=0;
  int currReading=0;
  brDriveActuator(Direction, 125);  //this keeps actuator moving in one direction unit prev reading = current reading within some margin
   
  do{
    prevReading = currReading;
    delay(100);
    currReading = analogRead(brSensorPin);
    Serial.println(currReading);
  }while( prevReading != currReading);

  brDriveActuator(STOP, 0);
  
  //return currReading;
}
/* params Direction= EXTEND / RETRACT; Speed 0-125 pwm sig.*/
void brDriveActuator(int Direction, int Speed){   //this is for the steering acuator only

int prevDirection; //may need this

  switch(Direction){
    case 1:       //extension
      
      digitalWrite(brIN4, 1);
      digitalWrite(brIN3, 0);
      analogWrite(brENB, Speed);
      break;
   
    case 0:       //stopping
      digitalWrite(brIN4, 0);
      digitalWrite(brIN3, 0);
      analogWrite(brENB,  0);
      break;

    case -1:      //retraction
      digitalWrite(brIN4, 0);
      digitalWrite(brIN3, 1);
      analogWrite(brENB, Speed);
      break;
  }
}




 
