# ESP8266 Vibration Alarm Troubleshooting Guide

## Quick Fix for Your Current Setup

### Immediate Steps to Try:

1. **Change the buzzer connection:**
   - Move buzzer from D4 to D1 (GPIO5)
   - Keep buzzer negative to GND

2. **Verify SW420 connections:**
   - Ensure SW420 VCC goes to ESP8266 3.3V (NOT 5V)
   - SW420 GND to ESP8266 GND
   - SW420 DO to ESP8266 D2

3. **Upload the provided code** (`esp8266_vibration_alarm.ino`)

## Testing Steps

### Step 1: Basic Component Test
1. Upload the code
2. Open Serial Monitor (115200 baud)
3. You should see startup messages
4. The built-in LED should be off initially

### Step 2: Test Each Component
Add this to your `setup()` function to test components:
```cpp
testComponents(); // Uncomment this line in setup()
```

### Step 3: Test Vibration Detection
1. Gently tap or shake the SW420 sensor
2. Watch Serial Monitor for "VIBRATION DETECTED!" message
3. Buzzer should activate with beeping pattern
4. Built-in LED should turn on during alarm

## Common Issues and Solutions

### Issue 1: Buzzer Not Working
**Symptoms:** No sound from buzzer
**Solutions:**
- Check if buzzer is active or passive
- For active buzzer: Use simple HIGH/LOW signals (current code)
- For passive buzzer: Use `playTone()` function in the code
- Add a transistor if buzzer needs more current

### Issue 2: SW420 Not Detecting
**Symptoms:** No vibration detection in Serial Monitor
**Solutions:**
- Check if SW420 has a sensitivity potentiometer - adjust it
- Verify 3.3V power supply (measure with multimeter)
- Try different GPIO pin (D5, D6, D7)
- SW420 might be faulty - test with multimeter

### Issue 3: ESP8266 Keeps Restarting
**Symptoms:** Continuous boot messages in Serial Monitor
**Solutions:**
- Remove all connections and test ESP8266 alone
- Add delays in code
- Use different GPIO pins (avoid D3, D4 during boot)
- Check power supply stability

### Issue 4: False Vibration Triggers
**Symptoms:** Alarm activates without vibration
**Solutions:**
- Increase `DEBOUNCE_TIME` in code
- Adjust SW420 sensitivity potentiometer
- Add pull-down resistor (10kΩ) on SW420 DO pin

## Wiring Verification Checklist

```
ESP8266 Pin  →  Component Pin
3.3V         →  SW420 VCC
GND          →  SW420 GND + Buzzer (-)
D2 (GPIO4)   →  SW420 DO
D1 (GPIO5)   →  Buzzer (+)
```

## Advanced Troubleshooting

### Use Multimeter to Check:
1. **Power Rails:**
   - 3.3V between ESP8266 3.3V and GND
   - Continuity on GND connections

2. **SW420 Output:**
   - Measure voltage on DO pin
   - Should be ~0V normally, ~3.3V when vibration detected

3. **Buzzer:**
   - Check if buzzer works with direct 3.3V connection
   - Measure resistance (should be 8-32 ohms typically)

### Code Debugging:
Add these debug lines to monitor pin states:
```cpp
Serial.print("Vibration Pin State: ");
Serial.println(digitalRead(VIBRATION_PIN));
Serial.print("Buzzer Pin State: ");
Serial.println(digitalRead(BUZZER_PIN));
```

## Alternative Connections (if current setup fails)

### Option 1: Use Different Pins
```
SW420 DO  → D5 (GPIO14)
Buzzer +  → D6 (GPIO12)
```

### Option 2: Add Transistor for Buzzer
```
ESP8266 D1 → 1kΩ resistor → Base of 2N2222
Collector → Buzzer (+)
Emitter → GND
Buzzer (-) → 3.3V or 5V
```

## Success Indicators
- Serial Monitor shows startup messages
- "VIBRATION DETECTED!" appears when sensor is tapped
- Buzzer makes sound in pattern (beep-beep-beep)
- Built-in LED turns on during alarm
- System returns to monitoring after 2 seconds

If none of these solutions work, the issue might be:
1. Faulty SW420 sensor
2. Faulty buzzer
3. Insufficient power supply
4. Damaged ESP8266 GPIO pins