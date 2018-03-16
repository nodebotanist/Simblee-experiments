#include<SimbleeForMobile.h>

const int LED_PIN = 2;
int LED_state = LOW;

// Simblee UI elements
uint8_t button_ID;
uint8_t switch_ID;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_state);

  // Advertisement data -- max chars for both fields is 16
  SimbleeForMobile.advertisementData = "blink";
  SimbleeForMobile.deviceName = "WRL-13632";

  // BLE TX Strength between -20 (a few feet) and 20 inclusive
  SimbleeForMobile.txPowerLevel = -4;

  SimbleeForMobile.begin();
}

void loop() {
  SimbleeForMobile.process();
}

void ui() {
  // color_t is a special type which contains red, green, blue, and alpha 
  // (transparency) information packed into a 32-bit value. The functions rgb()
  // and rgba() can be used to create a packed value.
  color_t darkgray = rgb(85,85,85);

  // The beginScreen() function both sets the background color and serves as a
  // notification that the host should try to cache the UI functions which come
  // between this call and the subsequent endScreen() call.
  SimbleeForMobile.beginScreen(darkgray);

  button_ID = SimbleeForMobile.drawButton(
    (SimbleeForMobile.screenWidth/2) - 75, // x location
    (SimbleeForMobile.screenHeight/2) - 22, // y location
    150, // width of button
    "Reverse LED", // text shown on button
    WHITE,// color of button
    BOX_TYPE);// type of button

  SimbleeForMobile.setEvents(button_ID, EVENT_PRESS | EVENT_RELEASE);

  switch_ID = SimbleeForMobile.drawSwitch(
    (SimbleeForMobile.screenWidth/2) - 25, // x location
    (SimbleeForMobile.screenHeight/2)+22, // y location
    BLUE); // color (optional)

  SimbleeForMobile.endScreen();
}

void ui_event(event_t &event){
  if( event.id == button_ID ){
    if ( event.type == EVENT_PRESS ){
      if (LED_state == HIGH) digitalWrite(LED_PIN, LOW);
        else digitalWrite(LED_PIN, HIGH);
    }
    if (event.type == EVENT_RELEASE){
      if (LED_state == HIGH) digitalWrite(LED_PIN, HIGH);
      else digitalWrite(LED_PIN, LOW);
    }
  }

  if( event.id == switch_ID ){
    if (LED_state == HIGH) LED_state = LOW;
    else LED_state = HIGH;
    digitalWrite(LED_PIN, LED_state);
  }
}