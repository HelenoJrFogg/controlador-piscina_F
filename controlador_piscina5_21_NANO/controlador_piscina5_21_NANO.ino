

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
   //bool estadochamarmenuTimer;
   unsigned long tempoalarme = 0;
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


//Array simbolo seta baixo
byte setaD[8] ={ B00000000,
                B00000000,
                B00011111,
                B00011111,
                B00001110,
                B00001110,
                B00000100,
                B00000100,
                };


//Array simbolo seta cima
byte setaU[8] ={ B00000100,
                 B00000100,
                 B00001110,
                 B00001110,
                 B00011111,
                 B00011111,
                 B00000000,
                 B00000000,};


                 //Array simbolo seta cima
byte setaM[8] ={ B00000000,
                 B00000000,
                 B00011111,
                 B00011111,
                 B00011111,
                 B00011111,
                 B00011111,
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
//unsigned long previousMillis;
//const long interval = 800; 

int temperaturapiscina;
int tempersaidaaquecedor;
int temperaturaPainel ;

//boolean disparoaquecerpiscina;
//boolean difentrsaida;

boolean aquecendo;
boolean aquecendoT;
boolean circulacaodeprotecao = LOW;

unsigned long referenciabasetempo2seg;
unsigned long ultimoreferenciabasetempo2seg = 0;
unsigned long basetempo2seg = 0;
unsigned long basetempo10seg;
unsigned long basetempo30seg;
int TAcionBomba;
//int TIntervBomba;
//boolean bomba1_acionada;
//unsigned long tbomba;
unsigned long tempobombaacioncircprot; //tempo de acionamento da bomba no acionamento de proteção.
//unsigned long tempointervdeprot;       // tempo de intervalo da bomba no acionamento de proteção. 

 //unsigned long tempo;


//bool DisparoProtecao;

unsigned long tempoestabilizacao = 0;
int circularaquecimento;
int ultimoestadocircularaquecimento;
unsigned long tempocirculacaoaquecimento =2;
//int circulando = LOW;
int modoteste = 0;
int modotestesaidas ;
int timerregressivo = 0;
int minutostimerregressivo = 0;
unsigned long ultimosminutostimerregressivo = 0;
int ultimoestadotimerregressivo;
int errosensor;
int temperaturabaixapainel = 300;
int tempotimerdiario = 0;


bool filtragemdiaria;
bool acionarbombafiltro = LOW;
bool acionamentocircprot = LOW;
int temperinicioaq;
//int temperiniciocirc;
bool restfabrica = LOW; 
int tdstatus = 0; 
float tbp;
int temporegressivotd1;
//int temporegressivotd2;

int tempointervalotimerdiario = 2040 ;//120;//2040;//10  ;//2040 ; // minutos * 2. 2040 = 17 hrs
int tempoesperatimerdiario =   360 ;//60;//360;//5      ;//360; //  minutos * 2. 360 = 3 hrs

int ultimotimerdiario = tempointervalotimerdiario;

unsigned long tempotemperaturaminimapainel = tempoesperatimerdiario;
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
  
  Serial.begin(115200);
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
       lcd.print(F("V2.35"));
       delay(2000);
       lcd.clear();


       lcd.createChar(0, grau);
       lcd.createChar(1, setaD);
       lcd.createChar(2, setaU);
       lcd.createChar(3, setaM);
    
       tone(beepPin, 3000, 80);
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

//temporegressivotd = tempoesperatimerdiario + tempointervalotimerdiario;

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(void){
 // Serial.println(millis() - previousMillis);
  //previousMillis = millis();  




    referenciabasetempo2seg = millis() / 2000;

    //if (referenciabasetempo10seg > ultimoreferenciabasetempo10seg || referenciabasetempo10seg < ultimoreferenciabasetempo10seg){
    if (referenciabasetempo2seg != ultimoreferenciabasetempo2seg){
        
    ultimoreferenciabasetempo2seg = referenciabasetempo2seg;
        basetempo2seg = basetempo2seg + 1;
        basetempo10seg = basetempo2seg  / 5;
        basetempo30seg = basetempo10seg / 3;
        tdstatus ++;
        lcd.setCursor(13, 1);
        lcd.print("       ");












    sensor_piscina.requestTemperatures();
    sensor_painel.requestTemperatures();
    sensor_retorno.requestTemperatures();

  temperaturapiscina   = 10 * sensor_piscina.getTempCByIndex(0);
  temperaturaPainel    = 10 * sensor_painel.getTempCByIndex(0);
  tempersaidaaquecedor = 10 * sensor_retorno.getTempCByIndex(0);

timerdiario ();


    }
    
   


/////////////MenuTimer

timer();


    //leituraanalogbotoes();
    //controle_botaoSet();
    //controle_botaoUp();
    //controle_botaoDw();



/////////////Menu
//Serial.println(tempochamarmenu);1

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
 
  restfabrica = LOW;

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
        tone(beepPin, 2800, 80);
         }
        
    if (contador > 14){
      contador = 1;
      tone(beepPin, 2900, 80);
      }
     
      
      
 switch (contador){
      
   case 1:
        if (buttonStateUp == HIGH && SetTemperPiscFloat < 80){
            SetTemperPiscFloat = SetTemperPiscFloat + 1;
            tone(beepPin, 3000, 80);
            }
             
        if (buttonStateDw == HIGH && SetTemperPiscFloat > 40){
            SetTemperPiscFloat = SetTemperPiscFloat - 1;
            tone(beepPin, 2600, 80);
            }
            
        lcd.setCursor(0, 0);
        lcd.print(F("1 Temperatura Maxima"));                    
        lcd.setCursor(3, 1);
        lcd.print(F("de AQUECIMENTO"));                    
        lcd.setCursor(5, 2);
        lcd.print(F("da PISCINA"));

        lcd.setCursor(4, 3);
        lcd.print(SetTemperPiscFloat/2,1);          
          lcd.write((byte)0);
                lcd.print(F(" graus"));
                lcd.setCursor(1, 3);
                //lcd.print(F("<"));
                lcd.write((byte)1);
                lcd.setCursor(18, 3);
                lcd.write((byte)2);
                //lcd.print(F(">"));
          //lcd.print(SetTemperPiscFloat);
       break;

       case 2:
            if (buttonStateUp == HIGH ){
                SetAquecimentoAutomatico = !SetAquecimentoAutomatico;
                if(SetAquecimentoAutomatico == 1){
                  tone(beepPin, 2900, 80);
                } else tone(beepPin, 2600, 80);
              }
            
            if (buttonStateDw == HIGH){
                SetAquecimentoAutomatico = !SetAquecimentoAutomatico;
                if(SetAquecimentoAutomatico == 1){
                  tone(beepPin, 3000, 80);
                } else tone(beepPin, 2600, 80);
                  
              }
                lcd.setCursor(0, 0);
                lcd.print(F("2  AQUECIMENTO SOLAR"));
                lcd.setCursor(2, 1);
                lcd.print(F("MODO AQUECIMENTO"));
                lcd.setCursor(5, 2);
                lcd.print(F("AUTOMATICO"));
                lcd.setCursor(1, 3);
                //lcd.print(F("<"));
                lcd.write((byte)1);
                lcd.setCursor(18, 3);
                lcd.write((byte)2);
                //lcd.print(F(">"));             
                
                if (SetAquecimentoAutomatico == 1){
                  lcd.setCursor(5, 3);
                  lcd.print(F(" LIGADO"));
                  //tone(beepPin, 2800, 80);
                } else {
                  lcd.setCursor(5, 3);
                  lcd.print(F("DESLIGADO"));
                  //tone(beepPin, 2600, 80);
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
            tone(beepPin, 3000, 80);
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
            //lcd.setCursor(9, 3);
            lcd.print(F("  "));
            lcd.print(SetTempoTimerdiario);
            lcd.print(F(" Minutos"));
             
          }
          break;


       case 4:
          if (buttonStateUp == HIGH && SetTempoAcionBombaCirc < 240){
              SetTempoAcionBombaCirc = SetTempoAcionBombaCirc + 1;
              tone(beepPin, 3000, 80);
              }
          if (buttonStateDw == HIGH && SetTempoAcionBombaCirc > 0){
             SetTempoAcionBombaCirc = SetTempoAcionBombaCirc - 1;
             tone(beepPin, 2600, 80);
             }
             lcd.setCursor(0, 0);
             lcd.print(F("4 Tempo de Acionament"));
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
  
             lcd.setCursor(0, 3);
          if (horas < 10){
            lcd.print("0");
             }
             lcd.print(horas);
             lcd.print(":");
             //lcd.setCursor(5, 3);
          if (minutos < 10){
             lcd.print("0");
             }
             lcd.print(minutos);
             lcd.print(":");
            // lcd.setCursor(8, 3);
          if (segundos < 10){
              lcd.print("0");
              }
              lcd.print(segundos); 
              //lcd.setCursor(9, 3);
            lcd.print(F("  "));
            lcd.print(minutos);
            lcd.print(F(" Minutos"));
              
            break;
            
      
       case 5:       
          if (buttonStateUp == HIGH && SetTempoBombaCircDesl < 240){
              SetTempoBombaCircDesl = SetTempoBombaCircDesl + 1;
              tone(beepPin, 3000, 80);
              }
          if (buttonStateDw == HIGH && SetTempoBombaCircDesl > 0){
             SetTempoBombaCircDesl = SetTempoBombaCircDesl - 1;
             tone(beepPin, 2600, 80);
             }
             lcd.setCursor(0, 0);
             lcd.print(F("5 Tempo de intervalo"));
             lcd.setCursor(0, 1);
             lcd.print(F("de Bomba desligada"));
             lcd.setCursor(1, 2);
             lcd.print(F("do ciclo d circulacao"));
             // lcd.print(SetTemperSuperAqFloat);
             total = SetTempoBombaCircDesl * 30;
             horas = (total / 3600);
             minutos = ((total - (horas * 3600)) / 60);
             segundos = (total % 60);
             
             lcd.setCursor(0, 3);
          if (horas < 10){
            lcd.print("0");
             }
             lcd.print(horas);
             lcd.print(":");
             //lcd.setCursor(5, 3);
          if (minutos < 10){
             lcd.print("0");
             }
             lcd.print(minutos);
             lcd.print(":");
             //lcd.setCursor(8, 3);
          if (segundos < 10){
              lcd.print("0");
              }
              lcd.print(segundos);
            //lcd.setCursor(9, 3);
            lcd.print(F(" "));
            lcd.print(minutos);
            lcd.print(F(" Minutos"));
            break;

          



       
   case 6:
        if (buttonStateUp == HIGH && SetTempInPainelFloat < 100){
            SetTempInPainelFloat = SetTempInPainelFloat + 1;
            tone(beepPin, 3000, 80);
            }
             
        if (buttonStateDw == HIGH && SetTempInPainelFloat > 50){
          SetTempInPainelFloat = SetTempInPainelFloat - 1;
          tone(beepPin, 2600, 80);
            }
            
        lcd.setCursor(0, 0);
        lcd.print(F("6 Temperatura Painel"));                    
        lcd.setCursor(0, 1);
        lcd.print(F(" de inicio"));                    
        lcd.setCursor(0, 2);
        lcd.print(F(" do aquecimento"));
        lcd.setCursor(4, 3);
        lcd.print(SetTempInPainelFloat/2,1);
         // lcd.setCursor(7, 3);
          lcd.write((byte)0);
           lcd.print(F(" graus"));
                lcd.setCursor(1, 3);
                //lcd.print(F("<"));
                lcd.write((byte)1);
                lcd.setCursor(18, 3);
                lcd.write((byte)2);
                //lcd.print(F(">"));
          //lcd.print(SetTempInPainelFloat);
       break; 

  case 7:
        if (buttonStateUp == HIGH && SetDifTemperEntrSaidaFloat <= 99){
          SetDifTemperEntrSaidaFloat = SetDifTemperEntrSaidaFloat + 1;
          tone(beepPin, 3000, 80);
          }
        
        if (buttonStateDw == HIGH && SetDifTemperEntrSaidaFloat > 0){
            SetDifTemperEntrSaidaFloat = SetDifTemperEntrSaidaFloat - 1;
            tone(beepPin, 2600, 80);
            }
            lcd.setCursor(0, 0);
            lcd.print(F("7 Ganho minimo de"));
            lcd.setCursor(0, 1);
            lcd.print(F("Temperatura do"));
            lcd.setCursor(0, 2);
            lcd.print(F(" Sistema ligado"));
            lcd.setCursor(4, 3);
            lcd.print(SetDifTemperEntrSaidaFloat/10);
            //lcd.setCursor(8, 3);
            lcd.write((byte)0);
                lcd.print(F(" graus"));
                lcd.setCursor(1, 3);
                //lcd.print(F("<"));
                lcd.write((byte)1);
                lcd.setCursor(18, 3);
                lcd.write((byte)2);
                //lcd.print(F(">"));
            //lcd.print(SetDifTemperEntrSaidaFloat);
                      
          break;

    case 8:
            if (buttonStateUp == HIGH && SetDifTemperEntrSaidabomba2Float <= 99){
              SetDifTemperEntrSaidabomba2Float = SetDifTemperEntrSaidabomba2Float + 1;
              tone(beepPin, 3000, 80);
              }
            
            if (buttonStateDw == HIGH && SetDifTemperEntrSaidabomba2Float > 0){
                SetDifTemperEntrSaidabomba2Float = SetDifTemperEntrSaidabomba2Float - 1;
                tone(beepPin, 2600, 80);
                }
                lcd.setCursor(0, 0);
                lcd.print(F("8 Ganho minimo de"));
                lcd.setCursor(0, 1);
                lcd.print(F("Temperatura de"));
                lcd.setCursor(0, 2);
                lcd.print(F("Acionamento Bomba2"));
                lcd.setCursor(4, 3);
                lcd.print(SetDifTemperEntrSaidabomba2Float/10);
                //lcd.setCursor(8, 3);
                lcd.write((byte)0);
                lcd.print(F(" graus"));
                lcd.setCursor(1, 3);
                //lcd.print(F("<"));
                lcd.write((byte)1);
                lcd.setCursor(18, 3);
                lcd.write((byte)2);
                //lcd.print(F(">"));

             //   lcd.print(">");
             //   lcd.print(SetDifTemperEntrSaidabomba2Float);
               break; 
          

        
   case 9:
        if (buttonStateUp == HIGH && SetTemperSuperAqfloat < 140){
            SetTemperSuperAqfloat = SetTemperSuperAqfloat + 1;
            tone(beepPin, 3000, 80);
            }
        if (buttonStateDw == HIGH && SetTemperSuperAqfloat > 100){
            SetTemperSuperAqfloat = SetTemperSuperAqfloat - 1;
            tone(beepPin, 2600, 80);
            }
        lcd.setCursor(0, 0);
        lcd.print(F("9 Temperatura de"));
        lcd.setCursor(0, 1);
        lcd.print(F("acionam. da PROTECAO"));
        lcd.setCursor(0, 2);
        lcd.print(F("por CALOR do painel"));
        lcd.setCursor(4, 3);
        lcd.print(SetTemperSuperAqfloat /2,1 );

           // lcd.setCursor(7, 3);
            lcd.write((byte)0);
                lcd.print(F(" graus"));
                lcd.setCursor(1, 3);
                //lcd.print(F("<"));
                lcd.write((byte)1);
                lcd.setCursor(18, 3);
                lcd.write((byte)2);
                //lcd.print(F(">"));
            //lcd.print(SetTemperSuperAqfloat);

       break;


    case 10:
        if (buttonStateUp == HIGH && SetTemperDegeloFloat < 50){
          SetTemperDegeloFloat = SetTemperDegeloFloat + 1;
          tone(beepPin, 3000, 80);          }
        
        if (buttonStateDw == HIGH && SetTemperDegeloFloat > -30){
            SetTemperDegeloFloat = SetTemperDegeloFloat - 1;
            tone(beepPin, 2600, 80);
            }
            lcd.setCursor(0, 0);
            lcd.print(F("10 Temperatura Protec"));
            lcd.setCursor(0, 1);
            lcd.print(F("de ANTICONGELAMENTO"));
            lcd.setCursor(0, 2);
            lcd.print(F(" do Painel"));
            lcd.setCursor(4, 3);
            lcd.print((SetTemperDegeloFloat/10) );//-10);
            //lcd.setCursor(10, 3);
            lcd.write((byte)0);
                lcd.print(F(" graus"));
                lcd.setCursor(1, 3);
                //lcd.print(F("<"));
                lcd.write((byte)1);
                lcd.setCursor(18, 3);
                lcd.write((byte)2);
                //lcd.print(F(">"));
            //lcd.print(SetTemperDegeloFloat);
        break;

  

        
    case 11:
        if (buttonStateUp == HIGH && SetTempoAcionBombaFloat <= 80){
            SetTempoAcionBombaFloat = SetTempoAcionBombaFloat + 1;
            tone(beepPin, 3000, 80);
            }
        if (buttonStateDw == HIGH && SetTempoAcionBombaFloat > 0){
           SetTempoAcionBombaFloat = SetTempoAcionBombaFloat - 1;
           tone(beepPin, 2600, 80);
           }
           lcd.setCursor(0, 0);
           lcd.print(F("11 Tempo de Acioname"));
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

           lcd.setCursor(0, 3);
        if (horas < 10){
          lcd.print("0");
           }
           lcd.print(horas);
           lcd.print(":");
           //lcd.setCursor(5, 3);
        if (minutos < 10){
           lcd.print("0");
           }
           lcd.print(minutos);
           lcd.print(":");
           //lcd.setCursor(8, 3);
        if (segundos < 10){
            lcd.print("0");
            }
            lcd.print(segundos); 
                //lcd.setCursor(9, 3);
            lcd.print(F("  "));
            lcd.print(minutos);
            lcd.print(F(" Minutos"));
//lcd.print(">");
//
            
          break;
          
    
     case 12:       
        if (buttonStateUp == HIGH && SetTempoBombaDeslFloat <= 239){
            SetTempoBombaDeslFloat = SetTempoBombaDeslFloat + 1;
            tone(beepPin, 3000, 80);
            }
        if (buttonStateDw == HIGH && SetTempoBombaDeslFloat > 0){
           SetTempoBombaDeslFloat = SetTempoBombaDeslFloat - 1;
           tone(beepPin, 2600, 80);
           }
           lcd.setCursor(0, 0);
           lcd.print(F("12 Tempo de intervalo"));
           lcd.setCursor(0, 1);
           lcd.print(F("de Bomba desligada"));
           lcd.setCursor(1, 2);
           lcd.print(F("do ciclo d protecao"));
           // lcd.print(SetTemperSuperAqFloat);
           total = SetTempoBombaDeslFloat * 30;
           horas = (total / 3600);
           minutos = ((total - (horas * 3600)) / 60);
           segundos = (total % 60);
           
           lcd.setCursor(0, 3);
        if (horas < 10){
          lcd.print("0");
           }
           lcd.print(horas);
           lcd.print(":");
           //lcd.setCursor(5, 3);
        if (minutos < 10){
           lcd.print("0");
           }
           lcd.print(minutos);
           lcd.print(":");
           //lcd.setCursor(8, 3);
        if (segundos < 10){
            lcd.print("0");
            }
            lcd.print(segundos);
            //lcd.setCursor(9, 3);
            lcd.print(F("  "));
            lcd.print(minutos);
            lcd.print(F(" Minutos"));
          break;

        

       case 13:
            if (buttonStateUp == HIGH && restfabrica == LOW){
              restfabrica = HIGH;
              tone(beepPin, 3000, 80);
              delay(500);
              buttonStateUp = LOW;
              }
            
            if (buttonStateDw == HIGH ){
                contador ++;
                restfabrica = LOW;
                tone(beepPin, 2600, 80);
                //break;
                }

                lcd.setCursor(0, 0);
                lcd.print(F("13 Restaurar valores"));
                lcd.setCursor(0, 1);
                lcd.print(F("de Fabrica"));
                  lcd.setCursor(1, 3);
                //lcd.print(F("<"));
                lcd.write((byte)1);
                lcd.setCursor(18, 3);
                lcd.write((byte)2);
                //lcd.print(F(">"));
                lcd.setCursor(2, 3);
                lcd.print(F(" NAO        SIM "));
                //lcd.setCursor(3, 3);
               // lcd.print(SetDifTemperEntrSaidabomba2Float/10);
               if (restfabrica == HIGH){
                lcd.setCursor(6, 2);
                lcd.print(F("CONFIRMA ?"));
                
                  lcd.setCursor(2, 3);
                  lcd.print(F(" NAO        SIM "));
                
                if (buttonStateUp == HIGH){
                  tone(beepPin, 3000, 3000);
                  lcd.clear();
                  lcd.setCursor(2, 1);
                  lcd.print(F("Restaurando"));
                  //delay(1000);
                  //lcd.clear();
                  lcd.setCursor(0, 2);
                  lcd.print(F("Valores de Fabrica"));
                  
                  
                  SetTemperPiscFloat = 62;           //1       /2 31 graus
                  SetAquecimentoAutomatico = 1;      //2          ligado
                  SetTempoTimerdiario = 15;          //3          15 minutos
                  SetTempInPainelFloat = 80;         //4       /2 40 minutos
                  SetDifTemperEntrSaidaFloat = 20;   //5      /10  2 graus
                  SetDifTemperEntrSaidabomba2Float = 30; //6  /10  3 graus
                  SetTemperSuperAqfloat = 116;       //7      /2  58 graus
                  SetTemperDegeloFloat = 40;         //8      /10  4 graus
                  SetTempoAcionBombaFloat= 40;       //9       /10 4 minutos
                  SetTempoBombaDeslFloat = 40;       //10      /2 20 minutos
                  SetTempoAcionBombaCirc = 20;       //11         20 minutos
                  SetTempoBombaCircDesl = 60;        //12         60 minutos
                  delay(2000);
                buttonStateSet = HIGH;
                contador ++;
                restfabrica = LOW;
                buttonStateUp = LOW;
                

                break;
                }
                
                
                } 
               
               //lcd.setCursor(8, 3);
               // lcd.write((byte)0);
               // lcd.print(">");
               // lcd.print(SetDifTemperEntrSaidabomba2Float);
               break; 

       case 14:
             //lcd.clear();
             lcd.setCursor(0, 0);
             lcd.print(F("14 Entrar no MODO"));
             lcd.setCursor(0, 1);
             lcd.print(F("de TESTE das Saidas"));
             lcd.setCursor(1, 3);
             lcd.print(F("ACEITAR: tecla "));

                lcd.write((byte)2);
             

             
             if (buttonStateUp == HIGH ){
                 modotestesaidas = HIGH;
                 tone(beepPin, 2800, 80);
                 lcd.clear();
                 //Serial.print("                                                                                      MODOTESTESAIDAS");
                 //Serial.println(buttonStateUp);
                }
             bool saidab1 = LOW;
             bool saidab2 = LOW;
             bool saidaf = LOW;

         while (modotestesaidas ==HIGH){
           
            //leituraanalogbotoes();
            controle_botaoSet();
            controle_botaoUp();
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
             lcd.print(F("Lig/Desl: Tecla "));
             lcd.write((byte)3);
             lcd.setCursor(1, 2);
             lcd.print(F("Sair: Tecla "));
             lcd.write((byte)1);

             if (buttonStateSet == HIGH){
              saidab1 = !saidab1;
              tone(beepPin, 2800, 80);
              }


              if (saidab1 == HIGH){
                lcd.setCursor(0, 3);
                lcd.print(F("Bomba Aquec. Ligada "));
                digitalWrite(bomba1, HIGH);
                tone(beepPin, 3000, 80);
                } else  {
                  lcd.setCursor(0, 3);
                  lcd.print(F("Bomba Aq. Desligada "));
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
                  tone(beepPin, 3000, 80);
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
            tone(beepPin, 2800, 100);
            }


            if (saidaf == HIGH){
              lcd.setCursor(0, 3);
              lcd.print(F("Bomba Filtro Ligada "));
              digitalWrite(bombafiltro, HIGH);
              tone(beepPin, 3000, 80);
              
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
                 lcd.clear();
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

        
      //default:
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
  


  //temperaturapiscina   = 10 * sensor_piscina.getTempCByIndex(0);
  //temperaturaPainel    = 10 * sensor_painel.getTempCByIndex(0);
  ///tempersaidaaquecedor = 10 * sensor_retorno.getTempCByIndex(0);
  

//timerdiario ();



  //Serial.print("  tempPisc: ");
  //Serial.print(temperaturapiscina);
  //Serial.print("< >");
  //Serial.print("  tempPisc: ");
  //Serial.print(EEPROM.read(0));
  //Serial.print(" <<< ");
  
  
//previousMillis = millis();

if (temperaturapiscina < -300 || temperaturaPainel < -400 || tempersaidaaquecedor < -300 ){

  errosensor = HIGH;

} else {
    errosensor = LOW;
}
  //Serial.print("    errosensor ");
  //Serial.println(errosensor);


if ((errosensor == HIGH || SetAquecimentoAutomaticoEEPROM == LOW) && basetempo10seg > tempoalarme ){
  
  lcd.clear(); 
  if (errosensor == HIGH && temperaturapiscina < -300){
    lcd.setCursor(1, 0); 
    lcd.print(F("ERRO SENSOR TEMPER."));
    lcd.setCursor(3, 1); 
    lcd.print(F(" da Piscina"));  
    }//else

    if(errosensor == HIGH && temperaturaPainel < -400){
    lcd.setCursor(3, 0);
    lcd.print(F("ERRO SENSOR"));
    lcd.setCursor(3, 2);
    lcd.print(F(" do Painel"));
    }//else 
    
    if(errosensor == HIGH && tempersaidaaquecedor < -400){
    lcd.setCursor(3, 0);
    lcd.print(F("ERRO SENSOR"));
    lcd.setCursor(3, 3);
    lcd.print(F(" do Retorno"));
    }//else
    
    if (SetAquecimentoAutomaticoEEPROM == LOW && errosensor == LOW){
      lcd.clear();
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
tempoalarme = basetempo10seg + 1 ;

}else{

    lcd.setCursor(5, 0);
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
    lcd.print(  (sensor_retorno.getTempCByIndex(0) - sensor_piscina.getTempCByIndex(0)),1);
    lcd.write((byte)0);
}    



 circulacaodeprot();

 
 controle_bomba_aq();
 

 acionarSaidas();


//Serial.println(millis() - previousMillis);
  
digitalWrite(ledPin, circulacaodeprotecao); //desliga led de aquecimento

  
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




void  atualizaeeprom(){

    
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
        delay(2000);
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
if (aquecendo == LOW ){  

  if ( temperaturaPainel >= SetTempInPainelEEPROM * 5 ){     
     if (temperaturapiscina + 3 < TemperPiscEEPROM * 5 ){ 
      if ( SetAquecimentoAutomaticoEEPROM == HIGH && errosensor == LOW  ) { 
        aquecendo = HIGH; 
        tempoestabilizacao = basetempo10seg + 12; 
        temperinicioaq = tempersaidaaquecedor + 10;
       } 
     }
  } 
}
        // Serial.print(" bt10 ");
        // Serial.print(basetempo10seg);
        // Serial.print(tempoestabilizacao);

        if (aquecendo == HIGH && basetempo10seg == tempoestabilizacao){
          //Serial.print(" tempeinicioaq ");
         // Serial.print(temperinicioaq);
           
          if (tempersaidaaquecedor < temperinicioaq ){
            if (tempersaidaaquecedor > temperinicioaq - 20){
              lcd.clear();
              lcd.setCursor(4, 0);
              lcd.print(F("VERIFICAR"));
              lcd.setCursor(7, 1);
              lcd.print(F("BOMBA"));
              lcd.setCursor(5, 2);
              lcd.print(F("AQUECIMENTO"));

              digitalWrite(bomba1, LOW);


              for (int i = 0; i < 20; i++){
                
              tone(beepPin, 3700, 50);
              delay(100);
              tone(beepPin, 3200, 50);
              delay(150);
              lcd.noBacklight();
              delay(150);
              lcd.backlight();
          
              }
              delay(30000);
              lcd.clear();
             // tone(beepPin, 3000, 1000);
             // delay(1000);
            //  tone(beepPin, 3500, 1000);
            //  delay(1000);
            //  tone(beepPin, 3200, 1000);    
             // delay(1000);
                          //


            }
          } 
        }
             
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
  


  }

 //digitalWrite(ledPin, digitalRead(bombafiltro)) ; 

//Desliga Circulação////////////////////////////////////////
if (circularaquecimento == HIGH  && basetempo30seg >= tempocirculacaoaquecimento){
//if (aquecendo == HIGH && circularaquecimento == HIGH  && basetempo30seg >= tempocirculacaoaquecimento){
  circularaquecimento = LOW;
  tempocirculacaoaquecimento = basetempo30seg + SetTempoBombaCircDesl;
  

  }

}   
          // Fim controle_bomba_aq




                        //Função aciona as saídas de aquecimento e filtragem
 void acionarSaidas(){ 

    if (aquecendo == HIGH && circulacaodeprotecao == LOW){
    digitalWrite(bomba1, HIGH);
    lcd.setCursor(0, 3);
    lcd.print(F("Aquecendo"));

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
    lcd.print("Aqu.Desl.");
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
         // lcd.setCursor(10, 3);
         // lcd.print(F(" FILTRANDO"));
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

if (basetempo10seg >0){

  if (errosensor == LOW && temperaturaPainel /5 > SetTemperSuperAqEEPROM  || temperaturaPainel <= SetTemperDegeloEEPROM  ){



      //if (circulacaodeprotecao == LOW ){
       //  circulacaodeprotecao = HIGH;
        // tempobombaacioncircprot = basetempo10seg;
      //  }
 
      if (digitalRead(bomba1) == LOW && basetempo10seg >= tempobombaacioncircprot){
        acionamentocircprot = HIGH;
        tempobombaacioncircprot = basetempo10seg + SetTempoAcionBomba;
        tone(beepPin, 2700, 500);
        delay(100);
         tone(beepPin, 2700, 500);
         delay(100);
          tone(beepPin, 2700, 500);
          delay(100);
        
       }


  } else {
           //circulacaodeprotecao = LOW;

         }



  if (basetempo10seg >= tempobombaacioncircprot && digitalRead(bomba1) == HIGH){
     //digitalWrite(bomba1, LOW);
    acionamentocircprot = LOW;
    tempobombaacioncircprot = basetempo10seg + (SetTempoBombaDesl * 3); 
    
    circulacaodeprotecao = LOW;

   }

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
    lcd.setCursor(10, 3);
  lcd.print(F("Filt.Lg  "));
  lcd.setCursor(19, 3); 
  lcd.print(minutostimerregressivo);
  }


 
//filtragemdiaria = HIGH;


if (minutostimerregressivo > 0){
  filtragemdiaria = HIGH;
}else filtragemdiaria = LOW;




} // Fim do timer

       









void timerdiario (){  
  
 Serial.print(" ttmp - tetd: ");
Serial.print( tempotemperaturaminimapainel + tempoesperatimerdiario - basetempo30seg );

  if(basetempo30seg  >= ultimotimerdiario ){
    
   //ultimotimerdiario = basetempo30seg;




     if (basetempo30seg == ultimotimerdiario){
    //if (basetempo30seg > tempotemperaturaminimapainel + tempoesperatimerdiario){
      tempotemperaturaminimapainel = basetempo30seg + tempoesperatimerdiario ;
      temperaturabaixapainel = temperaturaPainel;
      tbp = temperaturabaixapainel ;
      tone(beepPin, 3500, 10);
       Serial.print("              total:");
    Serial.print(total);
      ultimotimerdiario = basetempo30seg - 1; 

    } else if (basetempo30seg == tempotemperaturaminimapainel ){
      ultimotimerdiario = basetempo30seg + tempointervalotimerdiario; 
      //temperaturabaixapainel = temperaturaPainel;
      //filtragemdiaria = HIGH;
      minutostimerregressivo =  minutostimerregressivo + SetTempoTimerdiario;
     // minutostimerregressivo =  minutostimerregressivo + 4;
     tempotemperaturaminimapainel = basetempo30seg + tempoesperatimerdiario;
     tone(beepPin, 3500, 100);
     } else if( basetempo30seg > ultimotimerdiario){
      ultimotimerdiario = basetempo30seg -1 ;
     }



     if (temperaturaPainel < temperaturabaixapainel){
  
        temperaturabaixapainel = temperaturaPainel;
        tempotemperaturaminimapainel = basetempo30seg + tempoesperatimerdiario + 1;
        //tempotemperaturaminimapainel = basetempo30seg + 10;
        //ultimotimerdiario = basetempo30seg;
         tbp = temperaturabaixapainel ;
        // temporegressivotd = tempoesperatimerdiario;

      }


  } else tempotemperaturaminimapainel = basetempo30seg  + tempoesperatimerdiario- 1 ; // -2 para evitar que o timer fique com valor negativo
  
    
  
  Serial.print(" total:");
    Serial.print(total);

    Serial.print(" basetempo30seg:");
    Serial.print(basetempo30seg);
    Serial.print(" tempotemperaturaminimapainel:");
    Serial.print(tempotemperaturaminimapainel);
    Serial.print(" ultimotimerdiario:");
    Serial.print(ultimotimerdiario);
    Serial.print(" minutostimerregressivo:");
    Serial.println(minutostimerregressivo);




if (basetempo30seg > ultimotimerdiario + SetTempoTimerdiario){
  filtragemdiaria = LOW;
}



Serial.print(" temperaturabaixapainel:");
Serial.print(temperaturabaixapainel);
//Serial.print(" ultimotimerdiario: ");
//Serial.print(ultimotimerdiario);  
//Serial.print(" Ult > bs30 - 1800: ");
//Serial.print(ultimotimerdiario - (basetempo30seg - 1800));

//if (buttonStateDw == HIGH){

if (tdstatus > 2){
    tdstatus = 1;
  }
  //tone(beepPin, 2600, 50);
  //delay(100);


if ( tdstatus == 1){

/*
   if (ultimotimerdiario >= basetempo30seg){

    temporegressivotd1 =  tempotemperaturaminimapainel - basetempo30seg ;


    }else temporegressivotd1 = 0;

    if (ultimotimerdiario >= basetempo30seg) {
     temporegressivotd2  = ultimotimerdiario - basetempo30seg ;






    } else if (ultimotimerdiario < basetempo30seg && ultimotimerdiario > 0) {
      temporegressivotd2 = ultimotimerdiario - basetempo30seg + SetTempoTimerdiario;
      //temporegressivotd2 = ultimotimerdiario - basetempo30seg + 1800;
    } else temporegressivotd2 = 0;


    */




         temporegressivotd1 = (  tempotemperaturaminimapainel - basetempo30seg) + (ultimotimerdiario - basetempo30seg );



  lcd.setCursor(14, 1);
  lcd.print(F("T"));
  //lcd.print(temporegressivotd);
  //lcd.print(ultimotimerdiario);


             //total = SetTempoBombaCircDesl * 30;
           //  horas = temporegressivotd / 120; //(total / 3600);
           //  minutos =  temporegressivotd / 2 ; //((total - (horas * 3600)) / 60);
           //  segundos = temporegressivotd * 3; // (total % 60);

             total = temporegressivotd1 + 2 ;//+ temporegressivotd2; ;//* 30;
             horas = (total / 120);
             minutos = ((total - (horas * 120)) / 2);
             //segundos = (total % 2);
             
             //lcd.setCursor(0, 3);
          if (horas < 10){
            lcd.print("0");
             }
             lcd.print(horas);
             lcd.print(":");
             //lcd.setCursor(5, 3);
          if (minutos < 10){
             lcd.print("0");
             }
             lcd.print(minutos);
             //lcd.print(":");
             //lcd.setCursor(8, 3);
         // if (segundos < 10){
          //    lcd.print("0");
          //    }
          //   lcd.print(segundos);

}

if ( tdstatus == 2){

  lcd.setCursor(13, 1);
  lcd.print(F("TBP"));
  lcd.print(tbp/10,1);
  //lcd.print(temperaturabaixapainel);

}




} // Fim da função timerdiario



void Fchamadamenu(){
  //chamadamenu = HIGH;
  buttonStateSet = HIGH;

  tempomenu = millis();
  //tone(beepPin, 2600, 50);
 }


 

void timerminutos(){
   
buttonStateUp = HIGH;
//tone(beepPin, 2800, 50);
  
if (chamadamenu == LOW){
  tone(beepPin, 2800, 50);
   if (minutostimerregressivo == 0){
       minutostimerregressivo = 2;
    } else minutostimerregressivo = minutostimerregressivo + 1;
//delay(100);
}
}