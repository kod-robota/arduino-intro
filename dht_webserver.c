//подключение библиотек
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

// набор параметров для создания точки доступа 
const char *ssid = "Pauk15"; // имя сети
const char *password = "12345678"; // пароль от сети

// параметры для создания Web-сервера 
ESP8266WebServer server(80);

//обозначение сервоприводов
Servo servo_1;   //левая задняя
Servo servo_2;   // правая задняя
Servo servo_3;   // правая передняя
Servo servo_4;   //левая передняя

//состояние движения
bool LEFT=0;
bool FORW=1;
bool RIGHT=0;
bool STOP=0;

void setup() {

// подготовка пинов для сервоприводов
servo_1.attach(D8, 500, 2500);   //левая задняя
servo_2.attach(D7, 500, 2500);   // правая задняя
servo_3.attach(D6, 500, 2500);   // правая передняя
servo_4.attach(D5, 500, 2500);   //левая передняя
servo_1.write(90);   
servo_2.write(90);   
servo_3.write(90);   
servo_4.write(90);   
delay(1000);

// Подготовка сервера 
server.on("/", []() {
server.send(200, "text/html", webPage());
});


//что происходит при нажатии LEFT
server.on("/LEFT", [](){
  LEFT=1;
  FORW=0;
  RIGHT=0;
  STOP=0;
  server.send(200, "text/html", webPage());
  delay(100);   
});

//что происходит при нажатии FORWARD
server.on("/FORWARD", [](){
  LEFT=0;
  FORW=1;
  RIGHT=0;
  STOP=0;
  server.send(200, "text/html", webPage());
  delay(100);
});

//что происходит при нажатии RIGHT
server.on("/RIGHT", [](){
  LEFT=0;
  FORW=0;
  RIGHT=1;
  STOP=0;
  server.send(200, "text/html", webPage());
  delay(100);
});

//что происходит при нажатии STOP
server.on("/STOP", [](){
  LEFT=0;
  FORW=0;
  RIGHT=0;
  STOP=1;
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

if(LEFT==1){
  for (int i = 0; i<45; i+=5)
  {
  servo_1.write(135-i);
  servo_2.write(135-i);
  servo_3.write(135-i);
  servo_4.write(135-i);
    delay(3);
  }
  delay(200);
  
  servo_1.write(135);
  delay(200);
  
  servo_2.write(135);
  delay(200);
 
  servo_3.write(135);
  delay(200);
  
  servo_4.write(135);
  delay(200);
}
if(FORW==1){
  for (int i = 0; i<45; i+=5)
  {
  servo_1.write(135-i);//плавный переход ножки в положение 90°
  servo_2.write(45+i); //плавный переход ножки в положение 90°
  servo_3.write(45+i); //плавный переход ножки в положение 90°
  servo_4.write(135-i);//плавный переход ножки в положение 90°
  delay(3);
  }
  delay(200);
  
  servo_1.write(135);     
  delay(200);
  
  servo_2.write(45);   
  delay(200);
 
  servo_3.write(45);   
  delay(200);
  
  servo_4.write(135);   
  delay(200);
}
if(RIGHT==1){
  for (int i = 0; i<45; i+=5)
  {
  servo_1.write(45+i);
  servo_2.write(45+i);
  servo_3.write(45+i);
  servo_4.write(45+i);
    delay(3);
  }
  delay(200);
  
  servo_1.write(45);
  delay(200);
  
  servo_2.write(45);
  delay(200);
 
  servo_3.write(45);
  delay(200);
  
  servo_4.write(45);
  delay(200);
}
if(STOP==1){
  servo_1.write(90);
  delay(200);
  
  servo_2.write(90);
  delay(200);
 
  servo_3.write(90);
  delay(200);
  
  servo_4.write(90);
  delay(200);
}
}

// создание HTML страницы
String webPage()
{
String web;
// задаем размер вкладки
web += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"/> <meta charset=\"utf-8\"><title>Web Server</title><style>button{color:red;padding: 10px 27px;}</style></head>";

// выводим название страницы
web += "<h1 style=\"text-align: center;font-family: Open sans;font-weight: 100;font-size: 20px;\">Mr.Bebra</h1><div>";

// заголовок
web += "<p style=\"text-align: center;margin-top: 0px;margin-bottom: 5px;\">KOD_ROBOTA</p>";

// создание индикаторного блока
if (LEFT == 1)
{
web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #228B22;margin: 0 auto;\">LEFT</div>";
}
if (FORW == 1)
{
web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #FF8C00;margin: 0 auto;\">FORWARD</div>";
}
if (RIGHT == 1)
{
web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #228B22;margin: 0 auto;\">RIGHT</div>";
}
if (STOP == 1)
{
web += "<div style=\"text-align: center;width: 98px;color:white ;padding: 10px 30px;background-color: #4169E1;margin: 0 auto;\">STOP</div>";
}

// отображение кнопок
web += "<div style=\"text-align: center;margin: 5px 0px;\"> <a href=\"LEFT\"><button>LEFT</button></a>&nbsp;<a href=\"FORWARD\"><button>FORWARD</button></a>&nbsp;<a href=\"RIGHT\"><button>RIGHT</button></a>&nbsp;<a href=\"STOP\"><button>STOP</button></a></div>"; 

web += "</div>";
return (web);
}
