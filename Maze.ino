#include <Servo.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>

const bool debug = false;

const int trig = 2; //Ultrasonic
const int echo = 3; //Ultrasonic

Servo neck; //Servo Motor
AF_DCMotor leftTire(4);
AF_DCMotor rightTire(1);

const int leftSpeed = 100;
const int rightSpeed = 87;

const int collision_distance = 11;
const int collision_left = 7;
const int collision_right = 7;
const int mazeCellWidth; // TODO TEST Calculate

const int FRONT_ORIENT = 90;
const int LEFT_ORIENT = 0;
const int RIGHT_ORIENT = 180;

int face_orient = 90;
bool movingRight = true;
bool driving = false;

int last_distance;
int error_counter;


//  Check distance(in cm) from ultrasonic
long sonicDistance(){
    long dur;
    long dis;
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

// rotates the servo periodically
void nextNeckAngle(){
    // TODO there's a  better way to handle this
    if(face_orient == 180){
        movingRight = false;
    }else if (face_orient == 0){
        movingRight = true;
    }
    if(movingRight){
        if(face_orient == 0){
            face_orient = 90;
        }else if(face_orient == 90){
            face_orient = 180;
        }
    }else{
        if(face_orient == 180){
            face_orient = 90;
        }else if(face_orient == 90){
            face_orient = 0;
        }
    }
    neck.write(face_orient);
    delay(250);
}

//Tyres
void moveFwd(){
    leftTire.setSpeed(leftSpeed);
    rightTire.setSpeed(rightSpeed);
    leftTire.run(FORWARD);
    rightTire.run(FORWARD);
    driving = true;
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
    driving = false;
    delay(250);
}

void rotateRight(){
    leftTire.setSpeed(leftSpeed);
    leftTire.run(FORWARD);
}

void rotateLeft(){
    rightTire.setSpeed(rightSpeed);
    rightTire.run(FORWARD);
}

void nudgeRight(int nudgeTime){
    rightTire.run(RELEASE);
    delay(nudgeTime);
    rightTire.setSpeed(rightSpeed);
    rightTire.run(FORWARD);
}// TODO TEST Nudge

void nudgeLeft(int nudgeTime){
    leftTire.run(RELEASE);
    delay(nudgeTime)
    leftTire.setSpeed(leftSpeed);
    leftTire.run(FORWARD);
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

// Check Direction to turn
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
    neck.write(face_orient);
    delay(1000);
    if(left>right){
        return 'l';
    }else{
        return 'r';
    }
}

// Turn in a particular direction
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

//Function comparing current distance to last
bool hasntMoved(long dist){
    return (dist>= last_distance-2 && dist <= last_distance+2);

}

void setup() {
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    neck.attach(9);

    moveFwd();
}

void loop() {
    if(face_orient == FRONT_ORIENT){ // Facing front
        if(sonicDistance() <= collision_distance){
            stopTyres();
            if(sonicDistance() <= collision_distance){
                // TODO Store Node in Graph
                turnTowards(checkToTurn());
            }
            moveFwd();
        }
    }else {
        if(face_orient == LEFT_ORIENT){ // Facing Left
            int sd = sonicDistance();
            if(sd <= 8){
                if(driving){
                    nudgeRight(100);
                }
            }else if(sd>mazeCellWidth){
                // stopTyres();
                // TODO Record Node to the Left in Graph
            }
        }else if(face_orient==RIGHT_ORIENT){ // Facing Right
            int sd = sonicDistance();
            if(sd <= 8){
                if(driving){
                    nudgeLeft(100);
                }
            }else if(sd>mazeCellWidth){
                // stopTyres();
                // TODO Record Node to the Right in Graph
            }
        }
    }
    if(hasntMoved(sonicDistance() )){
        error_counter++;
        if(error_counter==4){
            moveBack();
            delay(600);
            stopTyres();
            moveFwd();
            error_counter=0;
        }
    }else{
        last_distance = sonicDistance();
        error_counter=0;
    }
    nextNeckAngle();
}