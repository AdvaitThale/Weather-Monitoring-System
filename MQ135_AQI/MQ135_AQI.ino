#define MQ_Anpin    A1      // MQ135 AnalogPin
#define MQ_Digpin   2       // DigitalPin
#define co2Zero     55      // Calibrating CO2 to 0 level

void setup()
{
  Serial.begin(115200);
  pinMode(MQ_Anpin, INPUT);      //Analog Input Feed
  pinMode(MQ_Digpin, INPUT);     //Digital Input Feed
}

void loop()
{
  //  int co2now[10];                          //Array for CO2 readings
  //  int co2raw = 0;                          //Raw value of CO2
  //  int co2comp = 0;                         //Compensated CO2
  //  int co2ppm = 0;                          //Calculated ppm
  //  int avrg = 0;                            //Averaging
  //
  //  for (int x = 0; x < 10; x++)
  //  {
  //    co2now[x] = analogRead(A1);            //Sampled CO2 Reading 10 times
  //  }
  //  for (int x = 0; x < 10; x++)
  //  {
  //    avrg = avrg + co2now[x];               //Added Samples Together
  //  }
  //
  //  co2raw = avrg / 10;                         //Dividing Samples by 10
  //  co2comp = co2raw - co2Zero;                 //Compensated value
  //  co2ppm = map(co2comp, 0, 1023, 400, 5000);  //Values Mapped according to Atmospheric levels
  //
  //  Serial.print(" CO2 Level: ");
  //  Serial.print(co2ppm);
  //  Serial.print(" PPM\n");

}
