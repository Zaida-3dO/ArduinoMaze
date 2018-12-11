#include <Servo.h>
#include <AFMotor.h>
#include <SoftwareSerial.h>

const int trig = 2; //Ultrasonic
const int echo = 3; //Ultrasonic
const int wifiRxPin = 6; //WIFI
const int wifiTxPin = 10; //WIFI

Servo neck;
AF_DCMotor leftTire(4);
AF_DCMotor rightTire(1);
//SoftwareSerial wifiSerial(wifiRxPin, wifiTxPin); // RX, TX for ESP8266


int speed = 100;
int speed2 = 87;

int angle = 90;
bool movingRight = true;

int responseTime = 10; //communication timeout
String logs = "start";
bool const DEBUG = true;
int baudRate = 9600; //If this does not work, try 9600, 115200

void setup() {
  Serial.begin(9600);

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  neck.attach(9);
//
//   wifiSerial.begin(115200);
//  Serial.println("Starting Config!");
////  sendToWifi("AT+CIOBAUD=9600", responseTime, DEBUG); //Config Baud R8 //Doesnt work
//  sendToWifi("AT+CWMODE=2", responseTime, DEBUG); // configure as access point
//  sendToWifi("AT+CIFSR", responseTime, DEBUG); // get ip address
//  sendToWifi("AT+CIPMUX=1", responseTime, DEBUG); // configure for multiple connections
//  sendToWifi("AT+CIPSERVER=1,80", responseTime, DEBUG); // turn on server on port 80

//  Serial.println("Wifi connection is running!");

  
  moveFwd();
  // put your setup code here, to run once:

}

void loop() {
//   pingWifi();
   
    delay(250);
    char face = facing();
    if(face == 'f'){
      int sd = sonicDistance();
      if(sd<=11){
        if(sd==0){
          addLog("Sonic returned 0");
          return;
        }
        logSonic(angle,sd);
        stopTyres();
        neck.write(90);
        delay(500);
        sd = sonicDistance();
        if(sonicDistance() <=11){
          if(sd==0){
          addLog("Sonic returned 0");
          return;
        }else{
          addLog("Confirming");
          logSonic(angle,sd);
          turnTowards(checkToTurn());
          delay(500);
        }
        }else{
          neck.write(angle);
         delay(500);
        }
        moveFwd();
        
      }
    }else{
      delay(20);
    }
    nextNeckAngle();
    neck.write(angle);
 }

 void logSonic(int angle, int distance){
  addLog("New Distance"); 
  addLog("Angle",String(angle));
  addLog("Distx",String(distance));
 }

 void addLog(String logFile){
  logs+="\n"+logFile;
 }
 void addLog(String id, String logFile){
  logs+="\n"+id+": "+logFile;
 }

// void pingWifi(){
//  if (wifiSerial.available() > 0) {
//    String message = readWifiSerialMessage();
//    Serial.print("Wifi Sample: ");  
//    Serial.println("start{{}}  "+message+"  {{}}end");
//    sendData(logs);
//  }
// }
  
  
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
  dis = dur / 29 / 2;
  return dis;
  
}

void nextNeckAngle(){
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
}

char facing(){
  if(angle>=0&&angle<=20){
    return 'l';
  }else if(angle>=60&&angle<=120){
    return 'f';
  }else if(angle>=160&&angle<=180){
    return 'r';
  }
  return 'e';
}
  // put your main code here, to run repeatedly:

void moveFwd(){
  leftTire.setSpeed(speed);
  rightTire.setSpeed(speed2);
  leftTire.run(FORWARD);
  rightTire.run(FORWARD);
}
void moveBack(){
  leftTire.setSpeed(speed);
  rightTire.setSpeed(speed2);
  leftTire.run(BACKWARD);
  rightTire.run(BACKWARD);
  delay(300);
  stopTyres();
}

void stopTyres(){
  leftTire.run(RELEASE);
  rightTire.run(RELEASE);
}
char checkToTurn(){
  int front = sonicDistance();
  if(front<9){
    moveBack();
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
    turnLeft();
    delay(700);
    stopTyres();
  }
  if(point == 'r'){
    turnRight();
    delay(850);
    stopTyres();
  }
}

void turnRight(){
  leftTire.setSpeed(speed);
  leftTire.run(FORWARD);
}

void turnLeft(){
  rightTire.setSpeed(speed);
  rightTire.run(FORWARD);
}

void turn(){
  leftTire.setSpeed(100);
  rightTire.setSpeed(95);
  leftTire.run(FORWARD);
  rightTire.run(BACKWARD);
}

/*
  Name: sendData
  Description: Function used to send string to tcp client using cipsend
  Params:
  Returns: void
*/
//void sendData(String str) {
//  String len = "";
//  len += str.length();
//  sendToWifi("AT+CIPSEND=0," + len, responseTime, DEBUG);
//  delay(100);
//  sendToWifi(str, responseTime, DEBUG);
//  delay(100);
//  sendToWifi("AT+CIPCLOSE=5", responseTime, DEBUG);
//}
//
///*
//  Name: readWifiSerialMessage
//  Description: Function used to read data from ESP8266 Serial.
//  Params:
//  Returns: The response from the esp8266 (if there is a reponse)
//*/
//String  readWifiSerialMessage() {
//  char value[100];
//  int index_count = 0;
//  while (wifiSerial.available() > 0) {
//    value[index_count] = wifiSerial.read();
//    index_count++;
//  }
//  value[index_count] = '\0'; // Null terminate the string
//  String str(value);
//  str.trim();
//  return str;
//}



///*
//  Name: sendToWifi
//  Description: Function used to send data to ESP8266.
//  Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
//  Returns: The response from the esp8266 (if there is a reponse)
//*/
//String sendToWifi(String command, const int timeout, boolean debug) {
//  String response = "";
//  
//  Serial.println("SEND TO WIFI: "+command);
//  wifiSerial.println(command); // send the read character to the esp8266
//  long int time = millis();
//  while ( (time + timeout) > millis())
//  {
//    while (wifiSerial.available())
//    {
//      // The esp has data so display its output to the serial window
//      char c = wifiSerial.read(); // read the next character.
//      response += c;
//    }
//  }
//  if (debug)
//  {
//    Serial.println("RESPONSE: "+ response);
//  }
//  return response;
//}
