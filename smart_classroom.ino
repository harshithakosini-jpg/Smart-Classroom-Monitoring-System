#include <DHT.h>

// =====================================================
// PIN DEFINITIONS
// =====================================================

#define DHT_PIN       4
#define DHT_TYPE      DHT22

#define RELAY_PIN     26

#define LDR_PIN       34       // LDR AO

#define PIR_PIN       27       // PIR OUT
 
#define LIGHT_PIN     25       // MOSFET Gate

// =====================================================
// SETTINGS
// =====================================================

#define TEMP_LIMIT    35.0
#define LDR_LIMIT     1000

// =====================================================
// DHT22
// =====================================================

DHT dht(DHT_PIN, DHT_TYPE);

// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LIGHT_PIN, OUTPUT);

  // Initial OFF states
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LIGHT_PIN, LOW);

  Serial.println("======================================");
  Serial.println("ESP32 AUTOMATIC CONTROL SYSTEM");
  Serial.println("======================================");
}

// =====================================================
// LOOP
// =====================================================

void loop()
{
  // ===================================================
  // READ DHT22
  // ===================================================

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // ===================================================
  // READ LDR
  // ===================================================

  int ldrValue = analogRead(LDR_PIN);

  // ===================================================
  // READ PIR
  // ===================================================

  int motion = digitalRead(PIR_PIN);

  // ===================================================
  // TEMPERATURE + RELAY + DC MOTOR
  // ===================================================

  if (isnan(temperature))
  {
    Serial.println("DHT22 ERROR!");

    // Safety: turn relay OFF
    digitalWrite(RELAY_PIN, LOW);
  }
  else
  {
    if (temperature > TEMP_LIMIT)
    {
      digitalWrite(RELAY_PIN, HIGH);

      Serial.println("Temperature > 40 C");
      Serial.println("Relay: ON");
      Serial.println("DC Motor: ON");
    }
    else
    {
      digitalWrite(RELAY_PIN, LOW);

      Serial.println("Temperature <= 40 C");
      Serial.println("Relay: OFF");
      Serial.println("DC Motor: OFF");
    }
  }

  // ===================================================
  // LDR + PIR + USB LED
  // ===================================================

  if (ldrValue > LDR_LIMIT && motion == HIGH)
  {
    // LDR > 1000 AND MOTION DETECTED
    digitalWrite(LIGHT_PIN, HIGH);

    Serial.println("LDR > 1000");
    Serial.println("Motion: DETECTED");
    Serial.println("USB LIGHT: ON");
  }
  else
  {
    // Any other condition
    digitalWrite(LIGHT_PIN, LOW);

    Serial.println("USB LIGHT: OFF");

    if (ldrValue <= LDR_LIMIT)
    {
      Serial.println("LDR <= 1000");
    }

    if (motion == LOW)
    {
      Serial.println("Motion: NOT DETECTED");
    }
  }

  // ===================================================
  // SERIAL MONITOR
  // ===================================================

  Serial.println("--------------------------------------");

  if (!isnan(temperature))
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  Serial.print("Motion: ");

  if (motion == HIGH)
  {
    Serial.println("DETECTED");
  }
  else
  {
    Serial.println("NOT DETECTED");
  }

  Serial.println("--------------------------------------");

  delay(1000);
}  