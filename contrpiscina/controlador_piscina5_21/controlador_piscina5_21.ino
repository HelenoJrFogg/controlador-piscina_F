



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

LiquidCrystal_I2C lcd(0x3F,16,2);



//Array simbolo grau
byte grau[8] ={ B00001100,
                B00010010,
                B00010010,
                B00001100,
                B00000000,
                B00000000,
                B00000000,
                B00000000,};





int s1;

bool memupdate = 0 ;
int setmem;
float setmemfloat;
int temperaturapiscinaEEPROM;

int settemperaturaacionbomba;
float settemperaturaacionbomba1;
float temperaturadeacionamentobombaEEPROM;

int setdiftempentrsaida;
float setdiftempentrsaida1;
float diftemperatudaentrsaidaEEPROM;

int settempacionbomba;
float settempacionbomba1;
float tempodeacionamentobombaEEPROM;

int setbombadesl;
float setbombadesl1;
float bombadeslEEPROM;

int settemperdegelo;
float settemperdegelo1;
float temperdegeloEEPROM;



float tempreal;
float tempreal1;
int bomba = 16;// pino acionamento da bomba



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
float tempersaidaaquecedor;
float temperaturaplaca;

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
  temperaturadeacionamentobombaEEPROM = EEPROM.read(1);
  diftemperatudaentrsaidaEEPROM = EEPROM.read(2); 
  tempodeacionamentobombaEEPROM = EEPROM.read(3);
  bombadeslEEPROM = EEPROM.read(4);
  temperdegeloEEPROM = EEPROM.read(5);
  
  setmemfloat = temperaturapiscinaEEPROM;
  settemperaturaacionbomba1 = temperaturadeacionamentobombaEEPROM;
  settempacionbomba1 = tempodeacionamentobombaEEPROM;
  setdiftempentrsaida1 = diftemperatudaentrsaidaEEPROM;
  setbombadesl1 = bombadeslEEPROM;
  settemperdegelo1 = temperdegeloEEPROM;
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

// if ((millis() - lastDebounceTimeMenu) >3000) {// menuDebounceDelay
    
//       if (buttonState != menuState) {
    //  menuState = buttonState ;
//Serial.println(menuState);
         // }
//  }
//digitalWrite(ledPin, menuState);
//lastMenuState = buttonState;

//chamadamenu = menuState;
  

 basetempo10seg = millis() / 10000;
 basetempo30seg = basetempo10seg / 3;

  unsigned long start = millis();
    //int botoes;
  int tempomenu;
 
  setmem = temperaturapiscinaEEPROM;
  settemperaturaacionbomba = temperaturadeacionamentobombaEEPROM;
  setdiftempentrsaida = diftemperatudaentrsaidaEEPROM;
  settempacionbomba = tempodeacionamentobombaEEPROM;
  setbombadesl = bombadeslEEPROM;
  settemperdegelo = temperdegeloEEPROM;
  
  
  /*
  
  if (botaoset == HIGH || botaoup == HIGH || botaodw == HIGH){
         botoes = HIGH;
        // Serial.print("  botoes HIGH HIGH ");
         tp1 = millis();
                  }
        else{
         
         botoes = LOW;
         //Serial.print("  botoes LOWLOW ");

         }
         
   if (millis() - tp1 < 10000)    {
      tempomenu =HIGH ;
     // Serial.print("  tempomenu high ");
      }
     else{
      tempomenu = LOW;
      //Serial.print("  tempomenu low ");
          
  }
    
  if (tempomenu == HIGH || botoes == HIGH){
     chamadamenu = HIGH;
     //Serial.print("  chamadamenu high ");
     }
  else{
    //Serial.print("  chamadamenu low ");
       chamadamenu = LOW;
      }
  
  //Serial.println(chamadamenu);
*/



  
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
        if (buttonStateUp == HIGH & setmemfloat < 90){
            setmemfloat = setmemfloat + 1;
            }
             
        if (buttonStateDw == HIGH & setmemfloat > 0){
            setmemfloat = setmemfloat - 1;
            }
            
        lcd.setCursor(0, 0);
        lcd.print("1TempMaxPiscina");
        lcd.setCursor(3, 1);
        lcd.print(setmemfloat/2);
          lcd.setCursor(9, 1);
          lcd.write((byte)0);
       break; 
       
        
   case 2:
        if (buttonStateUp == HIGH & settemperaturaacionbomba1 <= 100){
            settemperaturaacionbomba1 = settemperaturaacionbomba1 + 1;
            }
        if (buttonStateDw == HIGH & settemperaturaacionbomba1 > 0){
            settemperaturaacionbomba1 = settemperaturaacionbomba1 - 1;
            }
        lcd.setCursor(0, 0);
        lcd.print("2TemperAcionBomba");
        lcd.setCursor(3, 1);
        lcd.print(settemperaturaacionbomba1 /2 );

            lcd.setCursor(9, 1);
            lcd.write((byte)0);

       break;

  case 3:
        if (buttonStateUp == HIGH & setdiftempentrsaida1 <= 99){
          setdiftempentrsaida1 = setdiftempentrsaida1 + 1;
          }
        
        if (buttonStateDw == HIGH & setdiftempentrsaida1 > 0){
            setdiftempentrsaida1 = setdiftempentrsaida1 - 1;
            }
            lcd.setCursor(0, 0);
            lcd.print("3difTemperEntrSaida");
            lcd.setCursor(3, 1);
            lcd.print(setdiftempentrsaida1/10);
            lcd.setCursor(8, 1);
            lcd.write((byte)0);
                      
          break;

        
    case 4:
        if (buttonStateUp == HIGH & settempacionbomba1 <= 80){
            settempacionbomba1 = settempacionbomba1 + 1;
            }
        if (buttonStateDw == HIGH & settempacionbomba1 > 0){
           settempacionbomba1 = settempacionbomba1 - 1;
           }
           lcd.setCursor(0, 0);
           lcd.print("4tempoAcionBomba");
           // lcd.print(settempacionbomba1);
           total = settempacionbomba1 * 10;
           horas = (total / 3600);
           minutos = ((total - (horas * 3600)) / 60);
           segundos = (total % 60);

              // lcd.setCursor(0, 1);
              // lcd.print(total);

           lcd.setCursor(2, 1);
        if (horas < 10){
          lcd.print("0");
           }
           lcd.print(horas);
           lcd.print(":");
           lcd.setCursor(5, 1);
        if (minutos < 10){
           lcd.print("0");
           }
           lcd.print(minutos);
           lcd.print(":");
           lcd.setCursor(8, 1);
        if (segundos < 10){
            lcd.print("0");
            }
            lcd.print(segundos);
          break;
          
    
     case 5:       
        if (buttonStateUp == HIGH & setbombadesl1 <= 239){
            setbombadesl1 = setbombadesl1 + 1;
            }
        if (buttonStateDw == HIGH & setbombadesl1 > 0){
           setbombadesl1 = setbombadesl1 - 1;
           }
           lcd.setCursor(0, 0);
           lcd.print("5tempoIntervBombaDesl");
           // lcd.print(settempacionbomba1);
           total = setbombadesl1 * 30;
           horas = (total / 3600);
           minutos = ((total - (horas * 3600)) / 60);
           segundos = (total % 60);
           lcd.setCursor(2, 1);
        if (horas < 10){
          lcd.print("0");
           }
           lcd.print(horas);
           lcd.print(":");
           lcd.setCursor(5, 1);
        if (minutos < 10){
           lcd.print("0");
           }
           lcd.print(minutos);
           lcd.print(":");
           lcd.setCursor(8, 1);
        if (segundos < 10){
            lcd.print("0");
            }
            lcd.print(segundos);
          break;

        
   case 6:
        if (buttonStateUp == HIGH & settemperdegelo1 < 60){
          settemperdegelo1 = settemperdegelo1 + 1;
          }
        
        if (buttonStateDw == HIGH & settemperdegelo1 > 0){
            settemperdegelo1 = settemperdegelo1 - 1;
            }
            lcd.setCursor(0, 0);
            lcd.print("6TemperInicDegelo");
            lcd.setCursor(5, 1);
            lcd.print(settemperdegelo1/10);
            lcd.setCursor(10, 1);
            lcd.write((byte)0);
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
  
  
  
  setmem = setmemfloat;
  settemperaturaacionbomba = settemperaturaacionbomba1;
  settempacionbomba = settempacionbomba1;
  setdiftempentrsaida = setdiftempentrsaida1;
  setbombadesl = setbombadesl1;
  settemperdegelo = settemperdegelo1;

  




      
 // Serial.print("eepromread  ");
  //Serial.println(EEPROM.read(0));
  //Serial.print("tempEEPROM  ");
 // Serial.println(temperaturapiscinaEEPROM);




   //sensors.requestTemperatures();
  // A temperatura em Celsius para o dispositivo 1 no índice 0 (é possivel ligar varios sensores usando a mesma porta do arduino)
  //float leitura0 = sensors.getTempCByIndex(0);
  //float leitura1 = sensors.getTempCByIndex(1);
  // Imprime na serial a varivel que recebe os dados do Sensor


  temperaturapiscina = 10 * sensor_piscina.getTempCByIndex(0);
  tempersaidaaquecedor = sensor_painel.getTempCByIndex(0);
  temperaturaplaca = sensor_retorno.getTempCByIndex(0);
  
  Serial.print("  tempPisc: ");
  Serial.print(temperaturapiscina);
  Serial.print("< >");
  //Serial.print("  tempPisc: ");
  Serial.print(EEPROM.read(0));
  Serial.print(" <<< ");
  
  
//  Serial.println(leitura0);
    lcd.setCursor(0, 0);
    lcd.print("Pi:");
    lcd.print(sensor_piscina.getTempCByIndex(0),1);
    lcd.setCursor(9, 0);
    lcd.print("Aq:");
    lcd.print(tempersaidaaquecedor, 2);
     lcd.setCursor(0, 1);
    lcd.print("Pa:");
    lcd.print(temperaturaplaca,2);
    // lcd.setCursor(10, 0);
   // lcd.print("BT10:");
   // lcd.print(basetempo10seg);
   //  lcd.setCursor(10, 1);
   // lcd.print("BT30:");
   // lcd.print(basetempo30seg); 

    



  // Serial.print(sensors.getResolution(s1), DEC);
 // lcd.setCursor(9, 3);
   // lcd.print(temperaturapiscinaEEPROM);
 // lcd.print(" ");
 // lcd.print(tempreal1);
unsigned long stop = millis();

 //Serial.print("Time used: ");
 // Serial.println(stop - start);
  //Serial.print("\n\n\n");

  


  

 if ((temperaturapiscina * 2 > temperaturapiscinaEEPROM) || (temperaturaplaca * 10 < temperdegeloEEPROM ) ) 
     {
       circulacaodeprotecao = HIGH;
       
        if (  (temperaturaplaca * 2 >= temperaturadeacionamentobombaEEPROM + 40) || (temperaturaplaca * 10 < temperdegeloEEPROM )  )
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
      
      










if (temperaturaplaca * 2 >= temperaturadeacionamentobombaEEPROM & circulacaodeprotecao == LOW ){
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
     
     //Serial.print("  circulacaodeprotecao: ");
     //Serial.println(circulacaodeprotecao); 
























    
 /*    
  
if(circulacaodeprotecao == HIGH  ){





 int tempaciprot;

   tempaciprot = tempobombaacioncircprot + settempacionbomba;

      if ( basetempo10seg < tempaciprot){
         digitalWrite(bomba, HIGH);
         tempointervdeprot = basetempo30seg;

         Serial.println(" bomaLigProt:");
     Serial.print(tempobombaacioncircprot + tempodeacionamentobombaEEPROM);
     

     Serial.print(tempobombaacioncircprot + tempodeacionamentobombaEEPROM);
     
     Serial.print(tempobombaacioncircprot + tempodeacionamentobombaEEPROM);

         }
         else {

          


          int tempinteprot;
          tempinteprot = tempointervdeprot + setbombadesl;

               if(  basetempo30seg < tempinteprot) {
                
                digitalWrite(bomba, LOW);
                
                  tempobombaacioncircprot = basetempo10seg;

                Serial.print(" BombaDeslProt:");
                Serial.print(tempointervdeprot);


               }

          }




      Serial.print("                                                   bombacionada:");
     Serial.print(bombacionada);

Serial.print(" TAcionBomba:");
     Serial.print(TAcionBomba);

      Serial.print(" tbomba:");
     Serial.print(tbomba);
     Serial.print(" disparoaquecerpiscina:");
     Serial.print(disparoaquecerpiscina);
     Serial.print(" basetempo10seg:");
     Serial.print(basetempo10seg);
     Serial.print(" difentrsaida:");
     Serial.print(difentrsaida);


     Serial.print("   TAC:");
     Serial.print(tempodeacionamentobombaEEPROM);
     Serial.print("  temperaturaplaca:");
     Serial.print(temperaturaplaca);
     Serial.print("  temperaturapiscinax10:");
     Serial.print(temperaturapiscina * 10);
     Serial.print("  tempersaidaaquecedor:");
     Serial.println(tempersaidaaquecedor * 10);
     









Serial.print(" tempobombaacioncircprot + tempodeacionamentobombaEEPROM:");
Serial.println(tempobombaacioncircprot + tempodeacionamentobombaEEPROM);
Serial.print(" tempodeacionamentobombaEEPROM:");
Serial.println(tempodeacionamentobombaEEPROM);
Serial.print(" tempobombaacioncircprot:");
Serial.println(tempobombaacioncircprot);
Serial.print(" basetempo10seg:");
Serial.println(basetempo10seg);
Serial.print(" basetempo30seg:");
Serial.println(basetempo30seg);


*/





    // lcd.setCursor(8, 1);
     //lcd.blink();


lcd.setCursor(9, 1);
    lcd.print("Dif:");
    lcd.print(temperaturaplaca - temperaturapiscina ,1);






  
}












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




  void  atualizaeeprom (){
//    Serial.print();
Serial.print("setmem: ");
Serial.print(setmem);
Serial.print(" temperaturapiscinaeeprom:");
Serial.println(temperaturapiscinaEEPROM);


    
      if (setmem != temperaturapiscinaEEPROM){
      EEPROM.write(0, setmem);
     // 
      memupdate = HIGH;  
      }
      
  if (settemperaturaacionbomba != temperaturadeacionamentobombaEEPROM){
      EEPROM.write(1, settemperaturaacionbomba);
      //
      memupdate = HIGH;
      }
      
  if (setdiftempentrsaida != diftemperatudaentrsaidaEEPROM){
   //   EEPROM.update(2, setdiftempentrsaida);
      
      } 
  
  if (settempacionbomba != tempodeacionamentobombaEEPROM){
     // EEPROM.update(3, settempacionbomba);
      
      }

  if (setbombadesl != bombadeslEEPROM){
     // EEPROM.white(4, setbombadesl);
      
      }

  if (settemperdegelo != temperdegeloEEPROM){
//      EEPROM.update(5, settemperdegelo);
      
      }

    if (memupdate == HIGH){
      EEPROM.commit();
      memupdate = LOW;
      Serial.println("atualiza memoria");
            lcd.setCursor(0, 0);
        lcd.print("   Salvando na memoria");
                    lcd.setCursor(0, 1);
        lcd.print("    memoria");
        delay(5000);
      
      }
    temperaturadeacionamentobombaEEPROM = EEPROM.read(1);
    diftemperatudaentrsaidaEEPROM = EEPROM.read(2);
    tempodeacionamentobombaEEPROM = EEPROM.read(3);
    bombadeslEEPROM = EEPROM.read(4);
    temperdegeloEEPROM = EEPROM.read(5);
    }
