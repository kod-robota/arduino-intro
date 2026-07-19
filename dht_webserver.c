//подключение библиотек
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define DHTPIN D4     // наш датчик подключен на этот контакт
#define DHTTYPE DHT11   // тип датчика DHT 11

DHT dht(DHTPIN, DHTTYPE); // инициализируем датчик


// набор параметров для создания точки доступа 
const char *ssid = "Pauk15"; // имя сети
const char *password = "12345678"; // пароль от сети

// параметры для создания Web-сервера 
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // Подготовка сервера 
  server.on("/", []() {
    server.send(200, "text/html", webPage());
  }
  );


//что происходит при нажатии LEFT
server.on("/dht", [](){
 
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

 if(TEMP==1){
 }

 if(TEMP==1){
 }
 
}
// создание HTML страницы
String webPage()
{
String web;
// задаем размер вкладки
web += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/> <meta charset=\"utf-8\"><title>Web Server</title><style>button{color:red;padding: 10px 27px;}</style></head>";

// выводим название страницы
web += "<h1 style=\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 20px;\">DHT Control</h1><div>";

// заголовок
web += "<p style=\"text-align: center;margin-top: 0px;margin-bottom: 5px;\">KOD_ROBOTA</p>";

// создание индикаторного блока
if (TEMP == 1)
{
web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #228B22;margin: 0 auto;\">TEMP</div>";
}
if (HUM == 1)
{
web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #FF8C00;margin: 0 auto;\">HUM</div>";
}

// отображение кнопок
web += "<div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"LEFT\"><button>TEMP</button></a>&nbsp;<a href=\"HUM\"><button>FORWARD</button></a>&nbsp;"; 

web += "</div>";
return (web);
}
