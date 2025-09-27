/*
 * ESP8266 Vibration Alarm System
 * Components: SW420 Vibration Sensor + Buzzer
 * 
 * Connections:
 * SW420 VCC -> ESP8266 3.3V
 * SW420 GND -> ESP8266 GND
 * SW420 DO  -> ESP8266 D2 (GPIO4)
 * 
 * Buzzer +  -> ESP8266 D1 (GPIO5)
 * Buzzer -  -> ESP8266 GND
 */

// Pin definitions
const int VIBRATION_PIN = D2;  // GPIO4 - SW420 Digital Output
const int BUZZER_PIN = D1;     // GPIO5 - Buzzer control
const int LED_PIN = LED_BUILTIN; // Built-in LED for visual indication

// Variables
bool vibrationDetected = false;
unsigned long lastVibrationTime = 0;
const unsigned long ALARM_DURATION = 2000; // Alarm duration in milliseconds
const unsigned long DEBOUNCE_TIME = 100;   // Debounce time to avoid false triggers

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("ESP8266 Vibration Alarm System Starting...");
  
  // Configure pins
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initial state
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, HIGH); // LED off (inverted logic)
  
  Serial.println("System ready! Monitoring for vibrations...");
  Serial.println("Connections:");
  Serial.println("SW420 VCC -> 3.3V");
  Serial.println("SW420 GND -> GND");
  Serial.println("SW420 DO  -> D2");
  Serial.println("Buzzer +  -> D1");
  Serial.println("Buzzer -  -> GND");
  Serial.println("------------------------");
}

void loop() {
  // Read vibration sensor
  int vibrationState = digitalRead(VIBRATION_PIN);
  
  // Check for vibration detection (SW420 outputs HIGH when vibration detected)
  if (vibrationState == HIGH && !vibrationDetected) {
    // Debounce check
    if (millis() - lastVibrationTime > DEBOUNCE_TIME) {
      vibrationDetected = true;
      lastVibrationTime = millis();
      
      Serial.println("VIBRATION DETECTED! Activating alarm...");
      
      // Activate alarm
      activateAlarm();
    }
  }
  
  // Check if alarm should be turned off
  if (vibrationDetected && (millis() - lastVibrationTime > ALARM_DURATION)) {
    vibrationDetected = false;
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, HIGH); // LED off
    Serial.println("Alarm deactivated. Monitoring resumed...");
  }
  
  // Small delay to prevent excessive polling
  delay(50);
}

void activateAlarm() {
  // Visual indication
  digitalWrite(LED_PIN, LOW); // LED on (inverted logic)
  
  // Sound alarm with pattern
  for (int i = 0; i < 5; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
  
  // Keep buzzer on for remaining duration
  digitalWrite(BUZZER_PIN, HIGH);
}

// Function to test components individually
void testComponents() {
  Serial.println("Testing components...");
  
  // Test LED
  Serial.println("Testing LED...");
  digitalWrite(LED_PIN, LOW);
  delay(1000);
  digitalWrite(LED_PIN, HIGH);
  
  // Test Buzzer
  Serial.println("Testing Buzzer...");
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
  
  // Test Vibration Sensor
  Serial.println("Testing Vibration Sensor (tap the sensor)...");
  for (int i = 0; i < 50; i++) {
    if (digitalRead(VIBRATION_PIN) == HIGH) {
      Serial.println("Vibration sensor working!");
      break;
    }
    delay(100);
  }
  
  Serial.println("Component test complete.");
}

// Alternative buzzer function for passive buzzers
void playTone(int frequency, int duration) {
  // Calculate the period in microseconds
  int period = 1000000 / frequency;
  int halfPeriod = period / 2;
  
  // Calculate number of cycles
  long cycles = (long)frequency * duration / 1000;
  
  for (long i = 0; i < cycles; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(halfPeriod);
  }
}