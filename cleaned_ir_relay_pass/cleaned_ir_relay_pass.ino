//WORKS!!

#include <Arduino.h>
/*
 * Specify which protocol(s) should be used for decoding.
 * If no protocol is defined, all protocols (except BEO / Bang&Olufsen) are active.
 * This must be done before the #include <IRremote.hpp>
 * In alphabetic order
 */
//#define DECODE_DENON        // Includes Sharp - requires around 250 bytes of program memory on ATmega328
//#define DECODE_JVC          // ~ 200 bytes
//#define DECODE_KASEIKYO     // Includes Panasonic ~ 300 bytes
//#define DECODE_LG           // ~ 400 bytes
//#define DECODE_NEC          // Includes Apple and Onkyo ~ 250 bytes
//#define DECODE_SAMSUNG      // ~ 300 bytes
//#define DECODE_SONY         // ~ 175 bytes
//#define DECODE_RC5          // RC5 + MARANTZ: ~ 425 bytes
//#define DECODE_RC6          // ~ 375 bytes

// Universal protocol decoder
//#define DECODE_DISTANCE_WIDTH // Universal decoder for pulse distance width protocols ~ 2275 bytes
//#define DECODE_HASH         // special decoder for all protocols ~ 250 bytes

// Exotic protocol decoder
//#define DECODE_BOSEWAVE     // ~ 140 bytes
//#define DECODE_FAST         // ~ 135 bytes
//#define DECODE_LEGO_PF      // ~ 300 bytes
//#define DECODE_MAGIQUEST    // ~ 270 bytes
//#define DECODE_MARANTZ      // RC5 + MARANTZ: ~ 425 bytes
//#define DECODE_OPENLASIR    // Modified NEC with 8-bit validated address + 16-bit command. ~ 175 bytes
//#define DECODE_WHYNTER      // ~ 90 bytes

//#define DECODE_BEO          // This protocol must always be enabled manually, i.e. it is NOT enabled if no protocol is defined. It prevents decoding of SONY! ~ 430 bytes

//#define DEBUG               // Activate this for lots of lovely debug output from the decoders.

//#define RAW_BUFFER_LENGTH  750 // For air condition remotes it may require up to 750. Default is 200.

//adding LCD

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Adding millis to code (check if cause timing problems)
byte delay_time=50;
unsigned long curr_time=0;
unsigned long prev_time=0;

//RELAY controlled by IR remote (My Relay Module is Active Low)
#define Relay_ON LOW
#define Relay_OFF HIGH
byte relay_pin=8;

//password
String pass="ABCD";  //ON
String off="1234";   //OFF
String entered="";   //STORES USER INPUT


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
    // pinMode(bl, OUTPUT); use PWM for dimming or external resistor (NOT FOR ONES WITH I2C)
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
          //used IrReceiver.resume(); after every data received and processed to free up the buffer and activate receiver
          //"entered" variable stores user input and has no length limit,so enter button created.                    
            if (IrReceiver.decodedIRData.command == 0x1) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("A"));
                lcd.setCursor(8,1); //8+i adjusts cursor accordingly to number of inputs already received from user 
                // do something else
                entered=entered+"A";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }

            } else if (IrReceiver.decodedIRData.command == 0x2) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("B"));
                lcd.setCursor(8,1);

                entered=entered+"B";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x3) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("C"));
                lcd.setCursor(8,1);
                
                entered=entered+"C";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x4) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("D"));
                lcd.setCursor(8,1);
                
                entered=entered+"D";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x5) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("1"));
                lcd.setCursor(8,1);
                
                entered=entered+"1";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x6) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("2"));
                lcd.setCursor(8,1);
                
                entered=entered+"2";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x7) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("3"));
                lcd.setCursor(8,1);
                
                entered=entered+"3";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x8) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("4"));
                lcd.setCursor(8,1);
                               
                entered=entered+"4";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0x9) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("5"));
                lcd.setCursor(8,1);
                               
                entered=entered+"5";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xA) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("6"));
                lcd.setCursor(8,1);
                               
                entered=entered+"6";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xB) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("7"));
                lcd.setCursor(8,1);
                              
                entered=entered+"7";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xC) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("8"));
                lcd.setCursor(8,1);
                
                entered=entered+"8";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xD) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("9"));
                lcd.setCursor(8,1);
                
                
                entered=entered+"9";
                lcd.print(entered);
                prev_time=curr_time;
                IrReceiver.resume();
                }
            }
            else if (IrReceiver.decodedIRData.command == 0xE) {
                if (curr_time-prev_time>=delay_time){
                Serial.println(F("0"));
                lcd.setCursor(8,1);
                
                entered=entered+"0";
                lcd.print(entered);
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
              if(entered==off){
                digitalWrite(relay_pin,Relay_OFF);
                Serial.println("Relay turned OFF");
                Serial.println(entered);
                lcd.setCursor(7, 0);
                lcd.print("OFF     ");
                }           
              if (pass!=entered && off!=entered){
                Serial.println("Wrong Password!");
                lcd.setCursor(7, 0);
                lcd.print("RE-ENTER");
                }
              lcd.setCursor(8, 1);
              lcd.print("        ");  
              entered="";
              prev_time=curr_time;
              IrReceiver.resume();
            }
          }
        }        
    }
}