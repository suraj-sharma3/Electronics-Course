int micPin = A1;
int soundValue = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  soundValue = analogRead(micPin);
  Serial.println(soundValue, DEC);
  delay(500);
}
