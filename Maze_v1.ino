#include <Servo.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>

const int trig = 2; //Ultrasonic
const int echo = 3; //Ultrasonic

Servo neck;
AF_DCMotor leftTire(4);
AF_DCMotor rightTire(1);


const int leftSpeed = 100;
const int rightSpeed = 87;


int collision_distance = 11;

int angle = 90;
bool movingRight = true;

void setup() {
  Serial.begin(9600);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  neck.attach(9);
  
  moveFwd();
}

void loop() {
    if(angle == 90){ // Facing front
      if(sonicDistance()<= collision_distance){
        stopTyres();
        neck.write(90);
        delay(250);
        if(sonicDistance() <= collision_distance){
          // TODO Store Node in Graph
          turnTowards(checkToTurn());
          delay(500);
        }else{
          neck.write(angle);
         delay(500);
        }
        moveFwd();   
      }
    }else if(angle==0){ // Facing Left
      //TODO handle looking left and right
      //Self balancing?
      delay(20);
    }else if(angle==180){ // Facing Right
      //TODO handle looking left and right
      //Self balancing?
      delay(20);
    }else{
      //??
    }
    //Turn Neck and wait for turn to happen
    nextNeckAngle();
    delay(250);
 }


//  Check distance(in cm) from ultrasonic
 int sonicDistance(){
  long dur;
  long dis;
  long dis_in;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);

  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  dur=pulseIn(echo,HIGH);
  if(dur==0){
    // TODO handle Ultrasonic error
  }
  dis = dur / 29 / 2;
  return dis;
}

void nextNeckAngle(){
  // TODO theres a  better way to handle this
  if(angle == 180){
    movingRight = false;
  }else if (angle == 0){
    movingRight = true;
  }
  if(movingRight){
    if(angle == 0){
      angle = 90;
    }else if(angle == 90){
      angle = 180;
    }
  }else{
    if(angle == 180){
      angle = 90;
    }else if(angle == 90){
      angle = 0;
    }
  }
  neck.write(angle);
}

void moveFwd(){
  leftTire.setSpeed(leftSpeed);
  rightTire.setSpeed(rightSpeed);
  leftTire.run(FORWARD);
  rightTire.run(FORWARD);
}

void moveBack(){
  leftTire.setSpeed(leftSpeed);
  rightTire.setSpeed(rightSpeed);
  leftTire.run(BACKWARD);
  rightTire.run(BACKWARD);
  
}

void stopTyres(){
  leftTire.run(RELEASE);
  rightTire.run(RELEASE);
}

char checkToTurn(){
  int front = sonicDistance();
  if(front<9){
    moveBack();
    delay(300);
    stopTyres();
  }
  neck.write(0);
  delay(1000);
  int left = sonicDistance();
  neck.write(180);
  delay(1000);
  int right = sonicDistance();
  neck.write(angle);
  delay(1000);
  if(left>right){
    return 'l';
  }else{
    return 'r';
  }
}

void turnTowards(char point){
  if(point == 'l'){
    rotateLeft();
    delay(850);
    stopTyres();
  }
  if(point == 'r'){
    rotateRight();
    delay(850);
    stopTyres();
  }
}

void rotateRight(){
  leftTire.setSpeed(leftSpeed);
  leftTire.run(FORWARD);
}

void rotateLeft(){
  rightTire.setSpeed(rightSpeed);
  rightTire.run(FORWARD);
}

void rotateRight_Centered(){
  leftTire.setSpeed(leftSpeed);
  rightTire.setSpeed(rightSpeed);
  leftTire.run(FORWARD);
  rightTire.run(BACKWARD);
}

void rotateLeft_Centered(){
  leftTire.setSpeed(leftSpeed);
  rightTire.setSpeed(rightSpeed);
  leftTire.run(BACKWARD);
  rightTire.run(FORWARD);
}
