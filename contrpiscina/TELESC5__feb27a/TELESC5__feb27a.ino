




#include <toneAC.h>
unsigned long freqh = 30000; //maxima frequencia de aceleração
int Dir = 2;                // pino saida direção
 long freq ;          // frequenia saida
long freqs = freq;
long freqCentral;
int joyst_map =0;
 #define rampadeaceleracao  1
 #define rampadedesaceleracao  0   

 



//////////////EEPROM
 #include <EEPROM.h>
 //int addr = 0;    // endereço de escrita na memória eeprom
int pulsosporseg;

/////////////LCD
 #include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

unsigned long tilcd = 0;
unsigned long tf = 0;
int tdiflcd = 500;   //taxa de atualização LCD milisegundos
int freqsLCD = 0;
int contlcd = 0;


/////////////////////////////////////Botão:
// constants won't change. They're used here to set pin numbers:
const int buttonPin = 8;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
bool lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
int debounceDelay = 50;    // the debounce time; increase if the output flickers
/////////////////////////////////////////

/////
int menuState = HIGH;         // the current state of the output pin
//int buttonState;             // the current reading from the input pin
bool lastMenuState = HIGH;   // the previous reading from the input pin
unsigned long lastDebounceTimeMenu = 0;  // the last time the output pin was toggled
int menuDebounceDelay = 4000;    // the debounce time; increase if the output flickers
int ultimoestadobotoes = 0;
unsigned long whilelastTime = 0;
int whilebuttonState = 0;


/////////////Menu
static unsigned long tpmenu;
bool tempomenu;
bool chamadamenu = LOW;
int tempodemenu = 5000;
int mudancaLCD;
bool botoes;
unsigned long previousMillis;
int interval = 300;
int contador = 0;
unsigned long TempoEntraMenu = 0;
bool entrarMenu = LOW;
bool entrandoMenu = LOW;
int buttonPushCounter = 0;   //contador da repetição do menu
unsigned long tempoSairMenuMillis = 0;






void setup() {

//////////////////////////////Botão:
 pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  // set initial LED state
  digitalWrite(ledPin, ledState);
//////////////////////////////////////////// 
  
 //EEPROM.put(0,6411);

 pulsosporseg = EEPROM.read(0);
 freqCentral = pulsosporseg;
 
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("FOGGIATTO");// mensagem inicial
  lcd.setCursor(2,1);
  lcd.print(pulsosporseg);
  lcd.setCursor(0,2);
    delay(2000);// tempo mensagem inicial
  
pinMode(Dir, OUTPUT);
digitalWrite(Dir, HIGH);

Serial.begin(9600);


//tpmenu = millis();
}


void loop() {

///////////////////BOTÂO
controle_led_botao();
//////////////



/////////Map joistik
joyst_map = map (analogRead(A0),0, 1023, -6, 7);
//Serial.print(joyst_map);
//Serial.print("   freq");
//Serial.println(freqs);
//Serial.print("   ");





/////////////Menu

if (buttonState != lastMenuState) {
lastDebounceTimeMenu = millis();
}

if ((millis() - lastDebounceTimeMenu) >3000) {// menuDebounceDelay
       if (buttonState != menuState) {
       menuState = buttonState ;
           //Serial.println(menuState);
       }
}
digitalWrite(ledPin, menuState);
lastMenuState = buttonState;

chamadamenu = menuState;





  
  if (chamadamenu != mudancaLCD){
      lcd.clear();
      mudancaLCD = chamadamenu;
      contador = -1;
      }
  

Serial.println(contador);

//====================================WHILE============================================
  
while     (chamadamenu == HIGH){
  joyst_map = map (analogRead(A0),0, 1023, -6, 7);
 // Serial.println("while");
controle_led_botao();
//Serial.println(joyst_map);
if (buttonState==HIGH || joyst_map !=0 ) {
  botoes= HIGH;
  tempoSairMenuMillis = millis();
       }else{ 
      botoes= LOW;
      }
        // Serial.print("botoes ");
       //  Serial.println(botoes); 
       //  Serial.print("ultimoestadobotoes ");  
       //  Serial.println(ultimoestadobotoes);
       //  Serial.print("mullis ");
       //  Serial.println(millis());
       //  Serial.print("whilasttime ");   
       //  Serial.println(whilelastTime);
  if ((botoes != ultimoestadobotoes)  || (millis() - whilelastTime > 1000 ) ) {
     
      
  

             if (botoes == HIGH)  {
                    lcd.clear();
                    buttonPushCounter++;// if the current state is HIGH then the button went from off to on:
                    Serial.println("on");Serial.println("on");
                    Serial.print("number of button pushes: ");
                     Serial.println(buttonPushCounter);
                     Serial.println(joyst_map);
                     
                         if (buttonPushCounter > 1) {
                            whilelastTime = millis()  - (buttonPushCounter * 100) ;  //              
                              } else whilelastTime = millis();
         








    

    
    if (buttonState == HIGH){
        contador = contador + 1;
        lcd.clear();
         }
        
    if (contador > 1)    {
      contador = 0;
      }
       



switch (contador){
      
   case 0:
        if (joyst_map > 0){
          if (joyst_map > 5){ 
            pulsosporseg = pulsosporseg + joyst_map;
            }else {
              pulsosporseg = pulsosporseg + 1;
              }
        }   
       if (joyst_map < 0){
        if (joyst_map < -5){
          pulsosporseg = pulsosporseg + joyst_map;
       }else{pulsosporseg = pulsosporseg - 1;
       }
            }
            
        lcd.setCursor(0, 0);
        lcd.print("Frequencia passos");
        lcd.setCursor(0, 1);
        lcd.print(pulsosporseg);
          lcd.setCursor(7, 1);
          lcd.print("dif: ");   //("(byte)0");
           lcd.setCursor(11, 1);
          lcd.print( pulsosporseg - freqCentral); 
       break; 
       
        
   case 1:
        //if (botaoup == HIGH & settemperaturaacionbomba1 <= 100){
         //   settemperaturaacionbomba1 = settemperaturaacionbomba1 + 1;
        //    }
      //  if (botaodw == HIGH & settemperaturaacionbomba1 > 0){
       //     settemperaturaacionbomba1 = settemperaturaacionbomba1 - 1;
       //     }
        lcd.setCursor(0, 0);
        lcd.print("2TemperAcionBomba");
        lcd.setCursor(3, 1);
        lcd.print("settemperaturaacionbomba1 /2 ");

            lcd.setCursor(9, 1);
            lcd.write("(byte)0");

       break;

default:
        contador = 0;
    }
  //  return;
   
 

} else {
           buttonPushCounter = 0;
            // Serial.println("off");// if the current state is LOW then the button went from on to off:
           }

// if (botoes == LOW) 
  
 
  
  
  }

ultimoestadobotoes = botoes ; 



if (millis() - tempoSairMenuMillis > 8000 ) {

chamadamenu = LOW;
 
}

  freqsLCD = 0;
toneAC(pulsosporseg);
  
   }   //fim do while


//==================================================================================================================

// read the input on analog pin 0:
 // int sensorValue = analogRead(A0);
  // print out the value you read:
  //Serial.println(sensorValue);
  //delay(1);        // delay in between reads for stability


if (pulsosporseg != freqCentral){
  EEPROM.write(0, pulsosporseg);
  freqCentral = pulsosporseg;
                      Serial.print("                    EEPROM UPDATE: ");
                     Serial.println(pulsosporseg);
  }




if  ((joyst_map != 0)  & (freqs<freqh)){

      if  (joyst_map > 0 ) {    
       //delayMicroseconds(1);     // Wait 1 ms so you can hear it.
      freq = freq+ (joyst_map*rampadeaceleracao);
        }
     else{  
      freq = freq+(joyst_map*rampadeaceleracao);
      }
}
  else {    
  if  ( freq > freqCentral) {  
   freq = freq-rampadedesaceleracao;
   freq = freq-1;
 }else {
  freq+freq+1;
  }
 
 if  ( freq < freqCentral) {  
   freq = freq+rampadedesaceleracao;
 }else {
  freq+freq-1;
  }  
  }
  
  

//}
if (freq<0){
  digitalWrite(Dir, LOW);
  freqs=(-1)*freq;
  }
else{
  digitalWrite(Dir, HIGH);
  
  freqs=freq;
  }
 
//toneAC(freqs); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).

if (ledState == HIGH) {
        
    
toneAC(freqs); // Play the frequency (150 Hz to 15 kHz in 10 Hz steps).
 }
 else{toneAC();
 }



///////LCD tempo
if ((millis() - tilcd > 200 )&& (freqs != freqsLCD )){  //tdiflcd
 lcd.clear();
 //lcd.autoscroll ();
  lcd.setCursor(0,0);
  lcd.print("FOGGIATTO TELESCOPIO");
  lcd.setCursor(0,1);
  lcd.print("Run");


  lcd.setCursor(4,1);
  lcd.print('>');//("(byte)0");
  lcd.setCursor(11,1);
  lcd.print(freqs);
  tilcd=millis();

 if  (joyst_map = 1 ) {    
      
      contlcd = contlcd++; 
            lcd.setCursor(4,1);
             lcd.print("> > >");//("(byte)0");
      
        }












  
  freqsLCD = freqs;
}
}
//}




////////////////////////Função botão
void controle_led_botao(){
   // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      //if (buttonState == HIGH) {
      //  ledState = !ledState;
      //}
    }
  }

  // set the LED:
  //digitalWrite(ledPin, buttonState);

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  
  
  }
