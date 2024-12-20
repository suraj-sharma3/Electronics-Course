#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;


void onBeatDetected() {
    Serial.println("Beat detected!");
}

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");

    if (!pox.begin()) {
        Serial.println("ERROR: Failed to initialize pulse oximeter");
        for (;;); // Stop the program here if initialization fails
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);
    Serial.println("Pulse oximeter initialized");
}

void loop() {
    pox.update();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        float heartRate = pox.getHeartRate();
        float spO2 = pox.getSpO2();

        if (heartRate > 0) {
            Serial.print("Heart rate in BPM: ");
            Serial.println(heartRate);
        } else {
            Serial.println("Heart rate in BPM: Invalid or no reading");
            Serial.println(heartRate);
        }

        if (spO2 > 0) {
            Serial.print("Oxygen in %: ");
            Serial.println(spO2);
        } else {
            Serial.println("Oxygen in %: Invalid or no reading");
            Serial.println(heartRate);
        }

        tsLastReport = millis();
    }
}
