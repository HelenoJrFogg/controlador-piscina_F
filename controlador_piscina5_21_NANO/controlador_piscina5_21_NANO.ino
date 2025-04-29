

//*************************************************************************************//
/*
Heleno Junior FOGGIATTO
hjfsmo@gmail.com
                                                                                  */
////ARDUINO NANO///
//incluide <Arduino.h> 
#include <EEPROM.h>


//////////////////////Sensores
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS_PISC         A3        // Pino do sensor da temperatura da piscina
#define ONE_WIRE_BUS_PAINEL       5         // Pino do sensor do painel de aquecimento
#define ONE_WIRE_BUS_RETORNO      4         // Pino sensor de retorno de agua
OneWire SensorPiscina(ONE_WIRE_BUS_PISC);
OneWire oneWire_out(ONE_WIRE_BUS_PAINEL);
OneWire oneWire_out_1(ONE_WIRE_BUS_RETORNO);
DallasTemperature sensor_piscina(&SensorPiscina);
DallasTemperature sensor_painel(&oneWire_out);
DallasTemperature sensor_retorno(&oneWire_out_1);

#define beepPin 6

/////////////////////////////////////Botões:

const int ledPin = 13;      // the number of the LED pin
int ledState = HIGH;         // the current state of the output pin

//int analogreading;
int debounceDelay = 50;    // the debounce time; increase if the output flickers

int buttonPinSet = 2;    // the number of the pushbutton pin
int buttonStateSet;             // the current reading from the input pin
bool lastButtonStateSet = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTimeSet = 0;  // the last time the output pin was toggled

int buttonPinUp = 3;    // the number of the pushbutton pin
int buttonStateUp;             // the current reading from the input pin
bool lastButtonStateUp = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTimeUp = 0;  // the last time the output pin was toggled

 int buttonPinDw = 12;    // the number of the pushbutton pin
int buttonStateDw;             // the current reading from the input pin
bool lastButtonStateDw = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTimeDw = 0;  // the last time the output pin was toggled
/////////////////////////////////////////////////////////////////////////////////////////////
//unsigned long difmillis =0;


   //bool chamarMenu = 0;
   unsigned long tempochamarmenuTimer = 0;
   //bool estadochamarmenu;
   bool estadochamarmenuTimer;
   //unsigned long lastDebounceTimeMenu = 0;
   bool mudancaLCD;
   unsigned long tempomenu;
   bool botoes = LOW;
   int buttonPushCounter = 0;
   unsigned long whilelastTime = 0;
   bool ultimoestadobotoes ;
  //int temporizador;
  

   
//LCD...

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);
//LiquidCrystal_I2C lcd(0x27,20,4);


//Array simbolo grau
byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};


bool memupdate = LOW ;
//1
int SetTemperPiscina;
float SetTemperPiscFloat;
int TemperPiscEEPROM;
//2
bool SetAquecimentoAutomatico;
bool SetAquecimentoAutomaticoEEPROM;
//3
int SetTempoTimerdiario;
//float SetTempoTimerdiarioFloat;
int SetTempoTimerdiarioEEPROM;
//5
int SetTempInPainel;
float SetTempInPainelFloat;
int SetTempInPainelEEPROM;
//6
int SetDifTempEntrSaida;
float SetDifTemperEntrSaidaFloat;
int DifTemperEntrSaidaEEPROM;
//7
int SetTemperSuperAq;
float SetTemperSuperAqfloat;
int SetTemperSuperAqEEPROM;
//8
int SetTemperDegelo;
float SetTemperDegeloFloat;
int SetTemperDegeloEEPROM;
//9
int SetTempoAcionBomba;
float SetTempoAcionBombaFloat;
int SetTempoAcionBombaEEPROM;
//10
int SetTempoBombaDesl;
float SetTempoBombaDeslFloat;
int SetTempoBombaDeslEEPROM;
//11
int SetTempoAcionBombaCirc;
//float SetTempoAcionBombaCircFloat;
int SetTempoAcionBombaCircEEPROM;
//12
int SetTempoBombaCircDesl;
//float SetTempoBombaCircDeslFloat;
int SetTempoBombaCircDeslEEPROM;
//13
int SetDifTempEntrSaidabomba2;
float SetDifTemperEntrSaidabomba2Float;
int DifTemperEntrSaidabomba2EEPROM;



#define bomba1       9 // pino acionamento da bomba de aquecimenti lento.
#define bomba2       8 // pino acionamento da bomba de aquecimento rapido.
#define bombafiltro  7 // pino acionamento da bomba de filtragem.


/////////////////////////////////////////


int contador = 0;


boolean chamadamenu = 0;
boolean chamadamenuTimer = 0;


//int segundos, minutos, horas, total, total1;
int segundos, minutos, horas, total;
unsigned long previousMillis;
//const long interval = 800; 

int temperaturapiscina;
int tempersaidaaquecedor;
int temperaturaPainel ;

boolean disparoaquecerpiscina;
boolean difentrsaida;

boolean aquecendo;
boolean aquecendoT;
boolean circulacaodeprotecao = LOW;

unsigned long referenciabasetempo10seg;
unsigned long ultimoreferenciabasetempo10seg = 0;
unsigned long basetempo10seg = 0;
unsigned long basetempo30seg;
int TAcionBomba;
int TIntervBomba;
boolean bomba1_acionada;
unsigned long tbomba;
unsigned long tempobombaacioncircprot; //tempo de acionamento da bomba no acionamento de proteção.
unsigned long tempointervdeprot;       // tempo de intervalo da bomba no acionamento de proteção. 

 //unsigned long tempo;


//bool DisparoProtecao;

unsigned long tempoestabilizacao = 0;
int circularaquecimento;
int ultimoestadocircularaquecimento;
unsigned long tempocirculacaoaquecimento =2;
int circulando = LOW;
int modoteste = 0;
int modotestesaidas ;
int timerregressivo = 0;
int minutostimerregressivo = 0;
unsigned long ultimosminutostimerregressivo = 0;
int ultimoestadotimerregressivo;
int errosensor;
int temperaturabaixapainel = 300;
int tempotimerdiario = 0;
int ultimotimerdiario = 0;
unsigned long tempotemperaturaminimapainel = 0;
bool filtragemdiaria;
bool acionarbombafiltro = LOW;
bool acionamentocircprot = LOW;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void setup(void){

    sensor_piscina.begin();
    sensor_painel.begin();
    sensor_retorno.begin();
    sensor_piscina.setWaitForConversion(false);
    sensor_painel.setWaitForConversion(false);
    sensor_retorno.setWaitForConversion(false);


   pinMode(buttonPinSet, INPUT_PULLUP);
   pinMode(buttonPinUp, INPUT_PULLUP);
   pinMode(buttonPinDw, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPinSet), Fchamadamenu, FALLING);
  attachInterrupt(digitalPinToInterrupt(buttonPinUp), timerminutos, FALLING);
 

  
  pinMode(bomba1, OUTPUT);
  pinMode(bomba2, OUTPUT);
  pinMode(bombafiltro, OUTPUT);
  
  Serial.begin(9600);
  //Serial.println(" ");
  

//EEPROM.begin(50);


     lcd.init();
delay(50);
     lcd.backlight();
       lcd.clear();
       lcd.setCursor(5, 0);
       lcd.print(F("FOGGIATTO"));
       lcd.setCursor(3, 1);
       lcd.print(F("CONTROLADORES"));
       lcd.setCursor(7, 3);
       lcd.print(F("V2.3"));
       delay(2000);
       lcd.clear();
       lcd.createChar(0, grau);
    tone(beepPin, 2800, 800);
  /*
  tone(beepPin, 2000, 400);
  delay(500);
  tone(beepPin, 2200, 400);
  delay(500);
  tone(beepPin, 2300, 400);
  delay(500);
  tone(beepPin, 2400, 400);
  delay(500);
  tone(beepPin, 2500, 400);
  delay(500);

  tone(beepPin, 2600, 400);
  delay(500);
  tone(beepPin, 2700, 400);
  delay(500);
  tone(beepPin, 2800, 400);
  delay(500);

  tone(beepPin, 2900, 400);
  delay(500);
  tone(beepPin, 3000, 400);
  delay(500);
  tone(beepPin, 3100, 400);
  delay(500);
  tone(beepPin, 3200, 400);
  delay(500);
  tone(beepPin, 3300, 400);
  delay(500);
  tone(beepPin, 3400, 400);
  delay(500);
  tone(beepPin, 3500, 400);
  delay(500);
  tone(beepPin, 3600, 400);
  delay(500);
  tone(beepPin, 3700, 400);
*/
  
  TemperPiscEEPROM = EEPROM.read(0);
  SetAquecimentoAutomaticoEEPROM = EEPROM.read(1);
  SetTempoTimerdiarioEEPROM = EEPROM.read(2);
  SetTempInPainelEEPROM = EEPROM.read(4);
  DifTemperEntrSaidaEEPROM = EEPROM.read(5);
  SetTemperSuperAqEEPROM = EEPROM.read(6);
  SetTemperDegeloEEPROM = EEPROM.read(7)- 100;
  SetTempoAcionBombaEEPROM = EEPROM.read(8);
  SetTempoBombaDeslEEPROM = EEPROM.read(9);
  SetTempoAcionBombaCircEEPROM = EEPROM.read(10);
  SetTempoBombaCircDeslEEPROM = EEPROM.read(11);
  DifTemperEntrSaidabomba2EEPROM = EEPROM.read(12);
  
  SetTemperPiscFloat = TemperPiscEEPROM ;
  SetTempInPainelFloat = SetTempInPainelEEPROM;
  SetTempoTimerdiario = SetTempoTimerdiarioEEPROM;
  SetDifTemperEntrSaidaFloat = DifTemperEntrSaidaEEPROM;
  SetTemperSuperAqfloat = SetTemperSuperAqEEPROM;
  SetTemperDegeloFloat = SetTemperDegeloEEPROM;
  SetTempoAcionBombaFloat = SetTempoAcionBombaEEPROM;
  SetTempoBombaDeslFloat = SetTempoBombaDeslEEPROM;
  SetDifTemperEntrSaidabomba2Float = DifTemperEntrSaidabomba2EEPROM;
  //SetTempoAcionBombaCircFloat = SetTempoAcionBombaCircEEPROM;
  //SetTempoBombaCircDeslFloat = SetTempoBombaCircDeslEEPROM;
  

 TAcionBomba = -1 - SetTempoAcionBombaEEPROM;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(void){
 // Serial.println(millis() - previousMillis);
  //previousMillis = millis();  

    sensor_piscina.requestTemperatures();
    sensor_painel.requestTemperatures();
    sensor_retorno.requestTemperatures();


    referenciabasetempo10seg = millis() / 10000;

    if (referenciabasetempo10seg > ultimoreferenciabasetempo10seg || referenciabasetempo10seg < ultimoreferenciabasetempo10seg){
        ultimoreferenciabasetempo10seg = referenciabasetempo10seg;
        basetempo10seg = basetempo10seg + 1;
    }
    basetempo30seg = basetempo10seg / 3;
   


/////////////MenuTimer

timer();


    //leituraanalogbotoes();
    //controle_botaoSet();
    //controle_botaoUp();
    //controle_botaoDw();



/////////////Menu
//Serial.println(tempochamarmenu);

if (buttonStateSet == HIGH){//} && estadochamarmenu == LOW)){  // && (millis()-  tempochamarmenu > 100)) {
//if ((buttonStateSet == HIGH && estadochamarmenu == LOW) && (millis()-  tempochamarmenu > 100)) {
//Serial.println(millis());
chamadamenu = HIGH;
contador = 0;
tone(beepPin, 2700, 800);
} 

    //leituraanalogbotoes();
     controle_botaoSet();
     controle_botaoUp();
     controle_botaoDw();
 
  SetTemperPiscina = TemperPiscEEPROM;
  SetAquecimentoAutomatico = SetAquecimentoAutomaticoEEPROM;
  SetTempoTimerdiario = SetTempoTimerdiarioEEPROM;
  SetTempInPainel = SetTempInPainelEEPROM;
  SetDifTempEntrSaida = DifTemperEntrSaidaEEPROM;
  SetTemperSuperAq = SetTemperSuperAqEEPROM;
  SetTemperDegelo = SetTemperDegeloEEPROM;
  SetTempoAcionBomba = SetTempoAcionBombaEEPROM;
  SetTempoBombaDesl = SetTempoBombaDeslEEPROM;
  SetTempoAcionBombaCirc = SetTempoAcionBombaCircEEPROM;
  SetTempoBombaCircDesl = SetTempoBombaCircDeslEEPROM;
  SetDifTempEntrSaidabomba2 = DifTemperEntrSaidabomba2EEPROM;
  


while   (chamadamenu == HIGH){

    //leituraanalogbotoes();
    controle_botaoSet();
    controle_botaoUp();
    controle_botaoDw();


if ( buttonStateSet == HIGH || buttonStateUp == HIGH || buttonStateDw == HIGH){
       tempomenu = millis();
       botoes = HIGH;
    } else botoes = LOW;


 if (millis() -  tempomenu > 10000) {
    lcd.clear();
  chamadamenu = LOW;
  tempomenu = 0;
 tone(beepPin, 3800, 200);
  
  SetTemperPiscina = SetTemperPiscFloat;
  SetTempInPainel = SetTempInPainelFloat;
  //SetTempoTimerdiario = SetTempoTimerdiarioFloat;
  SetDifTempEntrSaida = SetDifTemperEntrSaidaFloat;
  SetTemperSuperAq = SetTemperSuperAqfloat;
  SetTemperDegelo = SetTemperDegeloFloat;
  SetTempoAcionBomba = SetTempoAcionBombaFloat;
  SetTempoBombaDesl = SetTempoBombaDeslFloat;
  SetDifTempEntrSaidabomba2 = SetDifTemperEntrSaidabomba2Float;
  //SetTempoAcionBombaCirc = SetTempoAcionBombaCircFloat;
  //SetTempoBombaCircDesl = SetTempoBombaCircDeslFloat;
  
     
     atualizaeeprom();//funcao atualiza memoria
     
   //  Serial.println("                                                                                                      atualiza eeprom");
  
    }



if ((botoes != ultimoestadobotoes)  || (millis() - whilelastTime > 500 ) ) {


           if (botoes == HIGH)  {
                    lcd.clear();
                    buttonPushCounter++;// if the current state is HIGH then the button went from off to on:

                     
                         if (buttonPushCounter > 1) {
                            whilelastTime = millis()  - (buttonPushCounter * 100) ;  //              
                              } else whilelastTime = millis();



    
    
    if (buttonStateSet == HIGH){
        contador = contador + 1;
        lcd.clear();
        tone(beepPin, 2700, 80);
         }
        
    if (contador > 14){
      contador = 1;
      tone(beepPin, 2900, 80);
      }
     
      
      
 switch (contador){
      
   case 1:
        if (buttonStateUp == HIGH && SetTemperPiscFloat < 80){
            SetTemperPiscFloat = SetTemperPiscFloat + 1;
            tone(beepPin, 2800, 80);
            }
             
        if (buttonStateDw == HIGH && SetTemperPiscFloat > 40){
            SetTemperPiscFloat = SetTemperPiscFloat - 1;
            tone(beepPin, 2600, 80);
            }
            
        lcd.setCursor(0, 0);
        lcd.print(F("1 Temperatura Maxima"));                    
        lcd.setCursor(0, 1);
        lcd.print(F("   de aquecimento"));                    
        lcd.setCursor(0, 2);
        lcd.print(F("    da Piscina"));
        lcd.setCursor(3, 3);
        lcd.print(SetTemperPiscFloat/2,1);
          lcd.setCursor(7, 3);
          lcd.write((byte)0);
          lcd.print(F("  >  "));
          lcd.print(SetTemperPiscFloat);
       break;

       case 2:
            if (buttonStateUp == HIGH ){
                SetAquecimentoAutomatico = !SetAquecimentoAutomatico;
                //tone(beepPin, 2800, 80);
              }
            
            if (buttonStateDw == HIGH){
                SetAquecimentoAutomatico = !SetAquecimentoAutomatico ;
                }
                lcd.setCursor(0, 0);
                lcd.print(F("2  AQUECIMENTO"));
                lcd.setCursor(0, 1);
                lcd.print(F("MODO Aquecimento"));
                lcd.setCursor(0, 2);
                lcd.print(F(" Automatico"));
                
                if (SetAquecimentoAutomatico == 1){
                  lcd.setCursor(3, 3);
                  lcd.print(F("< LIGADO >"));
                  tone(beepPin, 2800, 80);
                } else {
                  lcd.setCursor(3, 3);
                  lcd.print(F("< DESLIGADO >"));
                  tone(beepPin, 2600, 80);
                }

                
                
                //lcd.setCursor(3, 3);
                //lcd.print(SetDifTemperEntrSaidabomba2Float/10);
                //lcd.setCursor(8, 3);
                //lcd.write((byte)0);
                //lcd.print(">");
                //lcd.print(SetDifTemperEntrSaidabomba2Float);
               break;  


    case 3:
        if (buttonStateUp == HIGH && SetTempoTimerdiario <= 240){
            SetTempoTimerdiario = SetTempoTimerdiario + 5;
            tone(beepPin, 2800, 80);
            }
        if (buttonStateDw == HIGH && SetTempoTimerdiario > 0){
           SetTempoTimerdiario = SetTempoTimerdiario - 5;
           tone(beepPin, 2600, 80);
           }
           lcd.setCursor(0, 0);
           lcd.print(F("3 Tempo TIMER DIARIO"));
            lcd.setCursor(0, 1);
           lcd.print(F("Tempo de Acionamento"));
           lcd.setCursor(0, 2);
           lcd.print(F("da Bomba Filtragem"));
           // lcd.print(SetTemperSuperAqFloat);
           total = SetTempoTimerdiario * 60;
           horas = (total / 3600);
           minutos = ((total - (horas * 3600)) / 60);
           segundos = (total % 60);

              // lcd.setCursor(0, 1);
              // lcd.print(SetTempoAcionBombaFloat);
  if (SetTempoTimerdiario == 0){
    lcd.setCursor(0, 3);
    lcd.print(F("DESLIGADO"));
    } else {
           lcd.setCursor(0, 3);
        if (horas < 10){
          lcd.print("0");
           }
           lcd.print(horas);
           lcd.print(":");
           lcd.setCursor(3, 3);
        if (minutos < 10){
           lcd.print("0");
           }
           lcd.print(minutos);
           lcd.print(":");
           lcd.setCursor(6, 3);
        if (segundos < 10){
            lcd.print("0");
            }
            lcd.print(segundos); 
            lcd.setCursor(9, 3);
            lcd.print(SetTempoTimerdiario);
            lcd.print(" Minutos");
             
          }
          break;



  case 4:
            if (buttonStateUp == HIGH && SetDifTemperEntrSaidabomba2Float <= 99){
              SetDifTemperEntrSaidabomba2Float = SetDifTemperEntrSaidabomba2Float + 1;
              tone(beepPin, 2800, 80);
              }
            
            if (buttonStateDw == HIGH && SetDifTemperEntrSaidabomba2Float > 0){
                SetDifTemperEntrSaidabomba2Float = SetDifTemperEntrSaidabomba2Float - 1;
                tone(beepPin, 2600, 80);
                }
                lcd.setCursor(0, 0);
                lcd.print(F("4 Ganho minimo de"));
                lcd.setCursor(0, 1);
                lcd.print(F("Temperatura de"));
                lcd.setCursor(0, 2);
                lcd.print(F("Acionamento Bomba2"));
                lcd.setCursor(3, 3);
                lcd.print(SetDifTemperEntrSaidabomba2Float/10);
                lcd.setCursor(8, 3);
                lcd.write((byte)0);
                lcd.print(">");
                lcd.print(SetDifTemperEntrSaidabomba2Float);
               break; 


       
   case 5:
        if (buttonStateUp == HIGH && SetTempInPainelFloat < 100){
            SetTempInPainelFloat = SetTempInPainelFloat + 1;
            tone(beepPin, 2800, 80);
            }
             
        if (buttonStateDw == HIGH && SetTempInPainelFloat > 50){
          SetTempInPainelFloat = SetTempInPainelFloat - 1;
          tone(beepPin, 2600, 80);
            }
            
        lcd.setCursor(0, 0);
        lcd.print(F("5 Temperatura Painel"));                    
        lcd.setCursor(0, 1);
        lcd.print(F(" de inicio"));                    
        lcd.setCursor(0, 2);
        lcd.print(F(" do aquecimento"));
        lcd.setCursor(3, 3);
        lcd.print(SetTempInPainelFloat/2,1);
          lcd.setCursor(7, 3);
          lcd.write((byte)0);
          lcd.print(F("  >  "));
          lcd.print(SetTempInPainelFloat);
       break; 

  case 6:
        if (buttonStateUp == HIGH && SetDifTemperEntrSaidaFloat <= 99){
          SetDifTemperEntrSaidaFloat = SetDifTemperEntrSaidaFloat + 1;
          tone(beepPin, 2800, 80);
          }
        
        if (buttonStateDw == HIGH && SetDifTemperEntrSaidaFloat > 0){
            SetDifTemperEntrSaidaFloat = SetDifTemperEntrSaidaFloat - 1;
            tone(beepPin, 2600, 80);
            }
            lcd.setCursor(0, 0);
            lcd.print(F("6 Ganho minimo de"));
            lcd.setCursor(0, 1);
            lcd.print(F("Temperatura do"));
            lcd.setCursor(0, 2);
            lcd.print(F(" Sistema ligado"));
            lcd.setCursor(3, 3);
            lcd.print(SetDifTemperEntrSaidaFloat/10);
            lcd.setCursor(8, 3);
            lcd.write((byte)0);
            lcd.print(">");
            lcd.print(SetDifTemperEntrSaidaFloat);
                      
          break;

        
   case 7:
        if (buttonStateUp == HIGH && SetTemperSuperAqfloat < 140){
            SetTemperSuperAqfloat = SetTemperSuperAqfloat + 1;
            tone(beepPin, 2800, 80);
            }
        if (buttonStateDw == HIGH && SetTemperSuperAqfloat > 100){
            SetTemperSuperAqfloat = SetTemperSuperAqfloat - 1;
            tone(beepPin, 2600, 80);
            }
        lcd.setCursor(0, 0);
        lcd.print(F("7 Temperatura de"));
        lcd.setCursor(0, 1);
        lcd.print(F("acionam. da PROTECAO"));
        lcd.setCursor(0, 2);
        lcd.print(F("por CALOR do painel"));
        lcd.setCursor(3, 3);
        lcd.print(SetTemperSuperAqfloat /2 );

            lcd.setCursor(7, 3);
            lcd.write((byte)0);
            lcd.print(">" );
            lcd.print(SetTemperSuperAqfloat);

       break;


    case 8:
        if (buttonStateUp == HIGH && SetTemperDegeloFloat < 50){
          SetTemperDegeloFloat = SetTemperDegeloFloat + 1;
          tone(beepPin, 2800, 80);          }
        
        if (buttonStateDw == HIGH && SetTemperDegeloFloat > -30){
            SetTemperDegeloFloat = SetTemperDegeloFloat - 1;
            tone(beepPin, 2600, 80);
            }
            lcd.setCursor(0, 0);
            lcd.print(F("8 Temperatura Protec"));
            lcd.setCursor(0, 1);
            lcd.print(F("de ANTICONGELAMENTO"));
            lcd.setCursor(0, 2);
            lcd.print(F(" do Painel"));
            lcd.setCursor(5, 3);
            lcd.print((SetTemperDegeloFloat/10) );//-10);
            lcd.setCursor(10, 3);
            lcd.write((byte)0);
            lcd.print(">");
            lcd.print(SetTemperDegeloFloat);
        break;

  

        
    case 9:
        if (buttonStateUp == HIGH && SetTempoAcionBombaFloat <= 80){
            SetTempoAcionBombaFloat = SetTempoAcionBombaFloat + 1;
            tone(beepPin, 2800, 80);
            }
        if (buttonStateDw == HIGH && SetTempoAcionBombaFloat > 0){
           SetTempoAcionBombaFloat = SetTempoAcionBombaFloat - 1;
           tone(beepPin, 2600, 80);
           }
           lcd.setCursor(0, 0);
           lcd.print(F("9 Tempo de Acionamen"));
            lcd.setCursor(0, 1);
           lcd.print(F("to da Bomba do"));
           lcd.setCursor(0, 2);
           lcd.print(F("ciclo de Protecao"));
           // lcd.print(SetTemperSuperAqFloat);
           total = SetTempoAcionBombaFloat * 10;
           horas = (total / 3600);
           minutos = ((total - (horas * 3600)) / 60);
           segundos = (total % 60);

              // lcd.setCursor(0, 1);
              // lcd.print(SetTempoAcionBombaFloat);

           lcd.setCursor(2, 3);
        if (horas < 10){
          lcd.print("0");
           }
           lcd.print(horas);
           lcd.print(":");
           lcd.setCursor(5, 3);
        if (minutos < 10){
           lcd.print("0");
           }
           lcd.print(minutos);
           lcd.print(":");
           lcd.setCursor(8, 3);
        if (segundos < 10){
            lcd.print("0");
            }
            lcd.print(segundos); 
lcd.print(">");
lcd.print(SetTempoAcionBombaFloat);
            
          break;
          
    
     case 10:       
        if (buttonStateUp == HIGH && SetTempoBombaDeslFloat <= 239){
            SetTempoBombaDeslFloat = SetTempoBombaDeslFloat + 1;
            tone(beepPin, 2800, 80);
            }
        if (buttonStateDw == HIGH && SetTempoBombaDeslFloat > 0){
           SetTempoBombaDeslFloat = SetTempoBombaDeslFloat - 1;
           tone(beepPin, 2600, 80);
           }
           lcd.setCursor(0, 0);
           lcd.print(F("10 Tempo de intervalo"));
           lcd.setCursor(0, 1);
           lcd.print(F("de Bomba desligada"));
           lcd.setCursor(1, 2);
           lcd.print(F("do ciclo d protecao"));
           // lcd.print(SetTemperSuperAqFloat);
           total = SetTempoBombaDeslFloat * 30;
           horas = (total / 3600);
           minutos = ((total - (horas * 3600)) / 60);
           segundos = (total % 60);
           
           lcd.setCursor(2, 3);
        if (horas < 10){
          lcd.print("0");
           }
           lcd.print(horas);
           lcd.print(":");
           lcd.setCursor(5, 3);
        if (minutos < 10){
           lcd.print("0");
           }
           lcd.print(minutos);
           lcd.print(":");
           lcd.setCursor(8, 3);
        if (segundos < 10){
            lcd.print("0");
            }
            lcd.print(segundos);
            lcd.print(">");
            lcd.print(SetTempoBombaDeslFloat);
          break;

        
       case 11:
          if (buttonStateUp == HIGH && SetTempoAcionBombaCirc < 240){
              SetTempoAcionBombaCirc = SetTempoAcionBombaCirc + 1;
              tone(beepPin, 2800, 80);
              }
          if (buttonStateDw == HIGH && SetTempoAcionBombaCirc > 0){
             SetTempoAcionBombaCirc = SetTempoAcionBombaCirc - 1;
             tone(beepPin, 2600, 80);
             }
             lcd.setCursor(0, 0);
             lcd.print(F("11 Tempo de Acionamen"));
              lcd.setCursor(0, 1);
             lcd.print(F("Bomba de filtragem"));
             lcd.setCursor(0, 2);
             lcd.print(F("ciclo de circulacao"));
             // lcd.print(SetTemperSuperAqFloat);
             total = SetTempoAcionBombaCirc * 30;
             horas = (total / 3600);
             minutos = ((total - (horas * 3600)) / 60);
             segundos = (total % 60);
  
                // lcd.setCursor(0, 1);
                // lcd.print(SetTempoAcionBombaFloat);
  
             lcd.setCursor(2, 3);
          if (horas < 10){
            lcd.print("0");
             }
             lcd.print(horas);
             lcd.print(":");
             lcd.setCursor(5, 3);
          if (minutos < 10){
             lcd.print("0");
             }
             lcd.print(minutos);
             lcd.print(":");
             lcd.setCursor(8, 3);
          if (segundos < 10){
              lcd.print("0");
              }
              lcd.print(segundos); 
  lcd.print(">");
  lcd.print(SetTempoAcionBombaCirc);
              
            break;
            
      
       case 12:       
          if (buttonStateUp == HIGH && SetTempoBombaCircDesl < 240){
              SetTempoBombaCircDesl = SetTempoBombaCircDesl + 1;
              tone(beepPin, 2800, 80);
              }
          if (buttonStateDw == HIGH && SetTempoBombaCircDesl > 0){
             SetTempoBombaCircDesl = SetTempoBombaCircDesl - 1;
             tone(beepPin, 2600, 80);
             }
             lcd.setCursor(0, 0);
             lcd.print(F("12 Tempo de intervalo"));
             lcd.setCursor(0, 1);
             lcd.print(F("de Bomba desligada"));
             lcd.setCursor(1, 2);
             lcd.print(F("do ciclo d circulacao"));
             // lcd.print(SetTemperSuperAqFloat);
             total = SetTempoBombaCircDesl * 30;
             horas = (total / 3600);
             minutos = ((total - (horas * 3600)) / 60);
             segundos = (total % 60);
             
             lcd.setCursor(2, 3);
          if (horas < 10){
            lcd.print("0");
             }
             lcd.print(horas);
             lcd.print(":");
             lcd.setCursor(5, 3);
          if (minutos < 10){
             lcd.print("0");
             }
             lcd.print(minutos);
             lcd.print(":");
             lcd.setCursor(8, 3);
          if (segundos < 10){
              lcd.print("0");
              }
              lcd.print(segundos);
              lcd.print(">");
              lcd.print(SetTempoBombaCircDesl);
            break;

       case 13:
            if (buttonStateUp == HIGH && SetDifTemperEntrSaidabomba2Float <= 99){
              SetDifTemperEntrSaidabomba2Float = SetDifTemperEntrSaidabomba2Float + 1;
              tone(beepPin, 2800, 80);
              }
            
            if (buttonStateDw == HIGH && SetDifTemperEntrSaidabomba2Float > 0){
                SetDifTemperEntrSaidabomba2Float = SetDifTemperEntrSaidabomba2Float - 1;
                tone(beepPin, 2600, 80);
                }
                lcd.setCursor(0, 0);
                lcd.print(F("13 Ganho minimo de"));
                lcd.setCursor(0, 1);
                lcd.print(F("Temperatura de"));
                lcd.setCursor(0, 2);
                lcd.print(F(" Acion. Bomba2"));
                lcd.setCursor(3, 3);
                lcd.print(SetDifTemperEntrSaidabomba2Float/10);
                lcd.setCursor(8, 3);
                lcd.write((byte)0);
                lcd.print(">");
                lcd.print(SetDifTemperEntrSaidabomba2Float);
               break; 

       case 14:
             //lcd.clear();
             lcd.setCursor(0, 0);
             lcd.print(F("14 Entrar no MODO"));
             lcd.setCursor(0, 1);
             lcd.print(F("de TESTE das Saidas"));
             lcd.setCursor(1, 3);
             lcd.print(F("ACEITAR: tecla >"));

             
             if (buttonStateUp == HIGH ){
                 modotestesaidas = HIGH;
                 //Serial.print("                                                                                      MODOTESTESAIDAS");
                 //Serial.println(buttonStateUp);
                }
             bool saidab1 = LOW;
             bool saidab2 = LOW;
             bool saidaf = LOW;

         while (modotestesaidas ==HIGH){
           
            //leituraanalogbotoes();
            //controle_botaoSet();
            //controle_botaoUp();
            controle_botaoDw();


            if ( buttonStateSet == HIGH || buttonStateUp == HIGH || buttonStateDw == HIGH){
              //tempomenu = millis();
              botoes = HIGH;
           } else botoes = LOW;


           if ((botoes != ultimoestadobotoes)  || (millis() - whilelastTime > 500 ) ) {


            if (botoes == HIGH)  {
                    // lcd.clear();
                     buttonPushCounter++;// if the current state is HIGH then the button went from off to on:
              
                          if (buttonPushCounter > 1) {
                             whilelastTime = millis()  - (buttonPushCounter * 100) ;  //              
                               } else whilelastTime = millis();
 
 

            
            if (buttonStateUp == HIGH && buttonStateSet == LOW){
                modoteste = modoteste + 1;
                tone(beepPin, 2800, 80);
                }  

              if (modoteste > 3){
                  modoteste = 1;
                }
   
             
        switch (modoteste)
         {
         case 1:
             lcd.setCursor(0, 0);
             lcd.print(F("1 Bomba Aquecimento"));
             lcd.setCursor(0, 1);
             lcd.print(F("Lig/Desl: Tecla SET"));
             lcd.setCursor(1, 2);
             lcd.print(F("Sair: Tecla <"));

             if (buttonStateSet == HIGH){
              saidab1 = !saidab1;
              tone(beepPin, 2800, 80);
              }


              if (saidab1 == HIGH){
                lcd.setCursor(0, 3);
                lcd.print(F("Bomba Aquec. Ligada"));
                digitalWrite(bomba1, HIGH);
                } else  {
                  lcd.setCursor(0, 3);
                  lcd.print(F("Bomba Aq. Desligada"));
                  digitalWrite(bomba1, LOW);
                } 
                break;
          case 2:
              lcd.setCursor(0, 0);
              lcd.print(F("2 Bomba Aquecimento2"));
              //lcd.setCursor(0, 1);
              //lcd.print("Lig/Desl: Tecla SET");
              //lcd.setCursor(1, 2);
              //lcd.print("Sair: Tecla <");

              if (buttonStateSet == HIGH){
                saidab2 = !saidab2;
                tone(beepPin, 2800, 80);
                }


                if (saidab2 == HIGH){
                  lcd.setCursor(0, 3);
                  lcd.print(F("Bomba Aq2 Ligada   "));
                  digitalWrite(bomba2, HIGH);
                  
                  } else  {
                    lcd.setCursor(0, 3);
                    lcd.print(F("Bomba Aq2 Desligada"));
                    digitalWrite(bomba2, LOW);
                  }
                  break;
     
      case 3:
          lcd.setCursor(0, 0);
          lcd.print(F("3 Bomba de Filtragem"));
          //lcd.setCursor(0, 1);
          //lcd.print("Lig/Desl: Tecla SET");
          //lcd.setCursor(1, 2);
          //lcd.print("Sair: Tecla <");
          

          if (buttonStateSet == HIGH){
            saidaf = !saidaf;
            tone(beepPin, 3700, 100);
            }


            if (saidaf == HIGH){
              lcd.setCursor(0, 3);
              lcd.print(F("Bomba Filtro Ligada "));
              digitalWrite(bombafiltro, HIGH);
              
              
              } else  {
                lcd.setCursor(0, 3);
                lcd.print(F("BombFiltro Desligada"));
                digitalWrite(bombafiltro, LOW);
              }
              break;
     
     
    default:
    break;
     }//switch 

              if (buttonStateDw == HIGH ){
                 modotestesaidas = LOW;
                 chamadamenu = LOW;
                 digitalWrite(bomba1, LOW);
                 digitalWrite(bomba2, LOW); 
                 digitalWrite(bombafiltro, LOW);
                 tone(beepPin, 2800, 200);
                 //interrupts();
               //   Serial.print("                                                                                      MODOTESTESAIDAS");
               //   Serial.println(buttonStateUp);
                }
                 
                ultimoestadobotoes = botoes ; 
   
              } //fim do if
           } else {
            buttonPushCounter = 0;
             // Serial.println("off");// if the current state is LOW then the button went from on to off:
            }
         
              }//while
                      
          break; 

        
      default:
      contador = 0;
      lcd.clear();
    }//switch
   // return;


} else {
           buttonPushCounter = 0;
            // Serial.println("off");// if the current state is LOW then the button went from on to off:
           }



ultimoestadobotoes = botoes ; 

   
  } /////////fim do if

 
 delay(100);

 }  //////////////////////// fim do while
  
  


if (chamadamenu != mudancaLCD){
      lcd.clear();
      mudancaLCD = chamadamenu;
      tone (beepPin, 2700, 400);
      }
  


  temperaturapiscina   = 10 * sensor_piscina.getTempCByIndex(0);
  temperaturaPainel    = 10 * sensor_painel.getTempCByIndex(0);
  tempersaidaaquecedor = 10 * sensor_retorno.getTempCByIndex(0);
  

timerdiario ();



  //Serial.print("  tempPisc: ");
  //Serial.print(temperaturapiscina);
  //Serial.print("< >");
  //Serial.print("  tempPisc: ");
  //Serial.print(EEPROM.read(0));
  //Serial.print(" <<< ");
  
  
previousMillis = millis();

if (temperaturapiscina < -300 || temperaturaPainel < -400 || tempersaidaaquecedor < -300 ){
errosensor = HIGH;
} else {
    errosensor = LOW;
}
  //Serial.print("    errosensor ");
  //Serial.println(errosensor);


if ((errosensor == HIGH || SetAquecimentoAutomaticoEEPROM == LOW) && basetempo10seg > tempomenu ){
  
  lcd.clear(); 
  if (errosensor == HIGH && temperaturapiscina < -300){
    lcd.setCursor(1, 0); 
    lcd.print(F("ERRO SENSOR TEMPER."));
    lcd.setCursor(3, 1); 
    lcd.print(F(" da Piscina"));  
    }else if(errosensor == HIGH && temperaturaPainel < -400){
    lcd.setCursor(3, 0);
    lcd.print(F("ERRO SENSOR"));
    lcd.setCursor(3, 2);
    lcd.print(F(" do Painel"));
    }else if(errosensor == HIGH && tempersaidaaquecedor < -400){
    lcd.setCursor(3, 0);
    lcd.print(F("ERRO SENSOR"));
    lcd.setCursor(3, 3);
    lcd.print(F(" do Retorno"));
    }else{
    lcd.setCursor(8, 0);
    lcd.print(F("MODO"));
    lcd.setCursor(4, 1);
    lcd.print(F("AQUECIMENTO"));
    lcd.setCursor(5, 2);
    lcd.print(F("AUTOMATICO"));
    lcd.setCursor(3, 3);
    lcd.print(F("DESABILITADO"));
    }
    for (int i = 0; i < 5; i++){
      if (errosensor == HIGH) {
        tone(beepPin, 3700, 50);
        }
    
    delay(150);
    lcd.noBacklight();
    delay(150);
    lcd.backlight();

    }
delay(2000);



    lcd.clear();

    //lcd.autoscroll();
    //lcd.setCursor(0, 3);
    //lcd.print("Ret:");
    //lcd.print();
    //lcd.noAutoscroll();{
tempomenu = basetempo10seg;

}else{

    lcd.setCursor(2, 0);
    lcd.print("Piscina: ");
    lcd.print(sensor_piscina.getTempCByIndex(0),2);
    lcd.write((byte)0);
    lcd.setCursor(0, 1);
    lcd.print("Painel:");
    lcd.print(sensor_painel.getTempCByIndex(0),1);
    lcd.write((byte)0);
    // lcd.autoscroll();
    lcd.setCursor(0, 2);
    lcd.print("Ret:");
    lcd.print(sensor_retorno.getTempCByIndex(0), 1);
    lcd.write((byte)0);
    //lcd.noAutoscroll();
    lcd.setCursor(9, 2);
    lcd.print("Ganho:");
    lcd.print(  (sensor_retorno.getTempCByIndex(0) - sensor_piscina.getTempCByIndex(0)),2);
    lcd.write((byte)0);
}    

  circulacaodeprot();


     
   /*
   if ((temperaturaPainel >= (SetTemperSuperAqEEPROM /5) + 40) || (temperaturaPainel * 10 < SetTemperDegeloEEPROM))
        {
          digitalWrite(bomba1, HIGH);
         tempo = basetempo10seg;
        }     
      else{
        if (tempo + 6 <= basetempo10seg ){
             digitalWrite(bomba1, LOW);
             }
        
      
       else { circulacaodeprotecao = LOW;

              tempointervdeprot = basetempo30seg;
              tempobombaacioncircprot = basetempo10seg;
      
       }

if (temperaturaPainel * 2 >= SetTemperSuperAqEEPROM && circulacaodeprotecao == LOW ){
      disparoaquecerpiscina = HIGH;
      TAcionBomba = basetempo10seg;
      }
       else {disparoaquecerpiscina = LOW;
        
      }




int difT = temperaturapiscina * 10 + DifTemperEntrSaidaEEPROM;
int temperAq = tempersaidaaquecedor * 10;

if (  temperAq >= difT){
    difentrsaida = HIGH;
    TAcionBomba = basetempo10seg;
    }
    else difentrsaida = LOW; 



 //int ligarbomba;
 


 tbomba = basetempo10seg - TAcionBomba;

 if ( (tbomba  < SetTempoAcionBombaEEPROM) || disparoaquecerpiscina == HIGH )  {
     bomba1_acionada = HIGH;
     //digitalWrite(bomba, HIGH);
     }
 else{bomba1_acionada = LOW;
    // digitalWrite(bomba, LOW);
     }
 }
   */  
 
 controle_bomba_aq();
 

acionarSaidas();


//Serial.println(millis() - previousMillis);
  


  
}


/////////Fim do Loop//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////Função botão analógico
/*

void leituraanalogbotoes(){
     analogreading = analogRead(A0);
     if (analogreading > 360  && analogreading < 440){
     buttonPinSet = 1;
     Serial.print("Set");
     } else buttonPinSet =0;
     
     if (analogreading > 660  && analogreading < 740){
     buttonPinUp = 1;
     Serial.print("Up");
     } else buttonPinUp =0;
     
     if (analogreading > 960 ){
     buttonPinDw = 1;
     Serial.print("Dw");
     } else buttonPinDw =0;
     
  }


*/

void controle_botaoSet(){
    int reading = !digitalRead(buttonPinSet);
  if (reading != lastButtonStateSet) {
       lastDebounceTimeSet = millis();
       }
  if ((millis() - lastDebounceTimeSet) > debounceDelay) {
   
      if (reading != buttonStateSet) {
               buttonStateSet = reading;
               if (buttonStateSet == HIGH){ 
                 tone(beepPin, 2400, 100);
                 }

      }
  }
  lastButtonStateSet = reading;
  }

  
void controle_botaoUp(){
    int reading = !digitalRead(buttonPinUp);
  if (reading != lastButtonStateUp) {
       lastDebounceTimeUp = millis();
       }
  if ((millis() - lastDebounceTimeUp) > debounceDelay) {
   
      if (reading != buttonStateUp) {
               buttonStateUp = reading;
               if (buttonStateUp == HIGH)  {
                tone(beepPin, 2800, 10);
              }

      }
  }
  lastButtonStateUp = reading;
}

void controle_botaoDw(){
    int reading = !digitalRead(buttonPinDw);
  if (reading != lastButtonStateDw) {
       lastDebounceTimeDw = millis();
       }
    if ((millis() - lastDebounceTimeDw) > debounceDelay) {
   
      if (reading != buttonStateDw) {
         buttonStateDw = reading;
         if (buttonStateDw == HIGH)  tone(beepPin, 2600, 80);
         }
     }
  lastButtonStateDw = reading;
}

//*/


void  atualizaeeprom(){
  //    Serial.print();
  //Serial.print("SetTemperPiscina: ");
  //Serial.print(SetTemperPiscina);
  //Serial.print(" TemperPiscEEPROM:");
  //Serial.println(TemperPiscEEPROM);
    
   if (SetTemperPiscFloat != TemperPiscEEPROM){
      EEPROM.write(0, (SetTemperPiscFloat ));
      memupdate = HIGH;  
      }
    if (SetAquecimentoAutomatico != SetAquecimentoAutomaticoEEPROM){
      EEPROM.write(1, SetAquecimentoAutomatico);
      memupdate = HIGH;
      }
  if (SetTempoTimerdiario != SetTempoTimerdiarioEEPROM){
      EEPROM.write(2, SetTempoTimerdiario);
      memupdate = HIGH;
      }
    if (SetTempInPainelFloat != SetTempInPainelEEPROM){
       EEPROM.write(4, (SetTempInPainelFloat ));
       memupdate = HIGH;  
       }
   if (SetDifTempEntrSaida != DifTemperEntrSaidaEEPROM){
      EEPROM.write(5, SetDifTempEntrSaida);
      memupdate = HIGH;
      } 
  if (SetTemperSuperAqEEPROM != SetTemperSuperAq){
      EEPROM.write(6, SetTemperSuperAq);
      memupdate = HIGH;
      }
  if (SetTemperDegelo != SetTemperDegeloEEPROM){
      EEPROM.write(7, SetTemperDegelo + 100);
      memupdate = HIGH;  
      }    
  if (SetTempoAcionBomba != SetTempoAcionBombaEEPROM){
      EEPROM.write(8, SetTempoAcionBomba);
      memupdate = HIGH;
      }
  if (SetTempoBombaDesl != SetTempoBombaDeslEEPROM){
      EEPROM.write(9, SetTempoBombaDesl);
      memupdate = HIGH;
      }
      if (SetTempoAcionBombaCirc != SetTempoAcionBombaCircEEPROM){
        EEPROM.write(10, SetTempoAcionBombaCirc);
        memupdate = HIGH;
        }
    if (SetTempoBombaCircDesl != SetTempoBombaCircDeslEEPROM){
        EEPROM.write(11, SetTempoBombaCircDesl);
        memupdate = HIGH;
        }
        if (SetDifTempEntrSaidabomba2 != DifTemperEntrSaidabomba2EEPROM){
          EEPROM.write(12, SetDifTempEntrSaidabomba2);
          memupdate = HIGH;
          } 

    if (memupdate == HIGH){
      //   EEPROM.commit();
      memupdate = LOW;
      
         // Serial.println("atualiza memoria");
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print(F("Salvando na memoria"));
            //lcd.setCursor(0, 1);
           //lcd.print("    memoria");
          tone(beepPin, 3700, 2000);
        delay(3000);
        lcd.clear();
            
    TemperPiscEEPROM = EEPROM.read(0);
    SetAquecimentoAutomaticoEEPROM = EEPROM.read(1);
    SetTempoTimerdiarioEEPROM = EEPROM.read(2);
    SetTempInPainelEEPROM = EEPROM.read(4);
    DifTemperEntrSaidaEEPROM = EEPROM.read(5);
    SetTemperSuperAqEEPROM = EEPROM.read(6);
    SetTemperDegeloEEPROM = EEPROM.read(7)- 100;
    SetTempoAcionBombaEEPROM = EEPROM.read(8);
    SetTempoBombaDeslEEPROM = EEPROM.read(9);
    SetTempoAcionBombaCircEEPROM = EEPROM.read(10);
    SetTempoBombaCircDeslEEPROM = EEPROM.read(11);
    DifTemperEntrSaidabomba2EEPROM = EEPROM.read(12);
     }
    }




                       /// Função controle da bomba aquecimento

void controle_bomba_aq(){
   
  //Liga Aquecimento   
      if (errosensor == LOW && temperaturapiscina + 3 < TemperPiscEEPROM * 5 && temperaturaPainel >= SetTempInPainelEEPROM * 5 && SetAquecimentoAutomaticoEEPROM == HIGH){ 

        aquecendo = HIGH; 
        tempoestabilizacao = basetempo10seg + 6;  
       } 
         // Serial.print(basetempo10seg);
         // Serial.print(tempoestabilizacao);
   
  //Desliga Aquecimento////////////////////////////////////////   
if (aquecendo == HIGH && basetempo10seg > tempoestabilizacao || temperaturapiscina >= TemperPiscEEPROM * 5 ){ 
   if (tempersaidaaquecedor - temperaturapiscina  < SetDifTempEntrSaida  ){
     aquecendo = LOW;
     //lcd.setCursor(9, 3);
     //lcd.print(" deslig   ");
   }
}

//Liga Desliga modo turbo bomba 2////////////////////////////////////////
  if (aquecendo == HIGH && tempersaidaaquecedor - temperaturapiscina > SetDifTempEntrSaidabomba2){
      //lcd.setCursor(9, 3);
      //lcd.print("T");
      aquecendoT = HIGH;
     // Serial.print("AquecendoT ligado");  
    }else{
      //lcd.setCursor(9, 3);
      //lcd.print(" ");
      //aquecendoT = LOW;
      }

if (aquecendo == LOW || tempersaidaaquecedor - temperaturapiscina < SetDifTempEntrSaidabomba2 - 5 ){
      aquecendoT = LOW;
     // Serial.print("AquecendoT desligado"); 

    }


  
// Liga Circulação////////////////////////////////////////
if (aquecendo == HIGH && circularaquecimento == LOW && basetempo30seg >= tempocirculacaoaquecimento && SetTempoAcionBombaCirc > 0){
  circularaquecimento = HIGH;
  tempocirculacaoaquecimento = basetempo30seg + SetTempoAcionBombaCirc;
  
 //lcd.setCursor(7, 3);
  //lcd.print("C");

  }

 digitalWrite(ledPin, digitalRead(bombafiltro)) ; 

//Desliga Circulação////////////////////////////////////////
if (circularaquecimento == HIGH  && basetempo30seg >= tempocirculacaoaquecimento){
//if (aquecendo == HIGH && circularaquecimento == HIGH  && basetempo30seg >= tempocirculacaoaquecimento){
  circularaquecimento = LOW;
  tempocirculacaoaquecimento = basetempo30seg + SetTempoBombaCircDesl;
  
  //lcd.setCursor(7, 3);
  //lcd.print("  ");
  }

}   
          // Fim controle_bomba_aq




                        //Função aciona as saídas de aquecimento e filtragem
 void acionarSaidas(){ 

    if (aquecendo == HIGH && circulacaodeprotecao == LOW){
    digitalWrite(bomba1, HIGH);
    lcd.setCursor(0, 3);
    lcd.print(F("AQUECENDO"));

     if (aquecendoT == HIGH){
           digitalWrite(bomba2, HIGH);
           lcd.setCursor(9, 3);
           lcd.print("T");
         }
       
    }
    
 if(aquecendo == LOW || aquecendoT == LOW){
            digitalWrite(bomba2, LOW);
            lcd.setCursor(9, 3);
            lcd.print(" ");
         }



    if (aquecendo == LOW && acionamentocircprot == HIGH){
      digitalWrite(bomba1, HIGH);

      lcd.setCursor(0, 3);
      lcd.print(F("CIRCULACAO PROTECAO"));



    }



if (aquecendo == LOW && acionamentocircprot == LOW  ){
    digitalWrite(bomba1, LOW);
    lcd.setCursor(0, 3);
    lcd.print("Aqu.Desl ");
    }





 if (circularaquecimento != ultimoestadocircularaquecimento ){
    
    if (circularaquecimento == HIGH ){
      acionarbombafiltro = HIGH;

    }
       
    else{
    acionarbombafiltro = LOW;
    }
       
  ultimoestadocircularaquecimento = circularaquecimento;
  }

      if (acionarbombafiltro == HIGH || filtragemdiaria == HIGH ){
        digitalWrite(bombafiltro, HIGH);
        
       // if (filtragemdiaria == LOW){
          lcd.setCursor(10, 3);
          lcd.print(F(" FILTRANDO"));
       // } 
        //lcd.print(F(" FILTRANDO"));
      } 

  if (minutostimerregressivo == 0 && filtragemdiaria == LOW && acionarbombafiltro == LOW ){
    
    digitalWrite(bombafiltro, LOW);

      if (circulacaodeprotecao == LOW){
         lcd.setCursor(10, 3);
         lcd.print("FiltroDesl");
       }
    }

  }
            //Fim acionarSaidas





                            /// Função circulaçao de proteçao
  void circulacaodeprot(){


 if (errosensor == LOW && temperaturaPainel /5 > SetTemperSuperAqEEPROM  || temperaturaPainel <= SetTemperDegeloEEPROM  ){

       if (circulacaodeprotecao == LOW ){
         circulacaodeprotecao = HIGH;
        // tempobombaacioncircprot = basetempo10seg;
        }
 
      if (digitalRead(bomba1) == LOW && basetempo10seg >= tempobombaacioncircprot){
        acionamentocircprot = HIGH;
        tempobombaacioncircprot = basetempo10seg + SetTempoAcionBomba;
        
       }


  } else {
       circulacaodeprotecao = LOW;

         }



         if (  basetempo10seg >= tempobombaacioncircprot && digitalRead(bomba1) == HIGH){
           //digitalWrite(bomba1, LOW);
           acionamentocircprot = LOW;
           tempobombaacioncircprot = basetempo10seg + (SetTempoBombaDesl * 3); 
           }


      
 } // Fim circulacaodeprot



                              //Função TEMPORIZADOR/////
void timer (){     

      /////////////MenuTimer
    if (buttonStateUp ==LOW){
      tempochamarmenuTimer = millis();
     }else {
      
       
     //delay(300);
     }

    if (buttonStateUp == HIGH  && (millis()-  tempochamarmenuTimer > 4000)) {
    //Serial.println(millis());
    chamadamenuTimer = HIGH;
    //lcd.clear();
    contador = 0;
    //
     // Serial.print("tempochamarmenuTimer");
    //  Serial.print(tempochamarmenuTimer);
     tone(beepPin, 2700, 400 );
    }




while (chamadamenuTimer == HIGH) {
       controle_botaoSet();
       controle_botaoUp();
       controle_botaoDw(); 
      //if ( buttonStateSet == HIGH || buttonStateUp == HIGH || buttonStateDw == HIGH){
     if ( buttonStateUp == HIGH || buttonStateDw == HIGH){
       tempomenu = millis();
      botoes = HIGH;
     } else botoes = LOW;


    if (millis() -  tempomenu >10000 || buttonStateSet == HIGH ){
   // if (millis() -  tempomenu >8000  ){ 
   
      lcd.setCursor(0, 3);
      lcd.print(F("     SELECIONADO    "));
      tone(beepPin, 3700, 2000);
      delay(2000);
      lcd.clear();
      chamadamenuTimer = LOW;
      ultimoestadotimerregressivo = -1;
      // tempomenu = millis() - 20000;
      
      buttonStateSet = LOW;
     }
  
  
  if ((botoes != ultimoestadobotoes)  || (millis() - whilelastTime > 800 ) ) {
     //lcd.noBacklight();

           if (botoes == HIGH)  {
               lcd.clear();
               buttonPushCounter++;
              
                  if (buttonPushCounter > 1) {
                     whilelastTime = millis()  - (buttonPushCounter * 100) ;  //              
                       } else whilelastTime = millis();


if (buttonStateUp == HIGH ){
    timerregressivo = timerregressivo + 1;
    tone(beepPin, 2800, 50);
    }

if (buttonStateDw == HIGH ){
    timerregressivo = timerregressivo - 1;
    tone(beepPin, 2600, 50);
    }
    if (timerregressivo < 0) timerregressivo = 6; 
    if (timerregressivo > 6) timerregressivo = 0;   




  //lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(F("TIMER REGRESSIVO"));
  lcd.setCursor(0, 1);
  lcd.print(timerregressivo);
  //lcd.setCursor(0, 2);
  //lcd.print("Saida: Tecla  ");
  lcd.setCursor(0, 3);
  lcd.print("  <              > ");
   
  if (timerregressivo == 0){
    lcd.setCursor(2, 2);
    lcd.print(F("   DESLIGADO   "));
    minutostimerregressivo = 0;  
    }

  if (timerregressivo == 1){
    lcd.setCursor(2, 2);
    lcd.print(F("   30 MINUTOS    "));
    minutostimerregressivo = 30;  
    }
    if (timerregressivo == 2){
    lcd.setCursor(2, 2);
    lcd.print(F("   60 MINUTOS   "));
    minutostimerregressivo = 60;  
    }
    if (timerregressivo == 3){
    lcd.setCursor(2, 2);
    lcd.print(F("   90 MINUTOS   "));
    minutostimerregressivo = 90;  
    }
    if (timerregressivo == 4){
    lcd.setCursor(2, 2);
    lcd.print(F("   2 Horas   "));
    minutostimerregressivo = 120;
    }
    if (timerregressivo == 5){
    lcd.setCursor(2, 2);
    lcd.print(F("   3 Horas   "));
  minutostimerregressivo = 180;  
  }
  if (timerregressivo == 6){
    lcd.setCursor(2, 2);
    lcd.print(F("   4 Horas   "));
  minutostimerregressivo = 240;  
  }
    

  } else {
    buttonPushCounter = 0;
    }

  ultimoestadobotoes = botoes ; 

} // fim do if

}// fim do while

if (ultimosminutostimerregressivo < basetempo10seg/6 && minutostimerregressivo > 0){
//if (ultimosminutostimerregressivo < basetempo10seg && minutostimerregressivo > 0){
//if (ultimosminutostimerregressivo < basetempo30seg && minutostimerregressivo > 0){
  minutostimerregressivo = minutostimerregressivo - 1;
  ultimosminutostimerregressivo = basetempo10seg/6;
  //ultimosminutostimerregressivo = basetempo10seg;
  //ultimosminutostimerregressivo = basetempo30seg;
} 

 
//if (minutostimerregressivo != ultimoestadotimerregressivo){

//Serial.print("minutostimerregressivo: ");
//erial.print(minutostimerregressivo); 
//Serial.print(" ultimoestadotimerregressivo: ");
//Serial.print(ultimoestadotimerregressivo);
  
  //ultimoestadotimerregressivo = minutostimerregressivo;

  //lcd.clear();
  //  lcd.setCursor(10, 3);
 // lcd.print(F("Filt.Lg"));
if (minutostimerregressivo > 99){
   lcd.setCursor(10, 3);
  lcd.print(F("Filt.Lg"));
  lcd.setCursor(17, 3);
  lcd.print(minutostimerregressivo );
  } else if (minutostimerregressivo > 9){
     lcd.setCursor(10, 3);
  lcd.print(F("Filt.Lg "));
 lcd.setCursor(18, 3);
  lcd.print(minutostimerregressivo);
  } else if (minutostimerregressivo > 0){
 lcd.setCursor(19, 3); lcd.setCursor(10, 3);
  lcd.print(F("Filt.Lg  "));
  lcd.print(minutostimerregressivo);
  }
 
filtragemdiaria = HIGH;




  if (minutostimerregressivo == 0 ){
   // lcd.setCursor(10, 3);
    //lcd.print(F("FiltroDesl"));
    //digitalWrite(bombafiltro, LOW);
    //lcd.clear();
    //Serial.println("Circulacao desligada: ");
    filtragemdiaria = LOW;
   }
//} 






} // Fim do timer

       









void timerdiario (){     

if (temperaturaPainel < temperaturabaixapainel){

temperaturabaixapainel = temperaturaPainel;
//tempotemperaturaminimapainel = basetempo30seg + 360;
tempotemperaturaminimapainel = basetempo30seg + 10;
ultimotimerdiario = basetempo30seg;


}
    lcd.setCursor(12, 1);
    lcd.print(basetempo30seg);
   lcd.print("|");
   lcd.print(tempotemperaturaminimapainel);
   // lcd.print(basetempo30seg - (tempotemperaturaminimapainel + 360));
    //lcd.setCursor(13, 1);
   lcd.print("|");
   lcd.print(ultimotimerdiario);
   // lcd.print(basetempo30seg - (tempotemperaturaminimapainel + 360));

//if (basetempo30seg > tempotemperaturaminimapainel  && ultimotimerdiario > basetempo30seg - 1800){
  if (basetempo30seg > tempotemperaturaminimapainel  && ultimotimerdiario > basetempo30seg - 20){
    ultimotimerdiario = basetempo30seg;
    temperaturabaixapainel = temperaturaPainel;
    filtragemdiaria = HIGH;
    minutostimerregressivo =  SetTempoTimerdiario * 2;
  } 

if (basetempo30seg > ultimotimerdiario + (SetTempoTimerdiario * 2)){
  filtragemdiaria = LOW;
}



//Serial.print("temperaturabaixapainel: ");
//Serial.print(temperaturabaixapainel);
//Serial.print(" ultimotimerdiario: ");
//Serial.print(ultimotimerdiario);  
//Serial.print(" Ult > bs30 - 1800: ");
//Serial.print(ultimotimerdiario - (basetempo30seg - 1800));






} // Fim da função timerdiario



void Fchamadamenu(){
  //chamadamenu = HIGH;
  buttonStateSet = HIGH;
  //if (contador < 1 || contador > 14){
   // contador = 1;
  //  } //else contador = contador + 1;
  //contador = 0;
  //delay(200);
  //noInterrupts();
  tempomenu = millis();
  //tone(beepPin, 2600, 50);
 }


 

void timerminutos(){
 // minutostimerregressivo = minutostimerregressivo + 1;
  
buttonStateUp = HIGH;
//tone(beepPin, 2800, 50);
  
if (chamadamenu == LOW){
  tone(beepPin, 2800, 50);
   if (minutostimerregressivo == 0){
       minutostimerregressivo = minutostimerregressivo + 2;
      } else minutostimerregressivo = minutostimerregressivo + 1;
//delay(100);
}
}