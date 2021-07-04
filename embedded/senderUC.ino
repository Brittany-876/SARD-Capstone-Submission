#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Keypad.h>
#include <SoftwareSerial.h>

#define rxPin 7
#define txPin 8
LiquidCrystal_I2C lcd(0x27, 20, 4);
SoftwareSerial mySerial (rxPin, txPin); 

#define userID_Length 7
char Data[userID_Length];
byte data_count = 0;
char keypressed;
byte column = 0;
int menu = 1;
int x = 1;
int y = 1;
int z = 1;
int a = 1;
int b = 1;
int c = 1;
int d = 1;
int r = 0;
int s = 0;
int t = 1;
int e = 1;
int f = 1;
char buff[25];
const int mystr_size = 9;
char mystr[18];
char holds_data[9];

//constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4; 

//Array to represent keys on keypad
char keyslayout [ROWS] [COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Connections to uC
byte rowPins[ROWS] = {2, 3, 4, 5};//row connections
byte colPins [COLS] = {A0, A1, A2, A3}; //column connections 

//Create keypad object
Keypad customKeypad = Keypad(makeKeymap(keyslayout),rowPins,colPins, ROWS, COLS); //object

void displayScreen(){
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Welcome");
  lcd.setCursor(8,1);
  lcd.print("to");
  lcd.setCursor(7,2);
  lcd.print("Sard");
  lcd.setCursor(5,3);
  lcd.print("*");
  delay(5000);
  user_input_menu();
}

void setup() {
  pinMode (rxPin, INPUT);
  pinMode (txPin, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  displayScreen();
}

void user_input_menu(){
    switch (menu){
      case 0:
        menu = 1;
        break;
      case 1:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Using User ID?"));
        lcd.setCursor(0,1);
        lcd.print(F(">Yes"));
        lcd.setCursor(0,2);
        lcd.print(F("No"));
        break;
      case 2:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Enter User ID:"));
        break;
      case 3:
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print(F("Select Exercise"));
        lcd.setCursor(0,1);
        lcd.print(F(">Dorsiflexion"));
        lcd.setCursor(0,2);
        lcd.print(F("Plantarflexion"));
        lcd.setCursor(0,3);
        lcd.print(F("Inversion"));
        break;
      case 4:
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print(F("Dorsi Angle Shifts:"));
        lcd.setCursor(0,1);
        lcd.print(F(">5 degrees"));
        lcd.setCursor(0,2);
        lcd.print(F("10 degrees"));
        lcd.setCursor(0,3);
        lcd.print(F("15 degrees"));
        break;
      case 5:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Plantar Angle Shift"));
        lcd.setCursor(0,1);
        lcd.print(F(">10 degrees"));
        lcd.setCursor(0,2);
        lcd.print(F("20 degrees"));
        lcd.setCursor(0,3);
        lcd.print(F("30 degrees"));
        break;
      case 6:
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print(F("Inversion Angles:"));
        lcd.setCursor(0,1);
        lcd.print(F(">5 degrees"));
        lcd.setCursor(0,2);
        lcd.print(F("10 degrees"));
        lcd.setCursor(0,3);
        lcd.print(F("15 degrees"));
        break;
      case 7:
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print(F("Eversion Angles:"));
        lcd.setCursor(0,1);
        lcd.print(F(">5 degrees"));
        lcd.setCursor(0,2);
        lcd.print(F("10 degrees"));
        lcd.setCursor(0,3);
        lcd.print(F("15 degrees"));
        break;
      case 8:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Range Options:"));
        lcd.setCursor(0,1);
        lcd.print(F(">Minimal Range"));
        lcd.setCursor(0,2);
        lcd.print(F("Half Range"));
        lcd.setCursor(0,3);
        lcd.print(F("Full Range"));
        break;
      case 9:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("# of reps:"));
        lcd.setCursor(0,1);
        lcd.print(r);
        break;
      case 10:
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print(F("# of sets:"));
        lcd.setCursor(0,1);
        lcd.print(s);
        break;
      case 11:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Select Temperature:"));
        lcd.setCursor(0,1);
        lcd.print(F(">Normal"));
        lcd.setCursor(0,2);
        lcd.print(F("Hot"));
        lcd.setCursor(0,3);
        lcd.print(F("Cold"));
        break;
      case 12:
        lcd.clear(); 
        lcd.setCursor(0,0);
        lcd.print(F("Start exercise?"));
        lcd.setCursor(0,1);
        lcd.print(F(">Yes"));
        lcd.setCursor(0,2);
        lcd.print(F("No"));
        lcd.display();
        break;
      case 13:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(F("Another exercise?"));
        lcd.setCursor(0,1);
        lcd.print(F(">Yes"));
        lcd.setCursor(0,2);
        lcd.print(F("No"));
      break;
    }
}

void loop() {
  char keypressed = customKeypad.getKey();

  if(mySerial.available()){
    mySerial.readBytes(mystr,9);
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print(mystr);
    delay(2000);
    menu = 13;
    user_input_menu();
  }

  if (f == 1 && menu == 13 && keypressed == 'B'){
    f++;
    another_exercise();
  }

  if (f == 2 && menu == 13 && keypressed == 'A'){
    f--;
    another_exercise();
  }

  if (f == 2 && menu == 13 && keypressed == 'D'){
   lcd.clear();
   lcd.setCursor(3,0);
   lcd.print(F("Turn Device Off"));
  }
  
  //navigate up and down startDataoption for menu 1
 if(menu == 1 && x == 1 && keypressed == 'B'){
  x++; 
  start_data_options();
 }
 if(menu == 1 && keypressed == 'A'){
  x--;
  start_data_options();
 }
 
   //navigate thru menu (D - next/enter and * - back)
  if (keypressed == 'D' && menu == 1 & x == 1 ){
    menu = 2;
    user_input_menu();
  }

  if(e == 1 && menu == 12 && keypressed == 'D'){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Let's Go"));
    sprintf(buff, "%d %d %d %d %d %d %d %d %d ", y, z, a, b, c, d, t, r, s);
    mySerial.println(buff);
  }


  if(e == 2 && menu == 12 && keypressed == 'D' || f == 1 && menu == 13 && keypressed == 'D'){
   lcd.clear();
   menu = 1; 
   user_input_menu();//   startData(); // menu = 1
    
    x = 1;
    //menu = 1;
    data_count = 0;
    column = 0;
    y = 1;
    z = 1;
    a = 1;
    b = 1;
    c = 1;
    d = 1;
    r = 0;
    s = 0;
    t = 1;
    e = 1;
    f = 1;
   }

  if (keypressed =='D' && menu == 11){
    menu = 12;
    user_input_menu();
  }

  if (keypressed =='D' && menu == 10){
    menu = 11;
    user_input_menu();
  }
  
  if (keypressed =='D' && menu == 9){
    menu = 10;
    user_input_menu();
  }
  
  if (keypressed == 'D' && (menu == 4 || menu == 5 || menu == 6 || menu == 7 || menu == 8)){
    menu = 9;
    user_input_menu();
  }
 
  if (keypressed == 'D' && menu == 3 && y == 1){
    menu = 4;
    user_input_menu();
  }

  if (keypressed == 'D' && menu == 3 && y == 2){
    menu = 5;
    user_input_menu();
  }
  
  if (keypressed == 'D' && menu == 3 && y == 3){
    menu = 6;
    user_input_menu();
  }

  if (keypressed == 'D' && menu == 3 && y == 4){
    menu = 7;
    user_input_menu();
  }

  if (keypressed == 'D' && menu == 3 && y == 5){
    menu = 8;
    user_input_menu();
  }


  if (keypressed == '*' && ( menu == 2)){
    menu --;
    data_count = 0;
    user_input_menu();
    x = 1;
  }
  else if (keypressed == '*' && (menu == 3)){
    menu = 1;
    user_input_menu();
      data_count = 0;
      column = 0;
      x = 1;
      y = 1;
  }
  if (keypressed == '*' && (menu == 4 || menu == 5 || menu == 6 || menu == 7 || menu == 8 || menu == 9)){
    menu = 3;
    user_input_menu();
    a = 1;
    y = 1;
    z = 1;
    b = 1;
    c = 1;
    d = 1;
    r = 0;
  }

  if(keypressed == '*' && menu == 10){
    menu = 9;
    user_input_menu();
    s=0;
  }

  if(keypressed == '*' && menu == 11){
    menu = 10;
    user_input_menu();
    t = 1;
  }

  if(keypressed == '*' && menu == 12){
    menu = 11;
    user_input_menu();
    e = 1;
  }

  //if person selects no under startData - not using user id
  if(x == 2 && menu == 1 && keypressed == 'D'){
    lcd.clear(); 
      menu = 3;
      //x = 1;
      user_input_menu();
  }
  

  // if person selected yes under startData - using user id
  if (x == 1 && menu == 2 && column <= 4 && (keypressed == '1' || keypressed == '2' || keypressed == '3' || keypressed == '4' || keypressed == '5' || keypressed == '6' || keypressed == '7' || keypressed == '8' || keypressed == '9' || keypressed == '0')){
     column = data_count * 1;
     Data[data_count] = keypressed;
     lcd.setCursor(column, 1);
     lcd.print(Data[data_count]);
     Serial.print(Data[data_count]);
     data_count++;
     }
     else if (menu == 2 && keypressed == 'C'){
     lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Enter User ID:"));
      data_count = 0;
      column = 0;
     }
     else if (column < 5 && menu == 2 && data_count >= 1 &&  keypressed == 'D'){
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print(F("Insufficient Numbers"));
     delay(2000);
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print(F("Enter User ID:"));
     data_count = 0;
     column = 0;
     }
     else if (menu == 2 && column > 4 && keypressed == 'D'){
     lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(F("User ID Entered:"));
      lcd.setCursor(0, 1);
      for (int data_count = 0; data_count < 6; data_count++)
      {
          lcd.print(Data[data_count]);
      }
      //sprintf(patient_ID, "%d%d%d%d%d%d", Data[0], Data[1], Data[2], Data[3], Data[4], Data[5]);
      ///PatientID = String(patient_ID);
      ///lcd.print(PatientID);
      delay(2000);
      lcd.clear(); 
      menu = 3;
      user_input_menu();
     }

   //navigate up and down exercise_options for menu 3
 if(keypressed == 'B' && menu == 3 && (y == 1 || y == 2 || y == 3 || y == 4)){
  y++; 
  exercise_options();
 }
 if(keypressed == 'A' && menu == 3){
  y--;
  exercise_options();
 }

 //navigate up and down dorsi_angle_options for menu 4
if (keypressed == 'B' && menu == 4 && (z == 1 || z == 2 || z == 3)){
  z++;
  dorsi_angle_options();
}
if (keypressed == 'A' && menu == 4){
  z--;
  dorsi_angle_options();
}

//navigate up and down plant_angle_options for menu 5
if(keypressed == 'B' && menu == 5 && (a == 1 || a == 2 || a == 3 || a == 4)){
  a++;
  plant_angle_options();
}
if(keypressed == 'A' && menu == 5){
  a--;
  plant_angle_options();
}

//navigate up and down inversion_angle_options for menu 6
if (keypressed == 'B' && menu == 6 && (b == 1 || b == 2 || b == 3 || b == 4 || b == 5 || b == 6)){
  b++;
  inversion_angle_options();
}
if(keypressed == 'A' && menu == 6){
  b--;
  inversion_angle_options();
}

//navigate up and down eversion_angle_options for menu 7
if (keypressed == 'B' && menu == 7 && (c == 1 || c == 2 || c == 3 || c == 4)){
  c++;
  eversion_angle_options();
}
if(keypressed == 'A' && menu == 7){
  c--;
  eversion_angle_options();
}

//navigate up and down rangeofmotion_angle_options for menu 8
if (keypressed == 'B' && menu == 8 && (d == 1 || d == 2)){
  d++;
  rangeofmotion_angle_options();
}
if(keypressed == 'A' && menu == 8){
  d--;
  rangeofmotion_angle_options();
}

//enter # of reps for menu 9 using up and down
if (menu == 9 && keypressed == 'A'){
      r++;
      user_input_menu();
}
if (menu == 9 && keypressed == 'B'){
      r--;
      user_input_menu();
}

//enter # of sets for menu 10 using up and down
if (menu == 10 && keypressed == 'A'){
      s++;
      user_input_menu();
}
if (menu == 10 && keypressed == 'B'){
      s--;
      user_input_menu();
}

//navigate up and down rangeofmotion_angle_options for menu 8
if (keypressed == 'B' && menu == 11 && (t == 1 || t == 2)){
  t++;
  temperature_options();
}
if(keypressed == 'A' && menu == 11){
  t--;
  temperature_options();
}

 //navigate up and down startDataoption for menu 1
 if(menu == 12 && e == 1 && keypressed == 'B'){
  e++; 
  start_exercise_options();
 }
 if(menu == 12 && keypressed == 'A'){
  e--;
  start_exercise_options();
 }

}

void start_data_options(){
  switch (x){
    case 0:
      x=1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Using User ID?"));
      lcd.setCursor(0,1);
      lcd.print(F(">Yes"));
      lcd.setCursor(0,2);
      lcd.print(F("No"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Using User ID?"));
      lcd.setCursor(0,1);
      lcd.print(F("Yes"));
      lcd.setCursor(0,2);
      lcd.print(F(">No"));  
  }
}

void exercise_options(){
   switch(y){
    case 0:
      y=1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Select Exercise"));
      lcd.setCursor(0,1);
      lcd.print(F(">Dorsiflexion"));
      lcd.setCursor(0,2);
      lcd.print(F("Plantarflexion"));
      lcd.setCursor(0,3);
      lcd.print(F("Inversion"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Select Exercise"));
      lcd.setCursor(0,1);
      lcd.print(F("Dorsiflexion"));
      lcd.setCursor(0,2);
      lcd.print(F(">Plantarflexion"));
      lcd.setCursor(0,3);
      lcd.print(F("Inversion"));
      break;
   case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Select Exercise"));
      lcd.setCursor(0,1);
      lcd.print(F("Dorsiflexion"));
      lcd.setCursor(0,2);
      lcd.print(F("Plantarflexion"));
      lcd.setCursor(0,3);
      lcd.print(F(">Inversion         v"));
      break;
   case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Select Exercise"));
      lcd.setCursor(0,1);
      lcd.print(F(">Eversion          ^"));
      lcd.setCursor(0,2);
      lcd.print(F("Range of Motion"));
      break;
   case 5:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Select Exercise"));
      lcd.setCursor(0,1);
      lcd.print(F("Eversion"));
      lcd.setCursor(0,2);
      lcd.print(F(">Range of Motion"));
   }
}

void dorsi_angle_options(){
  switch (z){
    case 0:
      z = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Dorsi Angle Shifts:"));
      lcd.setCursor(0,1);
      lcd.print(F(">5 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F("10 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F("15 degrees"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Dorsi Angle Shifts:"));
      lcd.setCursor(0,1);
      lcd.print(F("5 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F(">10 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F("15 degrees"));
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dorsi Angle Shifts:");
      lcd.setCursor(0,1);
      lcd.print("5 degrees");
      lcd.setCursor(0,2);
      lcd.print("10 degrees");
      lcd.setCursor(0,3);
      lcd.print(">15 degrees        v");
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Dorsi Angle Shifts:");
      lcd.setCursor(0,1);
      lcd.print(">20 degrees        ^");
      break;
  }
}

void plant_angle_options(){
  switch(a){
    case 0:
      a = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Plantar Angle Shift:");
      lcd.setCursor(0,1);
      lcd.print(">10 degrees");
      lcd.setCursor(0,2);
      lcd.print("20 degrees");
      lcd.setCursor(0,3);
      lcd.print("30 degrees");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Plantar Angle Shift:");
      lcd.setCursor(0,1);
      lcd.print("10 degrees");
      lcd.setCursor(0,2);
      lcd.print(">20 degrees");
      lcd.setCursor(0,3);
      lcd.print("30 degrees");
      break;
   case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Plantar Angle Shift:"));
      lcd.setCursor(0,1);
      lcd.print(F("10 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F("20 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F(">30 degrees        v"));
      break;
   case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Plantar Angle Shift:"));
      lcd.setCursor(0,1);
      lcd.print(F(">40 degrees        ^"));
      lcd.setCursor(0,2);
      lcd.print(F("50 degrees"));
      break;
   case 5:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Plantar Angle Shift:"));
      lcd.setCursor(0,1);
      lcd.print(F("40 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F(">50 degrees"));
      break;
  }
}

void inversion_angle_options(){
  switch (b){
    case 0:
      b = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Inversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F(">5 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F("10 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F("15 degrees"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Inversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F("5 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F(">10 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F("15 degrees"));
      break;
   case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Inversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F("5 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F("10 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F(">15 degrees        v"));
      break;
   case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Inversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F(">20 degrees        ^"));
      lcd.setCursor(0,2);
      lcd.print(F("25 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F("30 degrees"));
      break;
   case 5:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Inversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F("20 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F(">25 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F("30 degrees"));
      break;
   case 6:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Inversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F("20 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F("25 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F(">30 degrees        v"));
      break;
   case 7:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Inversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F(">35 degrees        ^"));
      break;
  }
}

void eversion_angle_options(){
  switch (c){
    case 0:
      c = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Eversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F(">5 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F("10 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F("15 degrees"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Eversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F("5 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F(">10 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F("15 degrees"));
      break;
   case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Eversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F("5 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F("10 degrees"));
      lcd.setCursor(0,3);
      lcd.print(F(">15 degrees        v"));
      break;
   case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Eversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F(">20 degrees        ^"));
      lcd.setCursor(0,2);
      lcd.print(F("25 degrees"));
      break;
   case 5:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Eversion Angles:"));
      lcd.setCursor(0,1);
      lcd.print(F("20 degrees"));
      lcd.setCursor(0,2);
      lcd.print(F(">25 degrees"));
      break;
}
}

void rangeofmotion_angle_options(){
  switch(d){
    case 0:
      d = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Range Options:"));
      lcd.setCursor(0,1);
      lcd.print(F(">Minimal Range"));
      lcd.setCursor(0,2);
      lcd.print(F("Half Range"));
      lcd.setCursor(0,3);
      lcd.print(F("Full Range"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Range Options:"));
      lcd.setCursor(0,1);
      lcd.print(F("Minimal Range"));
      lcd.setCursor(0,2);
      lcd.print(F(">Half Range"));
      lcd.setCursor(0,3);
      lcd.print(F("Full Range"));
      break;
   case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Range Options:"));
      lcd.setCursor(0,1);
      lcd.print(F("Minimal Range"));
      lcd.setCursor(0,2);
      lcd.print(F("Half Range"));
      lcd.setCursor(0,3);
      lcd.print(F(">Full Range"));
      break;
  }
}

void temperature_options(){
  switch(t){
    case 0:
      t = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Temperature Options:"));
      lcd.setCursor(0,1);
      lcd.print(F(">Normal"));
      lcd.setCursor(0,2);
      lcd.print(F("Hot"));
      lcd.setCursor(0,3);
      lcd.print(F("Cold"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Temperature Options:"));
      lcd.setCursor(0,1);
      lcd.print(F("Normal"));
      lcd.setCursor(0,2);
      lcd.print(F(">Hot"));
      lcd.setCursor(0,3);
      lcd.print(F("Cold"));
      break;
   case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Temperature Options:"));
      lcd.setCursor(0,1);
      lcd.print(F("Normal"));
      lcd.setCursor(0,2);
      lcd.print(F("Hot"));
      lcd.setCursor(0,3);
      lcd.print(F(">Cold"));
      break;
  }
}

void start_exercise_options(){
  switch (e){
    case 0:
      e=1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Start exercise?"));
      lcd.setCursor(0,1);
      lcd.print(F(">Yes"));
      lcd.setCursor(0,2);
      lcd.print(F("No"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Start exercise?"));
      lcd.setCursor(0,1);
      lcd.print(F("Yes"));
      lcd.setCursor(0,2);
      lcd.print(F(">No")); 
  }
}

void another_exercise(){
  switch (f){
    case 0:
      f=1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Another exercise?"));
      lcd.setCursor(0,1);
      lcd.print(F(">Yes"));
      lcd.setCursor(0,2);
      lcd.print(F("No"));
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(F("Another exercise?"));
      lcd.setCursor(0,1);
      lcd.print(F("Yes"));
      lcd.setCursor(0,2);
      lcd.print(F(">No")); 
  }
}