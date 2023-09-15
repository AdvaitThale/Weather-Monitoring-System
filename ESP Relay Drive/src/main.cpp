#include <Arduino.h>

#define STATUS_LED_BUILTIN 2
#define BLUE_LED_BUILTIN 26
#define GREEN_LED_BUILTIN 25
#define RED_LED_BUILTIN 33
#define BUZZ_BUILTIN 32
#define RELAY_A 19
#define RELAY_B 23
#define LM_ADC 13

int _play = 0, $blue_brightness, $green_brightness, $red_brightness = 0, $fade = 2, _amp, $raw_temp;
float _lm;
void tone(byte _pin, int _freq);
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
  digitalWrite(RED_LED_BUILTIN, LOW);
  digitalWrite(GREEN_LED_BUILTIN, LOW);
  analogWrite(BLUE_LED_BUILTIN, $blue_brightness);
  $blue_brightness = $blue_brightness + $fade;
  if ($blue_brightness <= 0 || $blue_brightness >= 255) // reverse the direction of the fading at the ends of the fade
  {
    $fade = -$fade;
  }
  Serial.println($blue_brightness);
  delay(12); // wait for the dimming effect

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
  $raw_temp = analogRead(LM_ADC); // Read LM ADC
  _lm = (($raw_temp * 1.22) / 10);
  if (_lm < 10)
  {
    digitalWrite(BLUE_LED_BUILTIN, HIGH);
    digitalWrite(GREEN_LED_BUILTIN, LOW);
    digitalWrite(RED_LED_BUILTIN, LOW);
  }
  else if (_lm > 35)
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
  Serial.println(_lm);
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

void tone(byte _pin, int _freq)
{
  ledcSetup(0, 2000, 8);
  ledcAttachPin(_pin, 0);
  ledcWriteTone(0, _freq);
  _play = _pin;
}

void noTone()
{
  tone(_play, 0);
}