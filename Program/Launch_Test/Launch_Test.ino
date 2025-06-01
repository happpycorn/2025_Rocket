#include <SD.h>
#include <SPI.h>
#include <ParachuteSystem.h>

ParachuteSystem prcSystem; 

// 定義常數
const int SD_CS_PIN = 5;               // SD 卡的 Chip Select 引腳
const String INPUT_FILE = "test.csv";  // 輸入 CSV 檔案名稱
const String OUTPUT_FILE = "output.csv"; // 輸出 CSV 檔案名稱
const float SLHPA = 1013.25;

File inputFile, outputFile;

// 將布林陣列轉換為字串
String boolArrayToString(bool arr[], int size) {
    String result = "";
    for (int i = 0; i < size; i++) {
        result += String(arr[i]);
        if (i < size - 1) result += ",";  // 用逗號分隔
    }
    return result;
}

float readAltitude(float pressure, float seaLevelhPa) {
  
    return 44330 * (1.0 - pow(pressure / seaLevelhPa, 0.1903));
}

void listFiles() {
  File root = SD.open("/");
  while (true) {
    File entry = root.openNextFile();
    if (!entry) break;
    Serial.print("Found file: ");
    Serial.println(entry.name());
    entry.close();
  }
}

void setup() {
    Serial.begin(115200);
        
    // 初始化 SD 卡
    if (!SD.begin(SD_CS_PIN, SPI, 1000000)) {  // 使用常數 SD_CS_PIN
        Serial.println("SD 卡初始化失敗！");
        return;
    }

    listFiles();

    // 開啟輸入檔案 (data.csv)
    inputFile = SD.open(INPUT_FILE, FILE_READ);  // 使用常數 INPUT_FILE
    if (!inputFile) {
        Serial.println("無法打開 input 檔案！");
        return;
    }

    // 開啟輸出檔案 (output.csv)，如果已經存在則覆蓋
    outputFile = SD.open(OUTPUT_FILE, FILE_WRITE);  // 使用常數 OUTPUT_FILE
    if (!outputFile) {
        Serial.println("無法創建 output 檔案！");
        return;
    }

    // 讀取每行數據並處理
    while (inputFile.available()) {
        String line = inputFile.readStringUntil('\n');  // 讀取一行
        float input = line.toFloat();  // 轉換為浮點數

        float altiude;
        altiude = readAltitude(input, SLHPA);

        float s;
        bool deployedState[3], c1f, c2f;

        prcSystem.decideDeployment(
            input, s, deployedState, 
            c1f, c2f
        );  // 調用插件

        // 顯示結果並寫入輸出檔案
        String outputLine = "";
        outputLine += String(input) + ",";
        outputLine += String(altiude) + ",";
        outputLine += String(s, 2) + ",";
        outputLine += boolArrayToString(deployedState, 3) + ",";
        outputLine += String(c1f) + ",";
        outputLine += String(c2f);

        outputFile.println(outputLine);  // 將結果寫入 output.csv
        Serial.println(outputLine);  // 同時顯示在 Serial Monitor
    }

    // 關閉檔案
    inputFile.close();
    outputFile.close();
}

void loop() {}
