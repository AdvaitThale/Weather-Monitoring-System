#include <Arduino.h>

#define STATUS_LED_BUILTIN 2
#define BLUE_LED_BUILTIN 26
#define GREEN_LED_BUILTIN 25
#define RED_LED_BUILTIN 33
#define BUZZ_BUILTIN 32
#define RELAY_A 19
#define RELAY_B 23
#define LM_ADC 13

int PLAY = 0, $blue_brightness = 0, $fade = 1, _amp, RAW_TEMP;
float LM;
void tone(byte PIN, int FREQ);
void noTone();
void init();
void tempAlert();

void setup()
{
  Serial.begin(115200);
  pinMode(BLUE_LED_BUILTIN, OUTPUT);
  pinMode(GREEN_LED_BUILTIN, OUTPUT);
  pinMode(RED_LED_BUILTIN, OUTPUT);
  pinMode(BUZZ_BUILTIN, OUTPUT);
  pinMode(RELAY_A, OUTPUT);
  pinMode(RELAY_B, OUTPUT);
  pinMode(STATUS_LED_BUILTIN, OUTPUT);
  pinMode(LM_ADC, INPUT);
  init();
  digitalWrite(STATUS_LED_BUILTIN, HIGH);
}

void loop()
{
  analogWrite(BLUE_LED_BUILTIN, $blue_brightness);
  $blue_brightness = $blue_brightness + $fade;
  if ($blue_brightness <= 0 || $blue_brightness >= 255) // reverse the direction of the fading at the ends of the fade
  {
    $fade = -$fade;
  }
  delay(30); // wait for the dimming effect

  //  tempAlert();
  // digitalWrite(BLUE_LED_BUILTIN, HIGH);
  // digitalWrite(RED_LED_BUILTIN, HIGH);
  // digitalWrite(GREEN_LED_BUILTIN, LOW);
  // delay(100);
  // digitalWrite(GREEN_LED_BUILTIN, HIGH);
  // digitalWrite(BLUE_LED_BUILTIN, HIGH);
  // digitalWrite(RED_LED_BUILTIN, LOW);
  // delay(100);

  // digitalWrite(GREEN_LED_BUILTIN, HIGH);
  // digitalWrite(RED_LED_BUILTIN, HIGH);
  // digitalWrite(BLUE_LED_BUILTIN, HIGH);
  // delay(100);
  // digitalWrite(RELAY_A, HIGH);
  // digitalWrite(RELAY_B, LOW);
  // delay(1000);
  // digitalWrite(RELAY_A, LOW);
  // digitalWrite(RELAY_B, HIGH);
  // delay(1000);
  // digitalWrite(RELAY_A, HIGH);
  // digitalWrite(RELAY_B, HIGH);
  // delay(1000);
  // digitalWrite(RELAY_A, LOW);
  // digitalWrite(RELAY_B, LOW);
}

void tempAlert()
{
  RAW_TEMP = analogRead(LM_ADC); // Read LM ADC
  LM = ((RAW_TEMP * 1.22) / 10);
  if (LM < 10)
  {
    digitalWrite(BLUE_LED_BUILTIN, HIGH);
    digitalWrite(GREEN_LED_BUILTIN, LOW);
    digitalWrite(RED_LED_BUILTIN, LOW);
  }
  else if (LM > 35)
  {
    digitalWrite(RED_LED_BUILTIN, HIGH);
    digitalWrite(GREEN_LED_BUILTIN, LOW);
    digitalWrite(BLUE_LED_BUILTIN, LOW);
    digitalWrite(BUZZ_BUILTIN, !digitalRead(BUZZ_BUILTIN));
    delay(85);
  }
  else
  {
    digitalWrite(GREEN_LED_BUILTIN, HIGH);
    digitalWrite(RED_LED_BUILTIN, LOW);
    digitalWrite(BLUE_LED_BUILTIN, LOW);
  } // LM >= 10 & LM <= 25
  digitalWrite(GREEN_LED_BUILTIN, LOW);
  digitalWrite(RED_LED_BUILTIN, LOW);
  digitalWrite(BLUE_LED_BUILTIN, LOW);
  Serial.print("TEMP: ");
  Serial.println(LM);
}

void init()
{
  Serial.println("Initializing CORE...");
  digitalWrite(RED_LED_BUILTIN, !digitalRead(RED_LED_BUILTIN));
  delay(85);
  digitalWrite(RED_LED_BUILTIN, !digitalRead(RED_LED_BUILTIN));
  delay(85);
  digitalWrite(RED_LED_BUILTIN, !digitalRead(RED_LED_BUILTIN));
  delay(85);
  digitalWrite(BUZZ_BUILTIN, !digitalRead(BUZZ_BUILTIN));
  delay(85);
  tone(BUZZ_BUILTIN, 2000); // 4093
  delay(200);
  noTone();
  digitalWrite(BUZZ_BUILTIN, !digitalRead(BUZZ_BUILTIN));
  delay(100);
  Serial.println("Hashing to Defaults...");
  digitalWrite(BLUE_LED_BUILTIN, !digitalRead(BLUE_LED_BUILTIN));
  digitalWrite(RED_LED_BUILTIN, LOW);
  digitalWrite(GREEN_LED_BUILTIN, LOW);
  delay(300);
  digitalWrite(GREEN_LED_BUILTIN, LOW);
  digitalWrite(RED_LED_BUILTIN, LOW);
  digitalWrite(BLUE_LED_BUILTIN, LOW);
  digitalWrite(GREEN_LED_BUILTIN, HIGH);
  digitalWrite(BLUE_LED_BUILTIN, LOW);
  digitalWrite(RED_LED_BUILTIN, LOW);
  delay(300);
  Serial.println("Dev. Module Configured.");
}

void tone(byte PIN, int FREQ)
{
  ledcSetup(0, 2000, 8);
  ledcAttachPin(PIN, 0);
  ledcWriteTone(0, FREQ);
  PLAY = PIN;
}

void noTone()
{
  tone(PLAY, 0);
}