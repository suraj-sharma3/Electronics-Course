// use Node MCU 1.0 from boards manager for ESP8266
void setup() {
  pinMode(D4, OUTPUT);
}

void loop() {
  digitalWrite(D4, HIGH);
  delay(1000);
  digitalWrite(D4, LOW);
  delay(1000);
}

// The inbuilt LED on the NodeMCU board is connected to D4 pin
// There are 2 versions of NodeMCU boards : a smaller one (USB chip CP2102 - Driver install by itself) and a bigger one (USB chip - CH340 - driver install manual, The pin names font is bigger)
// Both the boards have the same ESP8266 chip
// The ESP8266 chip requires 3.3V to function, so the 3V mentioned on the board is actually 3.3V