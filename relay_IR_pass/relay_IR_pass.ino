//WORKS!!

#include <Arduino.h>
//adding LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Adding millis to code (check if cause timming problems)
byte delay_time=50;
unsigned long curr_time=0;
unsigned long prev_time=0;

//RELAY controlled by IR remote
#define Relay_ON LOW
#define Relay_OFF HIGH
byte relay_pin=8;

//password
String pass="ABCD";
String off="1234";
String entered="";
String offed="";

//#define DECODE_NEC          // Includes Apple and Onkyo ~ 250 bytes
//#define DECODE_RC5          // RC5 + MARANTZ: ~ 425 bytes
//#define DECODE_OPENLASIR    // Modified NEC with 8-bit validated address + 16-bit command. ~ 175 bytes
//#define RAW_BUFFER_LENGTH  750 // For air condition remotes it may require up to 750. Default is 200.

#include "PinDefinitionsAndMore.h" // Define macros for input and output pin etc. Sets FLASHEND and RAMSIZE and evaluates value of SEND_PWM_BY_TIMER.
#define DECODE_NEC
#include <IRremote.hpp> // include the library

void setup() {
    Serial.begin(9600);
    Serial.println("Running at 9600");
    Serial.flush(); // Blocks until all outgoing characters have been sent
    Serial.begin(115200);
    //LCD
    lcd.init();
    lcd.backlight();
    // pinMode(bl, OUTPUT); use PWM for dimming or external resistor
    // analogWrite(bl,150);
    lcd.setCursor(0, 0);
    lcd.print("RELAY: OFF");
    lcd.setCursor(0, 1);
    lcd.print("PASS :");
    // relay
   digitalWrite(relay_pin,Relay_OFF);
   pinMode(relay_pin,OUTPUT);
   digitalWrite(relay_pin,Relay_OFF);
    // Just to know which program is running on my Arduino
   // Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

    // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

    Serial.print(F("Ready to receive IR signals of protocols: "));
    // printActiveIRProtocols(&Serial); // Requires additional 318 bytes program memory
    // Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void loop() {
    if (IrReceiver.decode()) {    
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            //Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
            // We have an unknown protocol here, print extended info
            //IrReceiver.printIRResultRawFormatted(&Serial, true);

            IrReceiver.resume(); // Do it here, to preserve raw data for printing with printIRResultRawFormatted()
        } else {
            IrReceiver.resume(); // Early enable receiving of the next IR frame

            // IrReceiver.printIRResultShort(&Serial);   // Requires additional 1436 bytes program memory
            // IrReceiver.printIRSendUsage(&Serial);     // Calls printIRResultShort() and other functions, if protocol is UNKNOWN
        }
        //Serial.println();

         //Finally, check the received data and perform actions according to the received command
         
        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
            //Serial.println(F("Repeat received. Here you can repeat the same action as before."));
        } 
        else {
          curr_time = millis();                      
            if (IrReceiver.decodedIRData.command == 0x1) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("A"));
                lcd.setCursor(8,1); //8+i adjusts cursor accordingly to number of inputs already received from user 
                entered=entered+"A";
                offed=offed+"A";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }

            } else if (IrReceiver.decodedIRData.command == 0x2) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("B"));
                lcd.setCursor(8,1);
                entered=entered+"B";
                offed=offed+"B";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x3) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("C"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"C";
                offed=offed+"C";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x4) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("D"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"D";
                offed=offed+"D";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x5) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("1"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"1";
                offed=offed+"1";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x6) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("2"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"2";
                offed=offed+"2";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x7) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("3"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"3";
                offed=offed+"3";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x8) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("4"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"4";
                offed=offed+"4";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x9) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("5"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"5";
                offed=offed+"5";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xA) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("6"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"6";
                offed=offed+"6";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xB) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("7"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"7";
                offed=offed+"7";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xC) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("8"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"8";
                offed=offed+"8";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xD) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("9"));
                lcd.setCursor(8,1);
                
                // do something else
                entered=entered+"9";
                offed=offed+"9";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xE) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("0"));
                lcd.setCursor(8,1);
                // do something else
                entered=entered+"0";
                offed=offed+"0";
                lcd.print(offed);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }    
        
          if (IrReceiver.decodedIRData.command == 0xF) { // "Strobe" button acts as Enter.
            if (curr_time-prev_time>=delay_time){
              if (pass==entered){
                lcd.setCursor(7, 0);
                lcd.print("ON      "); //space to remove 'F' from 'OFF'               
                digitalWrite(relay_pin,Relay_ON);
                Serial.println("Relay turned ON");
                Serial.println(entered);
                }
              if(offed==off){
                digitalWrite(relay_pin,Relay_OFF);
                Serial.println("Relay turned OFF");
                Serial.println(offed);
                lcd.setCursor(7, 0);
                lcd.print("OFF     ");
                }           
              if (pass!=entered && offed!=off){
                Serial.println("Wrong Password!");
                lcd.setCursor(7, 0);
                lcd.print("RE-ENTER");
                }
              lcd.setCursor(8, 1);
              lcd.print("        ");  
              entered="";
              offed="";
              prev_time=curr_time;
              IrReceiver.resume();
            }
          }
        }        
    }
}