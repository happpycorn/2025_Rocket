#include <Arduino.h>

const TickType_t xFrequencyTask1 = pdMS_TO_TICKS(10);  // Task1: 10ms = 100Hz
const TickType_t xFrequencyTask2 = pdMS_TO_TICKS(20);  // Task2: 20ms = 50Hz

void Task1(void *pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount();  // 記錄當前時刻
  while (1) {
    // 每10ms執行一次
    Serial.println("Task 1 is running...");
    vTaskDelayUntil(&xLastWakeTime, xFrequencyTask1);  // 使用 vTaskDelayUntil 來實現精確定時
  }
}

void Task2(void *pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount();  // 記錄當前時刻
  while (1) {
    // 每20ms執行一次
    Serial.println("Task 2 is running...");
    vTaskDelayUntil(&xLastWakeTime, xFrequencyTask2);  // 使用 vTaskDelayUntil 來實現精確定時
  }
}

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  while (!Serial);  // 等待串口連接

  // 創建任務
  xTaskCreate(Task1, "Task 1", 10000, NULL, 1, NULL);  // 創建 Task 1
  xTaskCreate(Task2, "Task 2", 10000, NULL, 1, NULL);  // 創建 Task 2
}

void loop() {
  // 在主循環中不需要做任何事情，FreeRTOS 會自動控制任務調度
}
