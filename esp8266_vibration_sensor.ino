/*
 * ESP8266 Vibration Sensor (SW420) with Buzzer
 * 
 * Wiring:
 * SW420 Sensor:
 * - VCC (E-1) → ESP8266 3.3V
 * - GND (E-2) → ESP8266 G
 * - DO (E-3) → ESP8266 D1 (GPIO5)
 * 
 * Buzzer:
 * - Positive (+) → ESP8266 D4 (GPIO2)
 * - Negative (-) → ESP8266 G (Ground)
 */

// Pin definitions
const int VIBRATION_SENSOR_PIN = D1;  // GPIO5
const int BUZZER_PIN = D2;            // GPIO4 (D4)

// Variables
bool vibrationDetected = false;
unsigned long lastVibrationTime = 0;
const unsigned long BUZZER_DURATION = 2000; // 2 seconds

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("ESP8266 Vibration Sensor with Buzzer");
  Serial.println("=====================================");
  
  // Configure pins
  pinMode(VIBRATION_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Turn off buzzer initially
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.println("System initialized. Waiting for vibration...");
  Serial.println("Pin Configuration:");
  Serial.println("- Vibration Sensor: D1 (GPIO5)");
  Serial.println("- Buzzer: D2 (GPIO4)");
  Serial.println();
}

void loop() {
  // Read vibration sensor
  int sensorValue = digitalRead(VIBRATION_SENSOR_PIN);
  
  // Check if vibration is detected (SW420 outputs HIGH when vibration detected)
  if (sensorValue == HIGH && !vibrationDetected) {
    vibrationDetected = true;
    lastVibrationTime = millis();
    
    Serial.println("VIBRATION DETECTED!");
    Serial.print("Time: ");
    Serial.println(millis());
    
    // Activate buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Buzzer ON");
  }
  
  // Turn off buzzer after specified duration
  if (vibrationDetected && (millis() - lastVibrationTime >= BUZZER_DURATION)) {
    digitalWrite(BUZZER_PIN, LOW);
    vibrationDetected = false;
    Serial.println("Buzzer OFF");
    Serial.println("Waiting for next vibration...");
    Serial.println();
  }
  
  // Small delay to prevent overwhelming the serial output
  delay(50);
}

// Function to test buzzer (call this from serial monitor)
void testBuzzer() {
  Serial.println("Testing buzzer...");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("Buzzer test complete");
}

// Function to test vibration sensor
void testSensor() {
  Serial.println("Testing vibration sensor...");
  Serial.print("Sensor reading: ");
  Serial.println(digitalRead(VIBRATION_SENSOR_PIN));
  Serial.println("Tap or shake the sensor to test");
}