
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// MAX30100
#define REPORTING_PERIOD_MS 100
PulseOximeter pox;
uint32_t tsLastReport = 0;

void onBeatDetected()
{
  Serial.println("Beat detected!");
}

// OLED
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// MPU6050
Adafruit_MPU6050 mpu;

unsigned long previousMillis = 0;
const long interval = 5000; // 5 seconds
bool displayMax30100 = true;

// Structure to hold sensor data
struct SensorData {
  float heartRate;
  float spO2;
  float accX;
  float accY;
  float accZ;
  float gyroX;
  float gyroY;
  float gyroZ;
  float temperature;
  int gsrValue;
  String gsrState;
};

SensorData sensorData;

// GSR sensor
const int GSR_PIN = 32; // GPIO pin for the GSR sensor

// Adjusted thresholds based on observed values
const int HAPPY_THRESHOLD = 1900; // Below this value indicates a happy state
const int Stressed_THRESHOLD = 1950; // Above this value indicates a stressed state

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("OLED initialization failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  // MPU6050
  Serial.println("Initializing MPU6050...");
  if (!mpu.begin(0x68)) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  // MAX30100
  Serial.println("Initializing MAX30100...");
  if (!pox.begin()) {
    Serial.println("MAX30100 Initialization FAILED");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MAX30100 Initialization SUCCESS");
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);

  // GSR sensor
  pinMode(GSR_PIN, INPUT);
}

void updateSensors() {
  // Update MAX30100
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    sensorData.heartRate = pox.getHeartRate();
    sensorData.spO2 = pox.getSpO2();

    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    sensorData.accX = a.acceleration.x;
    sensorData.accY = a.acceleration.y;
    sensorData.accZ = a.acceleration.z;
    sensorData.gyroX = g.gyro.x;
    sensorData.gyroY = g.gyro.y;
    sensorData.gyroZ = g.gyro.z;
    sensorData.temperature = temp.temperature;

    tsLastReport = millis();
  }

  // Update GSR sensor
  sensorData.gsrValue = analogRead(GSR_PIN);
  sensorData.gsrState = categorizeGSR(sensorData.gsrValue);
}

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);

  if (displayMax30100) {
    display.println("MAX30100:");
    display.print("Heart rate: ");
    display.print(sensorData.heartRate);
    display.println(" bpm");
    display.print("SpO2: ");
    display.print(sensorData.spO2);
    display.println(" %");
  } else {
    display.println("MPU6050:");
    display.print("Acc X: ");
    display.print(sensorData.accX);
    display.println(" m/s^2");
    display.print("Acc Y: ");
    display.print(sensorData.accY);
    display.println(" m/s^2");
    display.print("Acc Z: ");
    display.print(sensorData.accZ);
    display.println(" m/s^2");
    display.print("Gyro X: ");
    display.print(sensorData.gyroX);
    display.println(" rad/s");
    display.print("Gyro Y: ");
    display.print(sensorData.gyroY);
    display.println(" rad/s");
    display.print("Gyro Z: ");
    display.print(sensorData.gyroZ);
    display.println(" rad/s");
    display.print("Temp: ");
    display.print(sensorData.temperature);
    display.println(" C");
  }

  // Display GSR sensor data
  display.println();
  display.println("GSR:");
  display.print("Value: ");
  display.println(sensorData.gsrValue);
  display.print("State: ");
  display.println(sensorData.gsrState);

  display.display();
}

void loop()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    displayMax30100 = !displayMax30100; // Toggle between MAX30100 and MPU6050 display
  }

  updateSensors();
  updateDisplay();
  delay(100);

  // Debugging information
  Serial.print("Heart rate raw value: ");
  Serial.println(sensorData.heartRate);
  Serial.print("SpO2 raw value: ");
  Serial.println(sensorData.spO2);
  Serial.print("Acceleration X: ");
  Serial.print(sensorData.accX);
  Serial.print(", Y: ");
  Serial.print(sensorData.accY);
  Serial.print(", Z: ");
  Serial.print(sensorData.accZ);
  Serial.println(" m/s^2");
  Serial.print("Rotation X: ");
  Serial.print(sensorData.gyroX);
  Serial.print(", Y: ");
  Serial.print(sensorData.gyroY);
  Serial.print(", Z: ");
  Serial.print(sensorData.gyroZ);
  Serial.println(" rad/s");
  Serial.print("Temperature: ");
  Serial.print(sensorData.temperature);
  Serial.println(" degC");
  Serial.print("GSR Value: ");
  Serial.print(sensorData.gsrValue);
  Serial.print(" - State: ");
  Serial.println(sensorData.gsrState);
  Serial.println("");
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
