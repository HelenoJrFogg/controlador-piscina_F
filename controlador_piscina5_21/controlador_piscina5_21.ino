



#include <EEPROM.h>


//////////////////////Sensores
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS_PISC 12
#define ONE_WIRE_BUS_PAINEL 13
#define ONE_WIRE_BUS_RETORNO 14
OneWire SensorPiscina(ONE_WIRE_BUS_PISC);
OneWire oneWire_out(ONE_WIRE_BUS_PAINEL);
OneWire oneWire_out_1(ONE_WIRE_BUS_RETORNO);
DallasTemperature sensor_piscina(&SensorPiscina);
DallasTemperature sensor_painel(&oneWire_out);
DallasTemperature sensor_retorno(&oneWire_out_1);



/////////////////////////////////////Botões:
int analogreading;
int buttonPinSet; //= 15;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin
int ledState = HIGH;         // the current state of the output pin
int buttonStateSet;             // the current reading from the input pin
bool lastButtonStateSet = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTimeSet = 0;  // the last time the output pin was toggled
int debounceDelay = 50;    // the debounce time; increase if the output flickers

 int buttonPinUp; // = 0;    // the number of the pushbutton pin
int buttonStateUp;             // the current reading from the input pin
bool lastButtonStateUp = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTimeUp = 0;  // the last time the output pin was toggled

 int buttonPinDw; // = 2;    // the number of the pushbutton pin
int buttonStateDw;             // the current reading from the input pin
bool lastButtonStateDw = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTimeDw = 0;  // the last time the output pin was toggled
/////////////////////////////////////////////////////////////////////////////////////////////
unsigned long difmillis =0;


   bool chamarMenu = 0;
   unsigned long tempochamarmenu = 0;
   bool estadochamarmenu;
   unsigned long lastDebounceTimeMenu = 0;
   bool mudancaLCD;
   unsigned long tempomenu;
   bool botoes = LOW;
   int buttonPushCounter = 0;
   unsigned long whilelastTime = 0;
   bool ultimoestadobotoes ;



   
//LCD...

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);



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

int setmem;
float setmemfloat;
int temperaturapiscinaEEPROM;

int settemperaturaacionbomba;
float setTemperAcionBombafloat;
int temperaturadeacionamentobombaEEPROM;

int setdiftempentrsaida;
float SetDifTemperEntrSaidaFloat;
int diftemperatudaentrsaidaEEPROM;

int settempacionbomba;
float SetTemperAcionBombaFloat;
int tempodeacionamentobombaEEPROM;

int setbombadesl;
float SetBomdaDeslFloat;
int bombadeslEEPROM;

int settemperdegelo;
float SetTemperDegeloFloat;
int temperdegeloEEPROM;



float tempreal;
float tempreal1;
int bomba = 2;// pino acionamento da bomba



/////////////////////////////////////////





int contador = 0;
boolean botaoset;
boolean botaodw;
boolean botaoup;


boolean chamadamenu = 0;
int tempodemenu = 5000;

// diferença milisegundos
unsigned long ti;
static unsigned long tf;
int tdif;
static unsigned long tp1;

int segundos, minutos, horas, total, total1;

unsigned long previousMillis;
const long interval = 800; 

int temperaturapiscina;
int tempersaidaaquecedor;
int temperaturaplaca;

boolean disparoaquecerpiscina;
boolean placaaquecida;
boolean difentrsaida;
boolean circularagua;
boolean aquecendo;
boolean circulacaodeprotecao;

unsigned long tbstart;
int tbstop;
unsigned long basetempo10seg;
unsigned long basetempo30seg;
int TAcionBomba;
int TIntervBomba;
boolean bombacionada;
unsigned long tbomba;
unsigned long tempobombaacioncircprot; //tempo de acionamento da bomba no acionamento de proteção.
unsigned long tempointervdeprot;       // tempo de intervalo da bomba no acionamento de proteção. 

 unsigned long tempo;


void setup(void)


{

    sensor_piscina.begin();
    sensor_painel.begin();
    sensor_retorno.begin();
    sensor_piscina.setWaitForConversion(false);
    sensor_painel.setWaitForConversion(false);
    sensor_retorno.setWaitForConversion(false);


    // pinMode(buttonPinSet, INPUT);
    //pinMode(buttonPinUp, INPUT);
   // pinMode(buttonPinDw, INPUT);

  
 

  
  pinMode(bomba, OUTPUT);
  
  Serial.begin(115200);
  Serial.println(" ");
  
  
 

EEPROM.begin(50);


  
     lcd.init();

     lcd.backlight();
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("CONTROLADORES ");
       lcd.setCursor(0, 1);
       lcd.print("FOGGIATTO V2.0");
       delay(2000);
       lcd.clear();
       lcd.createChar(0, grau);
    
  tp1 = -9000;
  
  temperaturapiscinaEEPROM = EEPROM.read(0);
  diftemperatudaentrsaidaEEPROM = EEPROM.read(1);
  temperaturadeacionamentobombaEEPROM = EEPROM.read(2);
  temperdegeloEEPROM = EEPROM.read(3)- 100;
  tempodeacionamentobombaEEPROM = EEPROM.read(4);
  bombadeslEEPROM = EEPROM.read(5);
  
  
  setmemfloat = temperaturapiscinaEEPROM ;
  SetDifTemperEntrSaidaFloat = diftemperatudaentrsaidaEEPROM;
  setTemperAcionBombafloat = temperaturadeacionamentobombaEEPROM;
  SetTemperDegeloFloat = temperdegeloEEPROM;
  SetTemperAcionBombaFloat = tempodeacionamentobombaEEPROM;
  SetBomdaDeslFloat = bombadeslEEPROM;
  
tbstart = millis()/ 10000;

 TAcionBomba = -1 - tempodeacionamentobombaEEPROM;
}





void loop(void){
    sensor_piscina.requestTemperatures();
    sensor_painel.requestTemperatures();
    sensor_retorno.requestTemperatures();
    
    leituraanalogbotoes();
    controle_led_botaoSet();
    controle_led_botaoUp();
    controle_led_botaoDw();



    Serial.print("// piscina:");
    Serial.print(sensor_piscina.getTempCByIndex(0));
    Serial.print(" painel:");
    Serial.print(sensor_painel.getTempCByIndex(0));
    Serial.print(" retorno:");
    Serial.print(sensor_retorno.getTempCByIndex(0),3);


    Serial.print("// Set:");
    Serial.print(buttonStateSet);
    Serial.print("  Up");
    Serial.print(buttonStateUp);
    Serial.print("  Dw");
    Serial.print(buttonStateDw);
    Serial.print(" dif milis ");
   // Serial.println((millis()-difmillis));
difmillis = millis();



/////////////Menu
if (buttonStateSet ==LOW){
  tempochamarmenu = millis();
}
Serial.println(tempochamarmenu);

if ((buttonStateSet == HIGH && estadochamarmenu == LOW) && (millis()-  tempochamarmenu > 3000)) {
Serial.println(millis());
chamadamenu = HIGH;
contador = 0;
} 



 basetempo10seg = millis() / 10000;
 basetempo30seg = basetempo10seg / 3;

  unsigned long start = millis();
    //int botoes;
  int tempomenu;
 
  setmem = temperaturapiscinaEEPROM;
  setdiftempentrsaida = diftemperatudaentrsaidaEEPROM;
  settemperaturaacionbomba = temperaturadeacionamentobombaEEPROM;
  settemperdegelo = temperdegeloEEPROM;
  settempacionbomba = tempodeacionamentobombaEEPROM;
  setbombadesl = bombadeslEEPROM;
  
  
  




  
  if (chamadamenu != mudancaLCD){
      lcd.clear();
      mudancaLCD = chamadamenu;
      }
  
  
while     (chamadamenu == HIGH){

    leituraanalogbotoes();
    controle_led_botaoSet();
    controle_led_botaoUp();
    controle_led_botaoDw();




if ( buttonStateSet ==HIGH || buttonStateUp == HIGH || buttonStateDw == HIGH){
  tempomenu = millis();
  botoes = HIGH;
  } else botoes = LOW;


 if (millis() -  tempomenu > 10000) {
     chamadamenu = LOW;
  
  setmem = setmemfloat;
  setdiftempentrsaida = SetDifTemperEntrSaidaFloat;
  settemperaturaacionbomba = setTemperAcionBombafloat;
  settemperdegelo = SetTemperDegeloFloat;
  settempacionbomba = SetTemperAcionBombaFloat;
  setbombadesl = SetBomdaDeslFloat;
  
  
     
     atualizaeeprom();//funcao atualiza memoria

  }



if ((botoes != ultimoestadobotoes)  || (millis() - whilelastTime > 1000 ) ) {


           if (botoes == HIGH)  {
                    lcd.clear();
                    buttonPushCounter++;// if the current state is HIGH then the button went from off to on:
                    Serial.println("on");Serial.println("on");
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
        
    if (contador > 6)    {
      contador = 1;
      }
     
      
      
 switch (contador){
      
   case 1:
        if (buttonStateUp == HIGH && setmemfloat < 80){
            setmemfloat = setmemfloat + 1;
            }
             
        if (buttonStateDw == HIGH && setmemfloat > 40){
            setmemfloat = setmemfloat - 1;
            }
            
        lcd.setCursor(0, 0);
        lcd.print("1 Temperatura Maxima");                    
        lcd.setCursor(3, 1);
        lcd.print("da Piscina");                    
        //lcd.setCursor(0, 0);
        //lcd.print("1 Temperatura Maxima");
        lcd.setCursor(3, 3);
        lcd.print(setmemfloat/2,1);
          lcd.setCursor(7, 3);
          lcd.write((byte)0);
       break; 
       
  case 2:
        if (buttonStateUp == HIGH && SetDifTemperEntrSaidaFloat <= 99){
          SetDifTemperEntrSaidaFloat = SetDifTemperEntrSaidaFloat + 1;
          }
        
        if (buttonStateDw == HIGH && SetDifTemperEntrSaidaFloat > 0){
            SetDifTemperEntrSaidaFloat = SetDifTemperEntrSaidaFloat - 1;
            }
            lcd.setCursor(0, 0);
            lcd.print("2 Ganho minimo de");
            lcd.setCursor(0, 1);
            lcd.print("temperatura do");
            lcd.setCursor(0, 2);
            lcd.print("painel");
            lcd.setCursor(3, 3);
            lcd.print(SetDifTemperEntrSaidaFloat/10);
            lcd.setCursor(8, 3);
            lcd.write((byte)0);
                      
          break;

        
   case 3:
        if (buttonStateUp == HIGH && setTemperAcionBombafloat < 140){
            setTemperAcionBombafloat = setTemperAcionBombafloat + 1;
            }
        if (buttonStateDw == HIGH && setTemperAcionBombafloat > 100){
            setTemperAcionBombafloat = setTemperAcionBombafloat - 1;
            }
        lcd.setCursor(0, 0);
        lcd.print("3 Temperatura de");
        lcd.setCursor(0, 1);
        lcd.print("Acionamento da bomba");
        lcd.setCursor(0, 2);
        lcd.print("Protecao por calor");
        lcd.setCursor(3, 3);
        lcd.print(setTemperAcionBombafloat /2 );

            lcd.setCursor(7, 3);
            lcd.write((byte)0);

       break;


          case 4:
        if (buttonStateUp == HIGH && SetTemperDegeloFloat < 160){
          SetTemperDegeloFloat = SetTemperDegeloFloat + 1;
          }
        
        if (buttonStateDw == HIGH && SetTemperDegeloFloat > 50){
            SetTemperDegeloFloat = SetTemperDegeloFloat - 1;
            }
            lcd.setCursor(0, 0);
            lcd.print("4 Temperatra de Inicio");
            lcd.setCursor(5, 1);
            lcd.print("do Degelo");
            //lcd.setCursor(0, 0);
            //lcd.print("6 Temperatra deInicDegelo");
            lcd.setCursor(5, 3);
            lcd.print((SetTemperDegeloFloat/10) -10);
            lcd.setCursor(10, 3);
            lcd.write((byte)0);
        break;

  

        
    case 5:
        if (buttonStateUp == HIGH && SetTemperAcionBombaFloat <= 80){
            SetTemperAcionBombaFloat = SetTemperAcionBombaFloat + 1;
            }
        if (buttonStateDw == HIGH && SetTemperAcionBombaFloat > 0){
           SetTemperAcionBombaFloat = SetTemperAcionBombaFloat - 1;
           }
           lcd.setCursor(0, 0);
           lcd.print("5 Tempo de Acionamen");
            lcd.setCursor(0, 1);
           lcd.print("to da Bomba");
           lcd.setCursor(0, 2);
           lcd.print("(ciclo Circalacao)");
           // lcd.print(SetTemperAcionBombaFloat);
           total = SetTemperAcionBombaFloat * 10;
           horas = (total / 3600);
           minutos = ((total - (horas * 3600)) / 60);
           segundos = (total % 60);

              // lcd.setCursor(0, 1);
              // lcd.print(total);

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
          break;
          
    
     case 6:       
        if (buttonStateUp == HIGH && SetBomdaDeslFloat <= 239){
            SetBomdaDeslFloat = SetBomdaDeslFloat + 1;
            }
        if (buttonStateDw == HIGH && SetBomdaDeslFloat > 0){
           SetBomdaDeslFloat = SetBomdaDeslFloat - 1;
           }
           lcd.setCursor(0, 0);
           lcd.print("6 Tempo minimo do");
           lcd.setCursor(0, 1);
           lcd.print("Intervalo de Bomba");
           lcd.setCursor(3, 2);
           lcd.print("Desligada");
           // lcd.print(SetTemperAcionBombaFloat);
           total = SetBomdaDeslFloat * 30;
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
          break;

        

        
      default:
        contador = 0;
    }
   // return;


} else {
           buttonPushCounter = 0;
            // Serial.println("off");// if the current state is LOW then the button went from on to off:
           }



ultimoestadobotoes = botoes ; 

   
  } //fim do if




 // Serial.println("fim do while");

 delay(100);
 }  //fim do while
  
  


  


  temperaturapiscina = 10 * sensor_piscina.getTempCByIndex(0);
  temperaturaplaca = 10 * sensor_painel.getTempCByIndex(0);
  tempersaidaaquecedor = 10 * sensor_retorno.getTempCByIndex(0);
  
  Serial.print("  tempPisc: ");
  Serial.print(temperaturapiscina);
  Serial.print("< >");
  //Serial.print("  tempPisc: ");
  Serial.print(EEPROM.read(0));
  Serial.print(" <<< ");
  
  
//  Serial.println(leitura0);
    lcd.setCursor(0, 0);
    lcd.print("Pi:");
    lcd.print(sensor_piscina.getTempCByIndex(0), 2);
    lcd.setCursor(9, 0);
    lcd.print("Aq:");
    lcd.print(sensor_retorno.getTempCByIndex(0), 2);
    lcd.setCursor(0, 1);
    lcd.print("Pa:");
    lcd.print(sensor_painel.getTempCByIndex(0),2);

    lcd.setCursor(9, 1);
    lcd.print("Dif:");
    lcd.print(sensor_piscina.getTempCByIndex(0) - sensor_retorno.getTempCByIndex(0));
    
    
     
    lcd.setCursor(0, 3);
    lcd.print(temperaturaplaca / 5);
   // lcd.print("Bomba:");
    if (digitalRead(bomba) == 1){
      lcd.print("    Ligada");
      } else    lcd.print(" Desligada");

   // lcd.setCursor(7, 3);
   // lcd.print("sTfl:");
   // lcd.print(setTemperAcionBombafloat); 



  // Serial.print(sensors.getResolution(s1), DEC);
 // lcd.setCursor(9, 3);
   // lcd.print(temperaturapiscinaEEPROM);
 // lcd.print(" ");
 // lcd.print(tempreal1);
unsigned long stop = millis();

 //Serial.print("Time used: ");
 // Serial.println(stop - start);
  //Serial.print("\n\n\n");

  lcd.setCursor(0, 2);
    lcd.print("CP:");
    lcd.print(circulacaodeprotecao);

    lcd.setCursor(10, 2);
    lcd.print("tp:");
    lcd.print(temperaturaplaca);


  

 if ((temperaturaplaca / 5  >  temperaturadeacionamentobombaEEPROM ) || (temperaturaplaca < temperdegeloEEPROM - 100 ) && millis() > 10000) 
     {
       circulacaodeprotecao = HIGH;
       
   if ((temperaturaplaca >= (temperaturadeacionamentobombaEEPROM /5) + 40) || (temperaturaplaca * 10 < temperdegeloEEPROM))
        {
          digitalWrite(bomba, HIGH);
         tempo = basetempo10seg;
        }
      else{
        if (tempo + 6 <= basetempo10seg ){
             digitalWrite(bomba, LOW);
             }
        }
      }
       else { circulacaodeprotecao = LOW;

              tempointervdeprot = basetempo30seg;
              tempobombaacioncircprot = basetempo10seg;
      


if (temperaturaplaca * 2 >= temperaturadeacionamentobombaEEPROM && circulacaodeprotecao == LOW ){
      disparoaquecerpiscina = HIGH;
      TAcionBomba = basetempo10seg;
      }
       else {disparoaquecerpiscina = LOW;
        
      }




int difT = temperaturapiscina * 10 + diftemperatudaentrsaidaEEPROM;
int temperAq = tempersaidaaquecedor * 10;

if (  temperAq >= difT){
    difentrsaida = HIGH;
    TAcionBomba = basetempo10seg;
    }
    else difentrsaida = LOW; 



 int ligarbomba;
 


 tbomba = basetempo10seg - TAcionBomba;

 if ( (tbomba  < tempodeacionamentobombaEEPROM) || disparoaquecerpiscina == HIGH )  {
     bombacionada = HIGH;
     //digitalWrite(bomba, HIGH);
     }
 else{bombacionada = LOW;
    // digitalWrite(bomba, LOW);
     }


      }
     

  

 
}


/////////Fim do Loop






////////////////////////Função botão


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




void controle_led_botaoSet(){
    int reading = buttonPinSet;
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

  
  void controle_led_botaoUp(){
    int reading = buttonPinUp;
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

  void controle_led_botaoDw(){
    int reading = buttonPinDw;
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
Serial.print("setmem: ");
Serial.print(setmem);
Serial.print(" temperaturapiscinaeeprom:");
Serial.println(temperaturapiscinaEEPROM);


    
   if (setmemfloat != temperaturapiscinaEEPROM){
      EEPROM.write(0, (setmemfloat ));
      memupdate = HIGH;  
      }
   if (setdiftempentrsaida != diftemperatudaentrsaidaEEPROM){
      EEPROM.write(1, setdiftempentrsaida);
      memupdate = HIGH;
      } 
  if (temperaturadeacionamentobombaEEPROM != settemperaturaacionbomba){
      EEPROM.write(2, settemperaturaacionbomba);
      memupdate = HIGH;
      }
  if (settemperdegelo != temperdegeloEEPROM){
      EEPROM.write(3, settemperdegelo + 100);
      memupdate = HIGH;  
      }    
  if (settempacionbomba != tempodeacionamentobombaEEPROM){
      EEPROM.write(4, settempacionbomba);
      memupdate = HIGH;
      }
  if (setbombadesl != bombadeslEEPROM){
      EEPROM.write(5, setbombadesl);
      memupdate = HIGH;
      }



    if (memupdate == HIGH){
      EEPROM.commit();
      memupdate = LOW;
      
      Serial.println("atualiza memoria");
            lcd.clear();
            lcd.setCursor(0, 1);
            lcd.print("Salvando na memoria");
            //lcd.setCursor(0, 1);
           //lcd.print("    memoria");
        delay(5000);
      
      
    temperaturapiscinaEEPROM = EEPROM.read(0);
    diftemperatudaentrsaidaEEPROM = EEPROM.read(1);
    temperaturadeacionamentobombaEEPROM = EEPROM.read(2);
    temperdegeloEEPROM = EEPROM.read(3)- 100;
    tempodeacionamentobombaEEPROM = EEPROM.read(4);
    bombadeslEEPROM = EEPROM.read(5);
    
  }
    }
