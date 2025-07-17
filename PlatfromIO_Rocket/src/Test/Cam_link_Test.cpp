#include <Arduino.h>
<<<<<<< HEAD
#include "esp_camera.h"

// 選擇板子為 AI-Thinker 模組（常見 ESP32-CAM 模組）
#define PWDN_GPIO_NUM     -1
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

void setup() {
	Serial.begin(115200);
	delay(1000);
	Serial.println("🚀 開始初始化相機...");

	camera_config_t config;
	config.ledc_channel = LEDC_CHANNEL_0;
	config.ledc_timer   = LEDC_TIMER_0;
	config.pin_d0       = Y2_GPIO_NUM;
	config.pin_d1       = Y3_GPIO_NUM;
	config.pin_d2       = Y4_GPIO_NUM;
	config.pin_d3       = Y5_GPIO_NUM;
	config.pin_d4       = Y6_GPIO_NUM;
	config.pin_d5       = Y7_GPIO_NUM;
	config.pin_d6       = Y8_GPIO_NUM;
	config.pin_d7       = Y9_GPIO_NUM;
	config.pin_xclk     = XCLK_GPIO_NUM;
	config.pin_pclk     = PCLK_GPIO_NUM;
	config.pin_vsync    = VSYNC_GPIO_NUM;
	config.pin_href     = HREF_GPIO_NUM;
	config.pin_sccb_sda = SIOD_GPIO_NUM;
	config.pin_sccb_scl = SIOC_GPIO_NUM;
	config.pin_pwdn     = PWDN_GPIO_NUM;
	config.pin_reset    = RESET_GPIO_NUM;
	config.xclk_freq_hz = 20000000;
	config.pixel_format = PIXFORMAT_JPEG;

	// 初始化為 SVGA 解析度
	config.frame_size = FRAMESIZE_SVGA;
	config.jpeg_quality = 10;
	config.fb_count = 1;

	// 初始化相機
	esp_err_t err = esp_camera_init(&config);
	if (err != ESP_OK) {
		Serial.printf("❌ 相機初始化失敗: 0x%x\n", err);
		return;
	}

	Serial.println("✅ 相機初始化成功！");
=======
#include <Wire.h>

void setup() {
    Serial.begin(9600);
    delay(2000);
    Serial.println("Start");

    for (int sda = 0; sda <= 22; sda++) {
        for (int scl = 0; scl <= 22; scl++) {
            if (sda == scl) continue; // Skip same-pin pair

            Wire.begin(sda, scl);
            delay(50);  // Small delay to stabilize

            for (byte addr = 8; addr < 120; addr++) {
                Wire.beginTransmission(addr);
                if (Wire.endTransmission() == 0) {
                    Serial.printf("%d, %d, 0x%02X\n", sda, scl, addr);
                }
            }

            Wire.end();  // Clean up for next combination
        }
    }

    Serial.println("Complete");
>>>>>>> 0723411855f5136b95aedc6181e990972f3d71e2
}

void loop() {}
