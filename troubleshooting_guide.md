# ESP8266 Vibration Sensor Troubleshooting Guide

## Common Issues and Solutions

### 1. **Buzzer Not Working**
**Problem**: Buzzer doesn't make sound
**Solutions:**
1. **Check buzzer type**: Make sure you're using an ACTIVE buzzer (not passive)
   - Active buzzer: Makes sound with just power
   - Passive buzzer: Needs PWM signal to make sound
2. **Verify wiring**: 
   - Positive (+) → D2 (GPIO4)
   - Negative (-) → Ground
3. **Test buzzer directly**: Connect buzzer directly to 3.3V and Ground

### 2. **Vibration Sensor Not Detecting**
**Problem**: SW420 not responding to vibration
**Solutions:**
1. **Check power supply**: Ensure 3.3V is reaching the sensor
2. **Verify sensitivity**: SW420 has adjustable sensitivity (potentiometer)
3. **Test sensor output**: Use multimeter to check DO pin voltage
4. **Check connections**: Ensure all three pins are properly connected

### 3. **Code Not Uploading**
**Problem**: Arduino IDE can't upload to ESP8266
**Solutions:**
1. **Install ESP8266 board package**:
   - File → Preferences → Additional Board Manager URLs
   - Add: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Tools → Board → Board Manager → Search "ESP8266" → Install
2. **Select correct board**: Tools → Board → ESP8266 Boards → NodeMCU 1.0
3. **Check COM port**: Tools → Port → Select correct COM port
4. **Hold BOOT button** while uploading if needed

### 4. **Serial Monitor Issues**
**Problem**: No output in Serial Monitor
**Solutions:**
1. **Set correct baud rate**: 115200
2. **Check COM port**: Same as upload port
3. **Add delay in setup()**: Some ESP8266 boards need time to initialize

## Step-by-Step Testing

### Test 1: Buzzer Test
```cpp
void testBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}
```

### Test 2: Sensor Test
```cpp
void testSensor() {
  Serial.print("Sensor value: ");
  Serial.println(digitalRead(VIBRATION_SENSOR_PIN));
}
```

### Test 3: Power Test
- Measure voltage at ESP8266 3.3V pin
- Should read approximately 3.3V
- Check ground continuity

## Hardware Verification

### Required Components:
- ESP8266 (NodeMCU or Wemos D1 Mini)
- SW420 Vibration Sensor
- Active Buzzer (5V or 3.3V)
- Breadboard and jumper wires
- Multimeter (for testing)

### Pin Verification:
```
ESP8266 → Component
3.3V    → SW420 VCC (E-1)
G       → SW420 GND (E-2) + Buzzer (-)
D1      → SW420 DO (E-3)
D2      → Buzzer (+)
```

## Debugging Steps

1. **Upload the code** and open Serial Monitor (115200 baud)
2. **Check initialization message** - should see "System initialized"
3. **Test buzzer manually** - call testBuzzer() function
4. **Test sensor** - tap the SW420 and watch serial output
5. **Verify pin assignments** - check if D1 and D2 are correct for your board

## Alternative Wiring (if D1/D2 don't work)

Try these pins instead:
- Sensor: D5 (GPIO14) or D6 (GPIO12)
- Buzzer: D3 (GPIO0) or D7 (GPIO13)

Update the pin definitions in the code accordingly.