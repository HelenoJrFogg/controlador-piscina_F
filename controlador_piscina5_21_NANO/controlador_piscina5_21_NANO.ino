

////ARDUINO NANO///

#include <EEPROM.h>


//////////////////////Sensores
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS_PISC         3         // Pino do sensor da temperatura da piscina
#define ONE_WIRE_BUS_PAINEL       5         // Pino do sensor do painel de aquecimento
#define ONE_WIRE_BUS_RETORNO      4         // Pino sensor de retorno de agua
OneWire SensorPiscina(ONE_WIRE_BUS_PISC);
OneWire oneWire_out(ONE_WIRE_BUS_PAINEL);
OneWire oneWire_out_1(ONE_WIRE_BUS_RETORNO);
DallasTemperature sensor_piscina(&SensorPiscina);
DallasTemperature sensor_painel(&oneWire_out);
DallasTemperature sensor_retorno(&oneWire_out_1);



/////////////////////////////////////Botões:
//unsigned long lastDebounceTime = 0 ;

const int ledPin = 13;      // the number of the LED pin
int ledState = HIGH;         // the current state of the output pin

//int analogreading;
int debounceDelay = 50;    // the debounce time; increase if the output flickers

int buttonPinSet = 11;    // the number of the pushbutton pin
int buttonStateSet;             // the current reading from the input pin
bool lastButtonStateSet = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTimeSet = 0;  // the last time the output pin was toggled

int buttonPinUp = 10;    // the number of the pushbutton pin
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
   unsigned long tempochamarmenu = 0;
   bool estadochamarmenu;
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





//int s1;

bool memupdate = LOW ;
//1
int SetTemperPiscina;
float SetTemperPiscFloat;
int TemperPiscEEPROM;
//2
int SetTempInPainel;
float SetTempInPainelFloat;
int SetTempInPainelEEPROM;
//3
int SetDifTempEntrSaida;
float SetDifTemperEntrSaidaFloat;
int DifTemperEntrSaidaEEPROM;
//4
int SetTemperSuperAq;
float SetTemperSuperAqfloat;
int SetTemperSuperAqEEPROM;
//5
int SetTemperDegelo;
float SetTemperDegeloFloat;
int SetTemperDegeloEEPROM;
//6
int SetTempoAcionBomba;
float SetTempoAcionBombaFloat;
int SetTempoAcionBombaEEPROM;
//7
int SetTempoBombaDesl;
float SetTempoBombaDeslFloat;
int SetTempoBombaDeslEEPROM;
//8
int SetTempoAcionBombaCirc;
//float SetTempoAcionBombaCircFloat;
int SetTempoAcionBombaCircEEPROM;
//9
int SetTempoBombaCircDesl;
//float SetTempoBombaCircDeslFloat;
int SetTempoBombaCircDeslEEPROM;
//10
int SetDifTempEntrSaidabomba2;
float SetDifTemperEntrSaidabomba2Float;
int DifTemperEntrSaidabomba2EEPROM;



//float tempreal;
//float tempreal1;

#define bomba1       9 // pino acionamento da bomba de aquecimenti lento.
#define bomba2       8 // pino acionamento da bomba de aquecimento rapido.
#define bombafiltro  7 // pino acionamento da bomba de filtragem.


/////////////////////////////////////////


int contador = 0;
//boolean botaoset;
///boolean botaodw;
//boolean botaoup;


boolean chamadamenu = 0;
//int tempodemenu = 5000;

// diferença milisegundos
//unsigned long ti;
//static unsigned long tf;
//int tdif;
//static unsigned long tp1;

int segundos, minutos, horas, total, total1;

//unsigned long previousMillis;
//const long interval = 800; 

int temperaturapiscina;
int tempersaidaaquecedor;
int temperaturaPainel;

boolean disparoaquecerpiscina;
//boolean placaaquecida;
boolean difentrsaida;

boolean aquecendo;
boolean aquecendoT;
boolean circulacaodeprotecao = LOW;

unsigned long tbstart;
int tbstop;
unsigned long basetempo10seg;
unsigned long basetempo30seg;
int TAcionBomba;
int TIntervBomba;
boolean bomba1_acionada;
unsigned long tbomba;
unsigned long tempobombaacioncircprot; //tempo de acionamento da bomba no acionamento de proteção.
unsigned long tempointervdeprot;       // tempo de intervalo da bomba no acionamento de proteção. 

 unsigned long tempo;


 bool DisparoProtecao;

unsigned long tempoestabilizacao = 0;
int circularaquecimento;
unsigned long tempocirculacaoaquecimento =2;
int circulando = LOW;
int modoteste = 0;
int modotestesaidas ;



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

  
 

  
  pinMode(bomba1, OUTPUT);
  pinMode(bomba2, OUTPUT);
  pinMode(bombafiltro, OUTPUT);
  
  Serial.begin(9600);
  //Serial.println(" ");
  
  
 

//EEPROM.begin(50);


  
     lcd.init();
delay(500);
     lcd.backlight();
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("CONTROLADORES ");
       lcd.setCursor(0, 1);
       lcd.print("FOGGIATTO V2.1");
       delay(2000);
       lcd.clear();
       lcd.createChar(0, grau);
    
  //tp1 = -9000;
  
  TemperPiscEEPROM = EEPROM.read(0);
  SetTempInPainelEEPROM = EEPROM.read(1);
  DifTemperEntrSaidaEEPROM = EEPROM.read(2);
  SetTemperSuperAqEEPROM = EEPROM.read(3);
  SetTemperDegeloEEPROM = EEPROM.read(4)- 100;
  SetTempoAcionBombaEEPROM = EEPROM.read(5);
  SetTempoBombaDeslEEPROM = EEPROM.read(6);
  SetTempoAcionBombaCircEEPROM = EEPROM.read(7);
  SetTempoBombaCircDeslEEPROM = EEPROM.read(8);
  DifTemperEntrSaidabomba2EEPROM = EEPROM.read(9);
  
  SetTemperPiscFloat = TemperPiscEEPROM ;
  SetTempInPainelFloat = SetTempInPainelEEPROM;
  SetDifTemperEntrSaidaFloat = DifTemperEntrSaidaEEPROM;
  SetTemperSuperAqfloat = SetTemperSuperAqEEPROM;
  SetTemperDegeloFloat = SetTemperDegeloEEPROM;
  SetTempoAcionBombaFloat = SetTempoAcionBombaEEPROM;
  SetTempoBombaDeslFloat = SetTempoBombaDeslEEPROM;
  SetDifTemperEntrSaidabomba2Float = DifTemperEntrSaidabomba2EEPROM;
  //SetTempoAcionBombaCircFloat = SetTempoAcionBombaCircEEPROM;
  //SetTempoBombaCircDeslFloat = SetTempoBombaCircDeslEEPROM;
  
tbstart = millis()/ 10000;

 TAcionBomba = -1 - SetTempoAcionBombaEEPROM;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop(void){
    sensor_piscina.requestTemperatures();
    sensor_painel.requestTemperatures();
    sensor_retorno.requestTemperatures();
    
    //leituraanalogbotoes();
    controle_botaoSet();
    controle_botaoUp();
    controle_botaoDw();



    Serial.println("// piscina:");
   //Serial.print(sensor_piscina.getTempCByIndex(0));
    //Serial.print(" painel:");
    //Serial.print(sensor_painel.getTempCByIndex(0));
    //Serial.print(" retorno:");
    //Serial.print(sensor_retorno.getTempCByIndex(0),3);


    //Serial.print("// Set:");
    //Serial.print(buttonStateSet);
    //Serial.print("  Up");
    //Serial.print(buttonStateUp);
    //Serial.print("  Dw");
    //Serial.print(buttonStateDw);
    //Serial.print(" dif milis ");
   // Serial.println((millis()-difmillis));
//difmillis = millis();



/////////////Menu
if (buttonStateSet ==LOW){
  tempochamarmenu = millis();
}
//Serial.println(tempochamarmenu);

if ((buttonStateSet == HIGH && estadochamarmenu == LOW) && (millis()-  tempochamarmenu > 100)) {
//Serial.println(millis());
chamadamenu = HIGH;
contador = 0;
} 



 basetempo10seg = millis() / 10000;
 basetempo30seg = basetempo10seg / 3;

 lcd.setCursor(0, 2);
 lcd.print(basetempo10seg);
 lcd.print("<10/30>");
 lcd.print(basetempo30seg); 

 // unsigned long start = millis();
    //int botoes;
  //int tempomenu;
 
  SetTemperPiscina = TemperPiscEEPROM;
  SetTempInPainel = SetTempInPainelEEPROM;
  SetDifTempEntrSaida = DifTemperEntrSaidaEEPROM;
  SetTemperSuperAq = SetTemperSuperAqEEPROM;
  SetTemperDegelo = SetTemperDegeloEEPROM;
  SetTempoAcionBomba = SetTempoAcionBombaEEPROM;
  SetTempoBombaDesl = SetTempoBombaDeslEEPROM;
  SetTempoAcionBombaCirc = SetTempoAcionBombaCircEEPROM;
  SetTempoBombaCircDesl = SetTempoBombaCircDeslEEPROM;
  SetDifTempEntrSaidabomba2 = DifTemperEntrSaidabomba2EEPROM;
  
  
  
  




  
  if (chamadamenu != mudancaLCD){
      lcd.clear();
      mudancaLCD = chamadamenu;
      }
  
      //.println();
      //Serial.print("chamadamenu  ");
     //Serial.println(chamadamenu);
     // Serial.println("on");



while   (chamadamenu == HIGH){

    //leituraanalogbotoes();
    controle_botaoSet();
    controle_botaoUp();
    controle_botaoDw();




if ( buttonStateSet == HIGH || buttonStateUp == HIGH || buttonStateDw == HIGH){
       tempomenu = millis();
       botoes = HIGH;
    } else botoes = LOW;

 
 // Serial.print("millis()");
 //  Serial.print(millis());
  //Serial.println("menu_on");
  // Serial.println(botoes);
 // Serial.print("    tempomenu");
 //  Serial.println(tempomenu);
  //Serial.println("menu_on");


 if (millis() -  tempomenu > 10000) {
    
  chamadamenu = LOW;
  
  SetTemperPiscina = SetTemperPiscFloat;
  SetTempInPainel = SetTempInPainelFloat;
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
  
    }else{
 //   Serial.println(botoes);
 // Serial.println("menu_on");
  
  }



if ((botoes != ultimoestadobotoes)  || (millis() - whilelastTime > 500 ) ) {


           if (botoes == HIGH)  {
                    lcd.clear();
                    buttonPushCounter++;// if the current state is HIGH then the button went from off to on:
                    Serial;Serial.println("on");
                    Serial.print("number of button pushes: ");
                     Serial.println(buttonPushCounter);
                     //Serial.println(joyst_map);
                     
                         if (buttonPushCounter > 1) {
                            whilelastTime = millis()  - (buttonPushCounter * 100) ;  //              
                              } else whilelastTime = millis();



    
    
    if (buttonStateSet == HIGH){
        contador = contador + 1;
        lcd.clear();
         }
        
    if (contador > 11){
      contador = 1;
      }
     
      
      
 switch (contador){
      
   case 1:
        if (buttonStateUp == HIGH && SetTemperPiscFloat < 80){
            SetTemperPiscFloat = SetTemperPiscFloat + 1;
            }
             
        if (buttonStateDw == HIGH && SetTemperPiscFloat > 40){
            SetTemperPiscFloat = SetTemperPiscFloat - 1;
            }
            
        lcd.setCursor(0, 0);
        lcd.print("1 Temperatura Maxima");                    
        lcd.setCursor(0, 1);
        lcd.print("   de aquecimento");                    
        lcd.setCursor(0, 2);
        lcd.print("    da Piscina");
        lcd.setCursor(3, 3);
        lcd.print(SetTemperPiscFloat/2,1);
          lcd.setCursor(7, 3);
          lcd.write((byte)0);
          lcd.print("  >  ");
          lcd.print(SetTemperPiscFloat);
       break; 
       
       case 2:
        if (buttonStateUp == HIGH && SetTempInPainelFloat < 100){
            SetTempInPainelFloat = SetTempInPainelFloat + 1;
            }
             
        if (buttonStateDw == HIGH && SetTempInPainelFloat > 50){
          SetTempInPainelFloat = SetTempInPainelFloat - 1;
            }
            
        lcd.setCursor(0, 0);
        lcd.print("2 Temperatura Painel");                    
        lcd.setCursor(0, 1);
        lcd.print(" de inicio");                    
        lcd.setCursor(0, 2);
        lcd.print(" do aquecimento");
        lcd.setCursor(3, 3);
        lcd.print(SetTempInPainelFloat/2,1);
          lcd.setCursor(7, 3);
          lcd.write((byte)0);
          lcd.print("  >  ");
          lcd.print(SetTempInPainelFloat);
       break; 

  case 3:
        if (buttonStateUp == HIGH && SetDifTemperEntrSaidaFloat <= 99){
          SetDifTemperEntrSaidaFloat = SetDifTemperEntrSaidaFloat + 1;
          }
        
        if (buttonStateDw == HIGH && SetDifTemperEntrSaidaFloat > 0){
            SetDifTemperEntrSaidaFloat = SetDifTemperEntrSaidaFloat - 1;
            }
            lcd.setCursor(0, 0);
            lcd.print("3 Ganho minimo de");
            lcd.setCursor(0, 1);
            lcd.print("Temperatura do");
            lcd.setCursor(0, 2);
            lcd.print(" Sistema ligado");
            lcd.setCursor(3, 3);
            lcd.print(SetDifTemperEntrSaidaFloat/10);
            lcd.setCursor(8, 3);
            lcd.write((byte)0);
            lcd.print(">");
            lcd.print(SetDifTemperEntrSaidaFloat);
                      
          break;

        
   case 4:
        if (buttonStateUp == HIGH && SetTemperSuperAqfloat < 140){
            SetTemperSuperAqfloat = SetTemperSuperAqfloat + 1;
            }
        if (buttonStateDw == HIGH && SetTemperSuperAqfloat > 100){
            SetTemperSuperAqfloat = SetTemperSuperAqfloat - 1;
            }
        lcd.setCursor(0, 0);
        lcd.print("4 Temperatura de");
        lcd.setCursor(0, 1);
        lcd.print("acionam. da protecao");
        lcd.setCursor(0, 2);
        lcd.print("por calor do painel");
        lcd.setCursor(3, 3);
        lcd.print(SetTemperSuperAqfloat /2 );

            lcd.setCursor(7, 3);
            lcd.write((byte)0);
            lcd.print(">" );
            lcd.print(SetTemperSuperAqfloat);

       break;


    case 5:
        if (buttonStateUp == HIGH && SetTemperDegeloFloat < 160){
          SetTemperDegeloFloat = SetTemperDegeloFloat + 1;
          }
        
        if (buttonStateDw == HIGH && SetTemperDegeloFloat > 50){
            SetTemperDegeloFloat = SetTemperDegeloFloat - 1;
            }
            lcd.setCursor(0, 0);
            lcd.print("5 Temperatura Protec");
            lcd.setCursor(0, 1);
            lcd.print("do Anticongelamento");
            lcd.setCursor(0, 2);
            lcd.print(" do Painel");
            lcd.setCursor(5, 3);
            lcd.print((SetTemperDegeloFloat/10) -10);
            lcd.setCursor(10, 3);
            lcd.write((byte)0);
            lcd.print(">");
            lcd.print(SetTemperDegeloFloat);
        break;

  

        
    case 6:
        if (buttonStateUp == HIGH && SetTempoAcionBombaFloat <= 80){
            SetTempoAcionBombaFloat = SetTempoAcionBombaFloat + 1;
            }
        if (buttonStateDw == HIGH && SetTempoAcionBombaFloat > 0){
           SetTempoAcionBombaFloat = SetTempoAcionBombaFloat - 1;
           }
           lcd.setCursor(0, 0);
           lcd.print("6 Tempo de Acionamen");
            lcd.setCursor(0, 1);
           lcd.print("to da Bomba do");
           lcd.setCursor(0, 2);
           lcd.print("ciclo de Protecao");
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
          
    
     case 7:       
        if (buttonStateUp == HIGH && SetTempoBombaDeslFloat <= 239){
            SetTempoBombaDeslFloat = SetTempoBombaDeslFloat + 1;
            }
        if (buttonStateDw == HIGH && SetTempoBombaDeslFloat > 0){
           SetTempoBombaDeslFloat = SetTempoBombaDeslFloat - 1;
           }
           lcd.setCursor(0, 0);
           lcd.print("7 Tempo de intervalo");
           lcd.setCursor(0, 1);
           lcd.print("de Bomba desligada");
           lcd.setCursor(1, 2);
           lcd.print("do ciclo d protecao");
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

        
       case 8:
          if (buttonStateUp == HIGH && SetTempoAcionBombaCirc < 240){
              SetTempoAcionBombaCirc = SetTempoAcionBombaCirc + 1;
              }
          if (buttonStateDw == HIGH && SetTempoAcionBombaCirc > 0){
             SetTempoAcionBombaCirc = SetTempoAcionBombaCirc - 1;
             }
             lcd.setCursor(0, 0);
             lcd.print("8 Tempo de Acionamen");
              lcd.setCursor(0, 1);
             lcd.print("to da Bomba do");
             lcd.setCursor(0, 2);
             lcd.print("ciclo de circulacao");
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
            
      
       case 9:       
          if (buttonStateUp == HIGH && SetTempoBombaCircDesl < 240){
              SetTempoBombaCircDesl = SetTempoBombaCircDesl + 1;
              }
          if (buttonStateDw == HIGH && SetTempoBombaCircDesl > 0){
             SetTempoBombaCircDesl = SetTempoBombaCircDesl - 1;
             }
             lcd.setCursor(0, 0);
             lcd.print("9 Tempo de intervalo");
             lcd.setCursor(0, 1);
             lcd.print("de Bomba desligada");
             lcd.setCursor(1, 2);
             lcd.print("do ciclo d circulacao");
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

       case 10:
            if (buttonStateUp == HIGH && SetDifTemperEntrSaidabomba2Float <= 99){
              SetDifTemperEntrSaidabomba2Float = SetDifTemperEntrSaidabomba2Float + 1;
              }
            
            if (buttonStateDw == HIGH && SetDifTemperEntrSaidabomba2Float > 0){
                SetDifTemperEntrSaidabomba2Float = SetDifTemperEntrSaidabomba2Float - 1;
                }
                lcd.setCursor(0, 0);
                lcd.print("10 Ganho minimo de");
                lcd.setCursor(0, 1);
                lcd.print("Temperatura de");
                lcd.setCursor(0, 2);
                lcd.print(" Acion. Bomba2");
                lcd.setCursor(3, 3);
                lcd.print(SetDifTemperEntrSaidabomba2Float/10);
                lcd.setCursor(8, 3);
                lcd.write((byte)0);
                lcd.print(">");
                lcd.print(SetDifTemperEntrSaidabomba2Float);
                          
              break; 

       case 11:
             //lcd.clear();
             lcd.setCursor(0, 0);
             lcd.print("11 Entrar no MODO");
             lcd.setCursor(0, 1);
             lcd.print("de TESTE das Saidas");
             lcd.setCursor(1, 3);
             lcd.print("ACEITAR: tecla >");

             
             if (buttonStateUp == HIGH ){
                 modotestesaidas = HIGH;
              //   Serial.print("                                                                                      MODOTESTESAIDAS");
             //Serial.println(buttonStateUp);
                }
             

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
 
 

            
            if (buttonStateUp == HIGH ){
                modoteste = modoteste + 1;
                }  

              if (modoteste > 3){
                  modoteste = 1;
                }
   
             
        switch (modoteste)
         {
         case 1:
             lcd.setCursor(0, 0);
             lcd.print("1 Bomba Aquecimento");
             lcd.setCursor(0, 1);
             lcd.print("Lig/Desl: Tecla SET");
             lcd.setCursor(1, 2);
             lcd.print("Sair: Tecla <");

             if (buttonStateSet == HIGH){
              aquecendo = !aquecendo;
              }


              if (aquecendo == HIGH){
                lcd.setCursor(0, 3);
                lcd.print("Bomba Aquec. Ligada");
                } else  {
                  lcd.setCursor(0, 3);
                  lcd.print("Bomba Aq. Desligada");
                }
                break;
          case 2:
              lcd.setCursor(0, 0);
              lcd.print("2 Bomba Aquecimento2");
              //lcd.setCursor(0, 1);
              //lcd.print("Lig/Desl: Tecla SET");
              //lcd.setCursor(1, 2);
              //lcd.print("Sair: Tecla <");

              if (buttonStateSet == HIGH){
                aquecendoT = !aquecendoT;
                }


                if (aquecendoT == HIGH){
                  lcd.setCursor(0, 3);
                  lcd.print("Bomba Aq2 Ligada   ");
                  } else  {
                    lcd.setCursor(0, 3);
                    lcd.print("Bomba Aq2 Desligada");
                  }
                  break;
     
      case 3:
          lcd.setCursor(0, 0);
          lcd.print("3 Bomba de Filtragem");
          //lcd.setCursor(0, 1);
          //lcd.print("Lig/Desl: Tecla SET");
          //lcd.setCursor(1, 2);
          //lcd.print("Sair: Tecla <");
          

          if (buttonStateSet == HIGH){
            circularaquecimento = !circularaquecimento;
            }


            if (circularaquecimento == HIGH){
              lcd.setCursor(0, 3);
              lcd.print("Bomba Filtro Ligada ");
              } else  {
                lcd.setCursor(0, 3);
                lcd.print("BombFiltro Desligada");
              }
              break;
     
     
    default:
    break;
     }//switch 

              if (buttonStateDw == HIGH ){
                 modotestesaidas = LOW;
                 chamadamenu = LOW;
                Serial.print("                                                                                      MODOTESTESAIDAS");
             Serial.println(buttonStateUp);
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
    }//switch
   // return;


} else {
           buttonPushCounter = 0;
            // Serial.println("off");// if the current state is LOW then the button went from on to off:
           }



ultimoestadobotoes = botoes ; 

   
  } //fim do if




 // Serial.println("fim do while");

 delay(100);

 }  //////////////////////// fim do while
  
  


  


  temperaturapiscina = 10 * sensor_piscina.getTempCByIndex(0);
  temperaturaPainel = 10 * sensor_painel.getTempCByIndex(0);
  tempersaidaaquecedor = 10 * sensor_retorno.getTempCByIndex(0);
  
  Serial.print("  tempPisc: ");
  Serial.print(temperaturapiscina);
  Serial.print("< >");
  //Serial.print("  tempPisc: ");
  Serial.print(EEPROM.read(0));
  Serial.print(" <<< ");
  
  
//  Serial.println(leitura0);
    lcd.setCursor(0, 0);
    lcd.print("Pisc:");
    lcd.print(sensor_piscina.getTempCByIndex(0), 2);
    lcd.setCursor(11, 0);
    lcd.print("Ret:");
    lcd.print(sensor_retorno.getTempCByIndex(0), 2);
    lcd.setCursor(0, 1);
    lcd.print("Pain:");
    lcd.print(sensor_painel.getTempCByIndex(0),2);

    lcd.setCursor(11, 1);
    lcd.print("Ganh:");
    lcd.print(  sensor_retorno.getTempCByIndex(0) - sensor_piscina.getTempCByIndex(0),2);
         
    lcd.setCursor(0, 3);
    lcd.print(temperaturaPainel / 5);
    // lcd.print("Bomba:");
    // if (digitalRead(bomba1) == 1){
    // lcd.print("AQUECENDO");
    //  } else    lcd.print(" Desligada");

// unsigned long stop = millis();

    lcd.print("CP:");
    lcd.print(circulacaodeprotecao);

    lcd.setCursor(12, 2);
    lcd.print("tp:");
    lcd.print(temperaturaPainel);


  

 if ((temperaturaPainel / 5  >  SetTemperSuperAqEEPROM ) || (temperaturaPainel < SetTemperDegeloEEPROM - 100 ) && millis() > 10000) 
     {
       circulacaodeprotecao = HIGH;
     }  
   
   
   
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
     

      controle_bomba_aq();

 
}


/////////Fim do Loop//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////Função botão
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
                // only toggle the LED if the new button state is HIGH
               //if (buttonState == HIGH) {
              //  ledState = !ledState;
              //}
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
                // only toggle the LED if the new button state is HIGH
               //if (buttonState == HIGH) {
              //  ledState = !ledState;
              //}
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
                // only toggle the LED if the new button state is HIGH
               //if (buttonState == HIGH) {
              //  ledState = !ledState;
              //}
      }
  }
  lastButtonStateDw = reading;
  }




  void  atualizaeeprom(){
//    Serial.print();
Serial.print("SetTemperPiscina: ");
Serial.print(SetTemperPiscina);
Serial.print(" TemperPiscEEPROM:");
Serial.println(TemperPiscEEPROM);
    
   if (SetTemperPiscFloat != TemperPiscEEPROM){
      EEPROM.write(0, (SetTemperPiscFloat ));
      memupdate = HIGH;  
      }
      if (SetTempInPainelFloat != SetTempInPainelEEPROM){
        EEPROM.write(1, (SetTempInPainelFloat ));
        memupdate = HIGH;  
        }
   if (SetDifTempEntrSaida != DifTemperEntrSaidaEEPROM){
      EEPROM.write(2, SetDifTempEntrSaida);
      memupdate = HIGH;
      } 
  if (SetTemperSuperAqEEPROM != SetTemperSuperAq){
      EEPROM.write(3, SetTemperSuperAq);
      memupdate = HIGH;
      }
  if (SetTemperDegelo != SetTemperDegeloEEPROM){
      EEPROM.write(4, SetTemperDegelo + 100);
      memupdate = HIGH;  
      }    
  if (SetTempoAcionBomba != SetTempoAcionBombaEEPROM){
      EEPROM.write(5, SetTempoAcionBomba);
      memupdate = HIGH;
      }
  if (SetTempoBombaDesl != SetTempoBombaDeslEEPROM){
      EEPROM.write(6, SetTempoBombaDesl);
      memupdate = HIGH;
      }
      if (SetTempoAcionBombaCirc != SetTempoAcionBombaCircEEPROM){
        EEPROM.write(7, SetTempoAcionBombaCirc);
        memupdate = HIGH;
        }
    if (SetTempoBombaCircDesl != SetTempoBombaCircDeslEEPROM){
        EEPROM.write(8, SetTempoBombaCircDesl);
        memupdate = HIGH;
        }
        if (SetDifTempEntrSaidabomba2 != DifTemperEntrSaidabomba2EEPROM){
          EEPROM.write(9, SetDifTempEntrSaidabomba2);
          memupdate = HIGH;
          } 

    if (memupdate == HIGH){
   //   EEPROM.commit();
      memupdate = LOW;
      
      Serial.println("atualiza memoria");
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("Salvando na memoria");
            //lcd.setCursor(0, 1);
           //lcd.print("    memoria");
        delay(3000);
            
    TemperPiscEEPROM = EEPROM.read(0);
    SetTempInPainelEEPROM = EEPROM.read(1);
    DifTemperEntrSaidaEEPROM = EEPROM.read(2);
    SetTemperSuperAqEEPROM = EEPROM.read(3);
    SetTemperDegeloEEPROM = EEPROM.read(4)- 100;
    SetTempoAcionBombaEEPROM = EEPROM.read(5);
    SetTempoBombaDeslEEPROM = EEPROM.read(6);
    SetTempoAcionBombaCircEEPROM = EEPROM.read(7);
    SetTempoBombaCircDeslEEPROM = EEPROM.read(8);
    DifTemperEntrSaidabomba2EEPROM = EEPROM.read(9);
     }
    }

    //////////Função TEMPORIZADOR/////
    void timer (){






    }


    ////////////////////////////// Função controle da bomba aquecimento

void controle_bomba_aq(){
  //Liga Aquecimento////////////////////////////////////////
 //     if (temperaturapiscina < SetTemperPiscFloat * 5 && temperaturaPainel >= SetTempInPainelFloat * 5 ){ 
      if (temperaturapiscina + 3 < TemperPiscEEPROM * 5 && temperaturaPainel >= SetTempInPainelEEPROM * 5 ){ 
        lcd.setCursor(10, 3);
        lcd.print("   AQUEC");
        aquecendo = HIGH; 
   tempoestabilizacao = basetempo10seg + 6;
   
  
  } 
      
      Serial.print(basetempo10seg);
      Serial.print(tempoestabilizacao);
   
//Desliga Aquecimento////////////////////////////////////////   
//if (sensor_retorno.getTempCByIndex(0) - sensor_piscina.getTempCByIndex(0)  < SetDifTempEntrSaida / 10 && basetempo10seg > tempoestabilizacao ){// 
if (aquecendo == HIGH && basetempo10seg > tempoestabilizacao || temperaturapiscina >= TemperPiscEEPROM * 5 ){ 
   if (tempersaidaaquecedor - temperaturapiscina  < SetDifTempEntrSaida  ){
    //lcd.setCursor(10, 3);
    //lcd.print("   DESLIG");
    //aquecendo = LOW;
    //}
    aquecendo = LOW;
    lcd.setCursor(9, 3);
    lcd.print(" deslig   ");
aquecendo = LOW;
    
}
  
}

//Liga Desliga modo turbo bomba 2////////////////////////////////////////
  if (aquecendo == HIGH && tempersaidaaquecedor - temperaturapiscina > SetDifTempEntrSaidabomba2){
  
    lcd.setCursor(19, 3);
    lcd.print("T");

    }else{
      lcd.setCursor(19, 3);
      lcd.print(" ");
      }

  
// Liga Circulação////////////////////////////////////////
if (aquecendo == HIGH && circularaquecimento == LOW && basetempo30seg >= tempocirculacaoaquecimento && SetTempoAcionBombaCirc > 0){
  circularaquecimento = HIGH;
  tempocirculacaoaquecimento = basetempo30seg + SetTempoAcionBombaCirc;
  
 lcd.setCursor(7, 3);
  lcd.print("C");

  }

 digitalWrite(ledPin, circularaquecimento) ; 

//Desliga Circulação////////////////////////////////////////
if (aquecendo == HIGH && circularaquecimento == HIGH  && basetempo30seg >= tempocirculacaoaquecimento){
  circularaquecimento = LOW;
  tempocirculacaoaquecimento = basetempo30seg + SetTempoBombaCircDesl;
  
  lcd.setCursor(7, 3);
  lcd.print("  ");

  }

//if (aquecendo == HIGH && circularaquecimento == HIGH && basetempo30seg > tempocirculacaoaquecimento + 2){
  //circularaquecimento = LOW;
  //tempocirculacaoaquecimento = basetempo30seg;

//}

//temperaturapiscina = 10 * sensor_piscina.getTempCByIndex(0);
//temperaturaPainel = 10 * sensor_painel.getTempCByIndex(0);
//tempersaidaaquecedor = 10 * sensor_retorno.getTempCByIndex(0);

}




///////////////////////////////

        void controle_bomba(){
{
  /* code */
}






      if (bomba1_acionada == HIGH){
        digitalWrite(bomba1, HIGH);
        }
        //else digitalWrite(bomba1, LOW);
        }  