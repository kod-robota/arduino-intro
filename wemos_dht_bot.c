// See https://kit.alexgyver.ru/tutorials/fastbot/

#include "DHT.h"

#define DHTPIN D4     // наш датчик подключен на этот контакт
#define DHTTYPE DHT11   // тип датчика DHT 11

DHT dht(DHTPIN, DHTTYPE); // инициализируем датчик

float h, t; //глобальные переменные для влажности и температуры

#define WIFI_SSID "Название вашей сети Wi-Fi"
#define WIFI_PASS "Пароль сети WiFi"
#define BOT_TOKEN "Вставьте токен сюда из BotFather"

#include <FastBot.h>
FastBot bot(BOT_TOKEN);

void setup() {

  Serial.begin(115200);
  
  connectWiFi();
  bot.attach(newMsg);

  dht.begin(); 

  get_ht(h, t);

  if (isnan(h) || isnan(t)) {
    Serial.println("Ошибка считывания из DHT датчика!");
    return;
  }

  Serial.print("Влажность: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Tемпература: ");
  Serial.print(t);
  Serial.println(" *C ");
}

// обработчик сообщений, которые телеграмм нам присылает 
// (все что пользователь написал в бот)
void newMsg(FB_msg& msg) {
  if (msg.text == "/start") bot.sendMessage("Hello from Kod Robota!", msg.chatID);
  else if (msg.text == "/dht") {
    float h, t;
    get_ht(h, t);
    char s[48];
    snprintf(s, sizeof(s), "Temperature %i *C\nHumidity %i%%", (int)t, (int)h);
    Serial.println(s);
    bot.sendMessage(s, msg.chatID);
  }
  //else if (msg.text == "/led_on") digitalWrite(LED_BUILTIN, LOW);
  //else if (msg.text == "/led_off") digitalWrite(LED_BUILTIN, HIGH);
}

void connectWiFi() {
  delay(2000);
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial.println("Connected");
}

void get_ht(float& h, float& t)
{
  // считывание влажности
  h = dht.readHumidity();
  // считываение температуры в Цельсиях (по умолчанию)
  t = dht.readTemperature();
  // считывание температуры в Фаренгейтах, (isFahrenheit = true)
  //float f = dht.readTemperature(true); 
}

void loop() {

  delay(500);
  
  bot.tick();
}
