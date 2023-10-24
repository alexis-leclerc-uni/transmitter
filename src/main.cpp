#include <Arduino.h>
#include <SPI.h>
#include <RH_ASK.h>

// put function declarations here:
RH_ASK driver;

void sendMsg(char *msg);

int buttonState = 0;
int lastButtonState = 0;
const int bouton = 2;

void setup()
{
    Serial.begin(9600);	  // Debugging only
    pinMode(bouton, INPUT_PULLUP);
    if (!driver.init())
         Serial.println("init failed");
}

void loop()
{
     buttonState = digitalRead(bouton);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
        sendMsg("yo bouton");
      // if the current state is HIGH then the button went from off to on:
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

}

void sendMsg(char *msg){
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("message sent");
}