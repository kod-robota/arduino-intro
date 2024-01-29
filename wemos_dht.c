#include "DHT.h"

#define DHTPIN D4     // наш датчик подключен на этот контакт
#define DHTTYPE DHT11   // тип датчика DHT 11

DHT dht(DHTPIN, DHTTYPE); // инициализируем датчик

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
   // считывание влажности
  float h = dht.readHumidity();
  // считываение температуры в Цельсиях (по умолчанию)
  float t = dht.readTemperature();
  // считывание температуры в Фаренгейтах, (isFahrenheit = true)
  //float f = dht.readTemperature(true); 

  // завершение цикла, если не удалось прочитать одно из значений
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
  
  delay(500);
}
