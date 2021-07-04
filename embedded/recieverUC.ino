#include <SoftwareSerial.h>
#include <Servo.h>

#define rxPin 7
#define txPin 8

SoftwareSerial mySerial (rxPin,txPin); //RX, TX
#define relay_cold A3
#define relay_hot A2
#define sensor_cold A4

Servo myservoFront;  
Servo myservoBack;
Servo myservoRight;
Servo myservoLeft;

int pos = 135;

const int buffer_size = 25;
char buff[buffer_size];
char holds_numbers[25];
int data;
int count = 0;
char y;
char z;
char a;
char b;
char c;
char d;
char t;
String temp1;
String temp2;
String temp3;
String temp4;
String r;
String s;

int k;
int l;
int reading;
float temperature;
int dorsiAngle;
int plantarAngle;
int inversionAngle;
int eversionAngle;
int rangeAngleminus;
int rangeAngleplus;
int servoposition =135;
int dorsi_sets;
int plantar_sets;
int inversion_sets;
int eversion_sets;
int range_sets;
char mystr[9] = "Finished!";


void setup() {
  mySerial.begin(9600);

  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
 
  myservoFront.write(135);
  myservoBack.write(135);
  myservoRight.write(135);
  myservoLeft.write(135);
 
  pinMode(relay_cold, OUTPUT);
  pinMode(relay_hot, OUTPUT);
 
  myservoFront.attach(5);  
  myservoBack.attach(9);
  myservoRight.attach(10);
  myservoLeft.attach(6);
}

void loop() {
 
   if(mySerial.available() > 0){
    data = mySerial.readBytes(buff, buffer_size);
    delay(1000);
    for(int i = 0; i <data; i++){
      holds_numbers[i] = buff[i];
      //mySerial.print(holds_numbers[i]);
  }
  y = holds_numbers[0];
  z = holds_numbers[2];
  a = holds_numbers[4];
  b = holds_numbers[6];
  c = holds_numbers[8];
  d = holds_numbers[10];
  t = holds_numbers[12];
 
  if(holds_numbers[13] == ' ' && holds_numbers[15] == ' '){
    r = holds_numbers[14];
    k = r.toInt();
  }
  else if(holds_numbers[13] == ' ' && holds_numbers[16] == ' '){
    temp1 = holds_numbers[14];
    temp2 = holds_numbers[15];
    r = String (temp1 + temp2);
    k = r.toInt();
  }
 
  if(holds_numbers[16] == ' ' && holds_numbers[19] == ' '){
    temp3 = holds_numbers[17];
    temp4 = holds_numbers[18];
    s = String(temp3 + temp4);
    l = s.toInt();
  }
  else if(holds_numbers[15] == ' ' && holds_numbers[17] == ' '){
    s = holds_numbers[16];
    l = s.toInt();
  }
  else if(holds_numbers[16] == ' ' && holds_numbers[18] == ' '){
    s = holds_numbers[17];
    l = s.toInt();
  }
  else if(holds_numbers[15] == ' ' && holds_numbers[18] == ' '){
    temp3 = holds_numbers[16];
    temp4 = holds_numbers[17];
    s = String(temp3 + temp4);
    l = s.toInt();
  }
  //mySerial.print(k);
  //mySerial.print(l);
   
  //temperature supply switch
   if (t == '3'){
    digitalWrite(relay_hot, HIGH);
   }
   else if (t == '2'){
    digitalWrite(relay_cold, HIGH);  
   }

   //plantar angle options
   if (a == '1'){
    dorsiAngle = (servoposition - 36);
   }
   else if (a == '2'){
    dorsiAngle = (servoposition - 72);
   }
    else if (a == '3'){
    dorsiAngle = (servoposition - 72);
   }
   else if (a == '4'){
    dorsiAngle = (servoposition - 72);
   }
   else if (a == '5'){
    dorsiAngle = (servoposition - 72);
   }

   //plantar Exercise
   if (y == '2'){
   for (dorsi_sets = 1; dorsi_sets <= l; dorsi_sets +=1){
    for (int dorsi_reps = 1; dorsi_reps <= k; dorsi_reps +=1){
      for (pos = 135; pos >= dorsiAngle; pos -= 1) { 
        // in steps of 1 degree
        myservoFront.write(pos);              
        myservoBack.write(pos);
        delay(15);                       
      }
      for (pos = dorsiAngle; pos <= 135; pos += 1) { 
        myservoFront.write(pos);              
        myservoBack.write(pos);
        delay(15);                       
      }
     }
   }
   digitalWrite(relay_cold, LOW);
   digitalWrite(relay_hot, LOW);
   mySerial.write(mystr,9);
   }

 //dorsi angle options
   if (z == '1'){
    plantarAngle = (servoposition + 72);
   }
   else if (z == '2'){
    plantarAngle = (servoposition + 72);
   }
    else if (z == '3'){
    plantarAngle = (servoposition + 72);
   }
   else if (z == '4'){
    plantarAngle = (servoposition + 72);
   }

   //dorsi Exercise
   if (y == '1'){
   for (plantar_sets = 1; plantar_sets <= l; plantar_sets +=1){
    for (int plantar_reps = 1; plantar_reps <= k; plantar_reps +=1){
      for (pos = 135; pos <= plantarAngle; pos += 1) { 
        // in steps of 1 degree
        myservoFront.write(pos);              
        myservoBack.write(pos);
        delay(15);                       
      }
      for (pos = plantarAngle; pos >= 135; pos -= 1) { 
        myservoFront.write(pos);              
        myservoBack.write(pos);
        delay(15);                       
      }
     }
   }
   digitalWrite(relay_cold, LOW);
   digitalWrite(relay_hot, LOW);
   mySerial.write(mystr,9);
   }

   //Inversion Angle Options
   if (b == '1'){
    inversionAngle = (servoposition - 36);
   }
   else if (b == '2'){
    inversionAngle = (servoposition - 72);
   }
    else if (b == '3'){
    inversionAngle = (servoposition - 72);
   }
   else if (b == '4'){
    inversionAngle = (servoposition - 72);
   }
   else if (b == '5'){
    inversionAngle = (servoposition - 72);
   }
   else if (b == '6'){
    inversionAngle = (servoposition - 72);
   }
   else if (b == '7'){
    inversionAngle = (servoposition - 72);
   }
   //Inversion Exercise
   if (y == '3'){
   for (inversion_sets = 1; inversion_sets <= l; inversion_sets +=1){
    for (int inversion_reps = 1; inversion_reps <= k; inversion_reps +=1){
      for (pos = 135; pos >= inversionAngle; pos -= 1) { 
        // in steps of 1 degree
        myservoRight.write(pos);              
        myservoLeft.write(pos);
        delay(15);                       
      }
      for (pos = inversionAngle; pos <= 135; pos += 1) { 
        myservoRight.write(pos);              
        myservoLeft.write(pos);
        delay(15);                       
      }
     }
   }
   digitalWrite(relay_cold, LOW);
   digitalWrite(relay_hot, LOW);
   mySerial.write(mystr,9);
   }

   //Eversion Angle Options
   if (c == '1'){
    eversionAngle = (servoposition + 36);
   }
   else if (c == '2'){
    eversionAngle = (servoposition + 72);
   }
    else if (c == '3'){
    eversionAngle = (servoposition + 72);
   }
   else if (c == '4'){
    eversionAngle = (servoposition + 72);
   }
   else if (c == '5'){
    eversionAngle = (servoposition + 72);
   }

   //Eversion Exercise
  if (y == '4'){
   for (eversion_sets = 1; eversion_sets <= l; eversion_sets +=1){
    for (int eversion_reps = 1; eversion_reps <= k; eversion_reps +=1){
      for (pos = 135; pos <= eversionAngle; pos += 1) { 
        // in steps of 1 degree
        myservoRight.write(pos);              
        myservoLeft.write(pos);
        delay(15);                       
      }
      for (pos = plantarAngle; pos >= 135; pos -= 1) { 
        myservoRight.write(pos);              
        myservoLeft.write(pos);
        delay(15);                       
      }
     }
   }
   digitalWrite(relay_cold, LOW);
   digitalWrite(relay_hot, LOW);
   mySerial.write(mystr,9);
   }

   //range of motion
    if (d == '1'){
    rangeAngleplus = (servoposition + 36);
    rangeAngleminus = (servoposition - 36);
   }
   else if (d == '2'){
    rangeAngleplus = (servoposition + 36);
    rangeAngleminus = (servoposition - 36);
   }
    else if (d == '3'){
    rangeAngleplus = (servoposition + 36);
    rangeAngleminus = (servoposition - 36);
   }

   //Range of Motion Exercise
  if (y == '5'){
   for (range_sets = 1; range_sets <= l; range_sets +=1){
    for (int range_reps = 1; range_reps <= k; range_reps +=1){
    for (pos = 135; pos <= rangeAngleplus; pos += 1) { 
        // in steps of 1 degree
        myservoFront.write(pos);              
        myservoBack.write(pos);
        delay(15);                       
      }
      for (pos = 135; pos <= rangeAngleplus; pos += 1) { 
        // in steps of 1 degree
        myservoRight.write(pos);              
        myservoLeft.write(pos);
        delay(15);                       
      }
      for (pos = 135; pos >= rangeAngleminus; pos -= 1) { 
        // in steps of 1 degree
        myservoFront.write(pos);              
        myservoBack.write(pos);
        delay(15);                       
      }
     for (pos = 135; pos >= rangeAngleminus; pos -= 1) { 
        // in steps of 1 degree
        myservoRight.write(pos);              
        myservoLeft.write(pos);
        delay(15);                       
      }
   }
   myservoFront.write(135);              
   myservoBack.write(135);
   myservoRight.write(135);
   myservoLeft.write(135);
   digitalWrite(relay_cold, LOW);
   digitalWrite(relay_hot, LOW);
   mySerial.write(mystr,9);
   }
   
//  //temperature senor for peltier
//  reading = analogRead(sensor_cold);
//  temperature = reading *0.48828125;
//  //mySerial.print(temperature);
//  //mySerial.print(" \xC2\xB0");//degree symbol
//  //mySerial.println("C");
//  delay(1000);
}
}
}