/*
  Author: Advait Thale
  *******************************************************************
  *                   Weather Monitor via ESP32                     *
  *******************************************************************
  Portable Weather Monitoring System returning Atmospheric Pressure, Humidity, 
  Air Quality Index (AQI) and dual sensor temperature data. It contains DHT11 
  Humidity & Temprature Sensor, MQ135 Air Quality Index (AQI) Sensor, BMP280 Pressure 
  Sensor and ESP32 as MCU. The data is visualized on web server which is runned by
  ESP32 itself on browser via WiFi. Type IP Address 192.168.1.1 on browser after 
  connecting to ESP32. 
  
*/
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#define DHTTYPE DHT11   // DHT 11

/*Put your SSID & Password*/
const char* ssid = "Cunt";          // Enter SSID here
const char* password = "password";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
WebServer server(80);

// DHT Sensor
uint8_t DHTPin = 4;

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);

float Temperature;
float Humidity;

void setup() {
  Serial.begin(115200);
  pinMode(DHTPin, INPUT);
  dht.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password); // Set it to NULL, if you don’t want to set a password.
  //  WiFi.softAP(const char* ssid, const char* password, int channel, int ssid_hidden, int max_connection)
  //  ssid: name for the access point – maximum of 63 characters;
  //  password: minimum of 8 characters; set to NULL if you want the access point to be open;
  //  channel: Wi - Fi channel number (1 - 13)
  //  ssid_hidden: (0 = broadcast SSID, 1 = hide SSID)
  //  max_connection: maximum simultaneous connected clients (1 - 4)
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
  Serial.print("Local IP Addr.: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  Temperature = dht.readTemperature(); // Gets the values of the temperature
  Humidity = dht.readHumidity(); // Gets the values of the humidity
  server.send(200, "text/html", SendHTML(Temperature, Humidity));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat, float Humiditystat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<meta content=\"Advait Thale\" name=\"author\"><meta content=\"20\" http-equiv=\"refresh\">\n";
  ptr += "<title>Weather Monitor</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>ESP32 Weather Report</h1>\n";
  ptr += "<p>Temperature: ";
  ptr += (int)Temperaturestat;
  ptr += "°C</p>";
  ptr += "<p>Humidity: ";
  ptr += (int)Humiditystat;
  ptr += "%</p>";
  ptr += "</div>\n";
  ptr += "<footer><p>Author: Advait Thale</P></footer>";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
