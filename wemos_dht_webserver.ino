//подключение библиотек
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHT.h"
#include <string.h>
#include <cstdio>

#define DHTPIN D4     // наш датчик подключен на этот контакт
#define DHTTYPE DHT11   // тип датчика DHT 11

DHT dht(DHTPIN, DHTTYPE); // инициализируем датчик


// набор параметров для создания точки доступа 
const char *ssid = "Pauk15"; // имя сети
const char *password = "12345678"; // пароль от сети

// параметры для создания Web-сервера 
ESP8266WebServer server(80);

// переменные для считывания и вывода температуры и влажности
float TEMP=0;
char str_temp[20];

float HUM=0;
char str_hum[20];



void setup() {
  // 
  // dtostrf(значение, мин. ширина, кол-во знаков после запятой, буфер)
  dtostrf(HUM, 6, 2, str_hum); 
  dtostrf(TEMP, 6, 2, str_temp);

  Serial.begin(9600);
  dht.begin();

  // Подготовка сервера 
  server.on("/", []() {
    Serial.println(webPage());
    
    server.send(200, "text/html", webPage());
  }
  );


//что происходит при нажатии DHT
server.on("/DHT", [](){
  Serial.println("DHT called");
  // считываение температуры в Цельсиях (по умолчанию)
  TEMP = dht.readTemperature();
  
  // завершение цикла, если не удалось прочитать одно из значений
  if (isnan(TEMP)) {
    Serial.println("Ошибка считывания из DHT датчика!");
    strcpy(str_temp, "ERROR"); 
    //return;
  }
  Serial.print("TEMP "); Serial.println(TEMP);
  // dtostrf(значение, мин. ширина, кол-во знаков после запятой, буфер) 
  dtostrf(TEMP, 6, 2, str_temp);
  
  // считывание влажности
  HUM = dht.readHumidity();

  // завершение цикла, если не удалось прочитать одно из значений
  if (isnan(HUM)) {
    Serial.println("Ошибка считывания из DHT датчика!");
    strcpy(str_hum, "ERROR"); 
    //return;
  }
  
  Serial.print("HUM "); Serial.println(HUM);
  dtostrf(HUM, 6, 2, str_hum); 
  //sprintf(str_hum, "%f", HUM);
  
  server.send(200, "text/html", webPage());
  delay(100);   
});

    // создание точки доступа
 WiFi.softAP(ssid, password); 
 IPAddress myIP = WiFi.softAPIP();
 server.begin();
}
// создание сервера


void loop() {
 server.handleClient();
}

// создание HTML страницы
String webPage()
{
String web;
// задаем размер вкладки
web += "<html>";
web += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/> <meta charset=\"utf-8\"><title>Web Server</title><style>button{color:red;padding: 10px 27px;}</style></head>";

// выводим название страницы
web += "<body>";
web += "<h1 style=\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 20px;\">DHT Control</h1><div>";

// заголовок
web += "<p style=\"text-align: center;margin-top: 0px;margin-bottom: 5px;\">KOD_ROBOTA</p>";

// создание индикаторного блока

web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #228B22;margin: 0 auto;\">TEMP ";
web += str_temp;
web += "</div>";

web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #FF8C00;margin: 0 auto;\">HUM ";
web += str_hum;
web += "</div>";

// отображение кнопок
web += "<div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"DHT\"><button>DHT</button></a>"; 

web += "</div>";
web += "</body>";
web += "</html>";
return (web);

}
