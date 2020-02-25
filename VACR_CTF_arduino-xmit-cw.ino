/*
 VACR_CTF_arduino-xmit-cw
 Arduino xmitting Morse Code via RF
 By T.weeks@vt.edu, 2020-02-22 v0.16
 Based on TRANSMIT_CW by Monta Elkins 
 @ FoxGuard Solutions, 7/11/2018 V:0.14
 For Adduino UNO
    good square wave up to 2mhz (but quantitization steps at those frequencies is very large)
    disabled LED output
    Free for any use 
*/

// This is the message this program transmits continuously
//    only A-Z 0-9
//--------------------------------------------------------
//String messageToMorse ="CQ KF4ZJD";
//String messageToMorse ="CQ Password is DRTHVDR   ";
String messageToMorse ="  THE  FLAG  IS  X Y Z ";

// cwFast uses pins 9 & 10 for RF output defined by library
#define speakerPin 5       // hook a speaker here if you want to hear the transmission
#define RFFreq 1500000     // reasonable squarewave up to 2Mhz
                           // BTW 2,000,000 is 2.66 mhz
                           //  1,500,000 is 2.01Mhz
                           //  57150 is 58.1 khz
                           //  57100 is 57.5 khz
//#define dit 75 // all symbols are defined as multiples of dit
#define dit 200 // 200 ~ 6wpm  (nice and slow)
#define dah 3*dit
#define intraLetterSpace 1*dit
#define interLetterSpace (2)*dit  // 3
#define interWordSpace (4)*dit    //7 
#define toneFreq 1000   // Speaker frequency


#include <toneAC.h>  // this is for higher frequencies than the built-in tone command (with max of 65535 hz)
// Note on UNO toneAC uses (differential) pins 9 & 10
//    uses differnet pins on different Arduinos


const String PROGMEM morseCodeLetterTable[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
// Digits 0-9
const String PROGMEM morseCodeDigitTable[] = {"-----", ".----", "..---", "...--", "....-", ".....","-....", "--...", "---..", "----."};



// ------------------------------------------------------
void setup() {
  // initialize LED_BUILTIN as an output.
  pinMode(speakerPin,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);  // built-in led
  pinMode (9,OUTPUT);  // GND for continious operation - read by cwPin 12
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);  // pull high 
   
  Serial.begin(115200);
  Serial.println("Transmit CW version .16");
  Serial.println("  by Monta Elkins, FoxGuard Solutions");
  Serial.print("      connect RF wire to pin 9");
  Serial.println(); 
}

long b;
unsigned long timer;
unsigned long timer2;


//---------------------------------------------------------------------------------------
void loop() {
  
  morseAString(messageToMorse);
 
  
  if (digitalRead(10)==LOW) {
   //allows a jumper between pins 9 & 10 to put this into continuous RF transmit carrier mode
   continious(); 
  }

}

//-----------------------------------------------------------------------------------------

void morseAString(String message) {
  
  message.toUpperCase();
  int messageLength = message.length();
  int i=0;
  
  while (i< messageLength) {
    //Serial.print(i);
    //Serial.println(message[i]);
    
    if (message[i]==' ') {
      // this is a space so just interWordSpace delay
      delay(interWordSpace);
      Serial.print("SPACE CHAR ");
      Serial.println("interWordSpace");
    }
    else {
        //transmit the char
         morseAChar(message[i]);
    }
       
    i++;
  }
  delay(interWordSpace);
  Serial.println("interWordSpace");
}

void morseAChar(char aLetter) {
  String  morseCodeLetter=asciiCharToMorseCode(aLetter);
  int symbolLength= morseCodeLetter.length();
  int i=0;
  while (i < symbolLength) {
  if (morseCodeLetter.substring(i,(i+1)) == ".") {
    cwFast(dit);
  }
  else {
    cwFast(dah);
  }
  i++;
  }
  Serial.println();
 
  delay(interLetterSpace);
  //Serial.println("interLetterSpace");
}
   

String  asciiCharToMorseCode(char asciiLetter) {
    String morseCodeLetter;
    if ((asciiLetter>=48) && (asciiLetter<=57)) {
       //it's a digit
       morseCodeLetter=morseCodeDigitTable[ asciiLetter - 48];
       Serial.print("DIGIT: ");
       Serial.println(asciiLetter);
       return morseCodeLetter;
    }
    
    if ((asciiLetter>=65) && (asciiLetter<=90)) {
        // it's an upper case letter
       morseCodeLetter=morseCodeLetterTable[ asciiLetter - 65];
       //Serial.println(asciiLetter-65);
       Serial.println(asciiLetter);
       return morseCodeLetter;
    }
    
    // doens't fit something I can transmit by Morse
    Serial.print("Invalid Char:");
    Serial.println(asciiLetter);
    return "";
}


void cwFast(long didah) {  // didah contains length of dit or dah in ms
  //digitalWrite(LED_BUILTIN,HIGH);  // comment out this line to stop LED from blinking morse for CTF
  tone(speakerPin,toneFreq);      //audible output if speaker connected (disable for CTF?)
  toneAC(RFFreq);                 // RF output]
  
  delay(didah);
  
  noToneAC();
  digitalWrite(LED_BUILTIN,LOW);
  noTone(speakerPin);
  
  if (didah == dit) {
    Serial.print(" dit ");
  }
  else {
    Serial.print(" dah ");
  }
  
  delay(intraLetterSpace);  
  //Serial.print("intraLetterSpace");  
}


void continious() {
  // Just send out the RF carrier wave --
  //digitalWrite(LED_BUILTIN,HIGH);

  
  toneAC(RFFreq);                 // RF output
  delay(1000);                    // 1 second intervals
  noToneAC();
  
  //digitalWrite(LED_BUILTIN,LOW);

  
  
}

