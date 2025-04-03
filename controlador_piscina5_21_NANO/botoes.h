

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
         }
     }
  lastButtonStateDw = reading;
}