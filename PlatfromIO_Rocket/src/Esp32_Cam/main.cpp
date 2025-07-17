#include <Arduino.h>
#include "esp_camera.h"
#include "FS.h"
#include "SD_MMC.h"

#if defined(CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27
#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      21
#define Y4_GPIO_NUM      19
#define Y3_GPIO_NUM      18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22
#endif

void startCamera() {
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

	config.frame_size = FRAMESIZE_QQVGA; // 更小，節省記憶體
	config.jpeg_quality = 12;
	config.fb_count = 1;

	esp_err_t err = esp_camera_init(&config);
	if (err != ESP_OK) {
		Serial.printf("❌ 相機初始化失敗: %s\n", esp_err_to_name(err));
		return;
	}
	Serial.println("✅ 相機初始化成功");
}

void setup() {
	Serial.begin(115200);
	delay(1000);

	// 初始化相機
	startCamera();

	// 初始化 SD 卡
	if (!SD_MMC.begin()) {
		Serial.println("❌ SD 卡掛載失敗");
		return;
	}

	Serial.println("✅ SD 卡初始化成功");

	// 拍照
	camera_fb_t * fb = esp_camera_fb_get();
	if (!fb) {
		Serial.println("❌ 拍照失敗");
		return;
	}

	// 儲存影像到 SD 卡
	File file = SD_MMC.open("/photo.jpg", FILE_WRITE);
	if (!file) {
		Serial.println("❌ 開啟檔案失敗");
	} else {
		file.write(fb->buf, fb->len);
		Serial.println("✅ 照片儲存成功: /photo.jpg");
	}
	file.close();
	esp_camera_fb_return(fb);
}

void loop() {
  // 空的 loop，這是一次性拍照
}


eriogheorhghhh

