#include <LiquidCrystal.h>
//#include <SoftwareSerial.h>
//SoftwareSerial Serial1(10, 11); // RX, TX
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

  // The counter to make to push buttons stay ON with one push.
int count1 = 0;
int count2 = 0;
int count3 = 0;
int count4 = 0;
int count5 = 0;

 //Putty
int inbyte;

  // customer customer
int customer = 0;
  //interrupt
int interruptX = 0;

  //switch
const int SwitchPin = 47;
  //5 push buttons
const int buttonPin1 = 23;
const int buttonPin2 = 25;
const int buttonPin3 = 27;
const int buttonPin4 = 29;
const int buttonPin5 = 26;
  // 3 LED
const int RedledPin = 13;
const int WhiteledPin = 9;
const int GreenledPin = 8; //special LED
  // potentiometer
int PotentiometerPin = A3;

////////////////////////////////////////

 //
int SwitchState = 0;
  // 5 push buttons states 
int buttonState1 = 0; 
int buttonState2 = 0; 
int buttonState3 = 0; 
int buttonState4 = 0; 
int buttonState5 = 0; 
  // potentiometer state
int PotentiometerValue = 0; // The analogue values read from the potentiometer will go from 0-1023.

void setup() {
  //PUTTY related assigns

  // initialize both serial ports:
  Serial.begin(9600);
  Serial1.begin(9600);

  
  //LCD 
    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
    // Print a message to the LCD.
  lcd.print("Welcome!");

  
    //switch
  pinMode(SwitchPin, INPUT);
    //5 push buttons
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(buttonPin5, INPUT);
    // 3 LED
  pinMode(RedledPin, OUTPUT);
  pinMode(WhiteledPin, OUTPUT);
  pinMode(GreenledPin, OUTPUT);
  
  randomSeed(analogRead(A0)); // generating a random seed to make the random number more random and not predectable.

  attachInterrupt(digitalPinToInterrupt(buttonPin4), blink, CHANGE);
}

void loop() {
  //switch state reading
SwitchState = digitalRead(SwitchPin);
  //5 push buttons state reading
buttonState1 = digitalRead(buttonPin1);
buttonState2 = digitalRead(buttonPin2);
buttonState3 = digitalRead(buttonPin3);
buttonState4 = digitalRead(buttonPin4);
buttonState5 = digitalRead(buttonPin5);
  //Potentiometer value reading
PotentiometerValue = analogRead(PotentiometerPin);




 if (SwitchState == HIGH){
  /*if (customer % 2 == 1){ // checks if the customer is even or odd, if even then it is after 2 customer and chef needs a break.
    lcd.setCursor(0, 0);
    lcd.print("The chef needs ");
    lcd.setCursor(0, 1);
    lcd.print("a 5 second break");
  }*/
      // set up the LCD's number of columns and rows:
  //lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.setCursor(0, 0);
    lcd.print("Start!");
  

  if(buttonState1 == HIGH){
    count1 = 1;
  }
    if (count1 == 1){
        // set the cursor to column 0, line 1
        // (note: line 1 is the second row, since counting begins with 0):
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("You are Waiting!");
          
    if (buttonState5 == HIGH){
      count5 = 1;
    }
            if (count5 == 1){
                customer++;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("You are Serving!");
                delay(1000);
                ;
                
                if (buttonState2 == HIGH){
                  count2 = 1;
                }
                if (buttonState3 == HIGH){
                  count3 = 1;
                }
                if (count2 == 1 && count3 == 0){
                  // for Meat
                  lcd.clear();
                  digitalWrite(WhiteledPin, LOW);
                  digitalWrite(RedledPin, HIGH); // turn the LED on (HIGH is the voltage level)
                  delay(10000);
                  
                  digitalWrite(RedledPin, HIGH);
                  //lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Type of Meat: ");
                  Serial.print(PotentiometerValue);
                    if (680 < PotentiometerValue && PotentiometerValue <= 1023){
                      // Done
                      
                      lcd.setCursor(0, 0);
                      lcd.print("Type of Meat: ");
                      lcd.setCursor(1, 1);
                      lcd.print("WELL DONE");
                      delay(1000);
                      lcd.clear();

                    }if (682 > PotentiometerValue && PotentiometerValue > 341){
                      // Meduim
                      
                      lcd.setCursor(0, 0);
                      lcd.print("Type of Meat: ");
                      lcd.setCursor(1, 1);
                      lcd.print("MEDUIM");
                      delay(1000);
                      lcd.clear();

                    }if (341 > PotentiometerValue && PotentiometerValue >= 0){
                      //raw
                      
                      lcd.setCursor(0, 0);
                      lcd.print("Type of Meat: ");
                      lcd.setCursor(1, 1);
                      lcd.print("RAW");
                      delay(1000);
                      lcd.clear();

                    }
                if (buttonState3 == HIGH){
                  count3 = 1;
                }
                } if (count3 == 1 && count2 == 0){
                  // for Chicken
                  lcd.clear();
                  lcd.setCursor(0, 0);
                  lcd.print("Chicken");
                  delay(15000);
                  lcd.setCursor(1, 1);
                  lcd.print("Ready in 15s");
                  delay(15000);
                  //LED
                  digitalWrite(WhiteledPin, HIGH); // turn the LED on (HIGH is the voltage level)
                  digitalWrite(RedledPin, LOW);
                  delay(15000);
                  digitalWrite(WhiteledPin, LOW);
                }
            }
    }
 }
 //////////////////////////////////////////////////////////
 if (interruptX == 1){
      char RandomNumber = random(2); // generating a random number whenever the program starts.
    static unsigned long startTime = micros(); // get the start time in microseconds, static to keep the value between function calls
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("On Hold");                                                                    // fade in from min to max in increments of 5 points:
    
    while (micros() - startTime < 20000000UL) { // run the loop for 20 seconds, using unsigned long (UL) to specify the literal as an unsigned long

      for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 10)
      {
                                                                            // sets the value (range from 0 to 255):
      analogWrite(GreenledPin, fadeValue);
                                                                         // wait for 30 milliseconds to see the dimming effect
      //delay(30);
      delay(30);
      }
                                                                      // fade out from max to min in increments of 5 points:
      for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 10)
      {
                                                                    // sets the value (range from 0 to 255):
      analogWrite(GreenledPin, fadeValue);
                                                                   // wait for 30 milliseconds to see the dimming effect
      //delay(30);
      delay(30);
      }
    }
    
    if (RandomNumber == 0){
      //home delevry order is chekein
                        // for Meat
      lcd.clear();
      digitalWrite(WhiteledPin, LOW);
      digitalWrite(RedledPin, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(10000);
      
      digitalWrite(RedledPin, HIGH);
      //lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Type of Meat: ");
      
    }else {
      // home delvery is meat (which is when RandomNumber = 1)
            // for Chicken
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Chicken");
      delay(15000);
      lcd.setCursor(1, 1);
      lcd.print("Ready in 15s");
      delay(15000);
      //LED
      digitalWrite(WhiteledPin, HIGH); // turn the LED on (HIGH is the voltage level)
      digitalWrite(RedledPin, LOW);
      delay(15000);
      digitalWrite(WhiteledPin, LOW);
    }
    //////////////////////putty
    // read from port 1, send to port 0:
    if (Serial1.available()) {
    int inByte = Serial1.read();
    Serial.write(inByte);
    }
    // read from port 0, send to port 1:
    if (Serial.available()) {
    int inByte = Serial.read();
    Serial1.write(inByte);
    }
    //////////////////////putty

 }if (interruptX > 0){
  interruptX = 0;
 }
//////////////////////////////////////////////////////////
}
void blink(){
  interruptX++;
  //Serial1.print("inbyte");
} 
