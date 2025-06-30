#include <Arduino.h>

const TickType_t xFrequencyTask1 = pdMS_TO_TICKS(10);
const TickType_t xFrequencyTask2 = pdMS_TO_TICKS(20);

void Task1(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        Serial.println("Task 1 is running...");
        vTaskDelayUntil(&xLastWakeTime, xFrequencyTask1);
    }
}

void Task2(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    while (1) {
        Serial.println("Task 2 is running...");
        vTaskDelayUntil(&xLastWakeTime, xFrequencyTask2);
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial);

    xTaskCreate(Task1, "Task 1", 10000, NULL, 1, NULL);
    xTaskCreate(Task2, "Task 2", 10000, NULL, 1, NULL);
}

void loop() {}
