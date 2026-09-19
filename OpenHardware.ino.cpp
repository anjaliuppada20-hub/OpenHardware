/*
 * OpenHardware
 * Open-source Environmental Monitoring System
 *
 * Hardware:
 *   - ESP32
 *   - DHT11 temperature/humidity sensor
 *   - LED
 *
 * DHT11:
 *   VCC  -> 3.3V
 *   DATA -> GPIO 4
 *   GND  -> GND
 *
 * LED:
 *   Anode  -> GPIO 2 through 220Ω resistor
 *   Cathode -> GND
 */

#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT11
#define LED_PIN 2

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  Serial.println();
  Serial.println("================================");
  Serial.println("       OpenHardware v1.0");
  Serial.println("================================");
  Serial.println("Environmental monitoring started.");
  Serial.println();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check sensor
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("ERROR: Unable to read DHT11 sensor.");

    digitalWrite(LED_PIN, LOW);

    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity:    ");
  Serial.print(humidity);
  Serial.println(" %");

  // High-temperature warning
  if (temperature >= 30.0) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("STATUS: HIGH TEMPERATURE");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("STATUS: NORMAL");
  }

  Serial.println("--------------------------------");

  delay(2000);
}
