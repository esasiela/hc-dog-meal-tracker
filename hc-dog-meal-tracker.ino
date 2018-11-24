
#include <HC_BouncyButton.h>

// LED1 -> output indicator for breakfast
// LED2 -> output indicator for dinner
// LED_BUTTON -> output indicator built into the pushbutton
// BUTTON1 -> push button input

#define PIN_LED1 0
#define PIN_LED2 1

#define PIN_BUTTON1 2
#define PIN_LED_BUTTON 3

// how long to live in state 1 (breakfast served) in millis (54000000 = 15 hours)
#define TTL_BREAKFAST 54000000

// how long to live in state 2 or 3 (dinner served, independent of whether breakfast was served) in millis (28,800,000 = 8 hours)
#define TTL_DINNER 28800000

BouncyButton btn=BouncyButton(PIN_BUTTON1);

#define MAX_MEAL_STATE 4

/* 
 * 0=reset, no meals
 * 1=breakfast, no dinner 
 * 2=dinner, no breakfast
 * 3=breakfast and dinner (happy pups)
 */
byte mealState;

static unsigned long ttlMillis;

void setup() {
  pinMode(PIN_LED1, OUTPUT);
  digitalWrite(PIN_LED1, LOW);
  
  pinMode(PIN_LED2, OUTPUT);
  digitalWrite(PIN_LED2, LOW);

  // on by default
  pinMode(PIN_LED_BUTTON, OUTPUT);
  digitalWrite(PIN_LED_BUTTON, HIGH);

  pinMode(PIN_BUTTON1, INPUT_PULLUP);

  btn.init();
}

void loop() {

  // trigger on press (not release)
  if (btn.update() && !btn.getState()) {
    mealState++;
    if (mealState>=MAX_MEAL_STATE) {
      mealState=0;

      digitalWrite(PIN_LED1, LOW);
      digitalWrite(PIN_LED2, LOW);
        
    } else if (mealState==1) {
      digitalWrite(PIN_LED1, HIGH);
      digitalWrite(PIN_LED2, LOW);
      ttlMillis = millis() + TTL_BREAKFAST;
        
    } else if (mealState==2) {
      digitalWrite(PIN_LED1, LOW);
      digitalWrite(PIN_LED2, HIGH);
      ttlMillis = millis() + TTL_DINNER;
      
    } else if (mealState==3) {
      digitalWrite(PIN_LED1, HIGH);
      digitalWrite(PIN_LED2, HIGH);
      ttlMillis = millis() + TTL_DINNER;
      
    } else {
      // should never reach this, loop forever in hell
      digitalWrite(PIN_LED1, LOW);
      digitalWrite(PIN_LED2, HIGH);

      while (true) {
        digitalWrite(PIN_LED1, !digitalRead(PIN_LED1));
        digitalWrite(PIN_LED2, !digitalRead(PIN_LED2));
        delay(1000);
      }
    }
  }

  // did the timer reach the reset duration?
  if (mealState>0 && (long)(millis()-ttlMillis)>=0) {
    // we've been in a non-reset state too long, reset the state
    mealState=0;
    digitalWrite(PIN_LED1, LOW);
    digitalWrite(PIN_LED2, LOW);
  }
}
