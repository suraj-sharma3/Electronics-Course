const int GSR_PIN = 32; // GPIO pin for the GSR sensor

// Adjusted thresholds based on observed values
const int HAPPY_THRESHOLD = 1900; // Below this value indicates a happy state
const int Stressed_THRESHOLD = 1950; // Above this value indicates a sad state

void setup() {
  Serial.begin(115200);
  pinMode(GSR_PIN, INPUT);
}

void loop() {
  int sensorValue = analogRead(GSR_PIN); // Read the GSR sensor value
  String state = categorizeGSR(sensorValue); // Get the emotional state
  Serial.print("GSR Value: ");
  Serial.print(sensorValue);
  Serial.print(" - State: ");
  Serial.println(state);

  delay(100); // Small delay to avoid flooding the serial monitor
}

// Function to categorize GSR values into different emotional states
String categorizeGSR(int value) {
  if (value < HAPPY_THRESHOLD) {
    return "Happy";
  } else if (value > Stressed_THRESHOLD) {
    return "Stressed";
  } else {
    return "Relaxed";
  }
}
