#include <Arduino.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, 9, 8);

int cpu = 0, gpu = 0, ram = 0;

void drawBlock(int y, const char* label, int val) {
    // 1. 라벨 (위치 하향 조정)
    u8g2.setFont(u8g2_font_6x12_tf);
    u8g2.drawStr(2, y - 11, label);

    // 2. 수치 (오른쪽 정렬 및 위치 조정)
    u8g2.setFont(u8g2_font_7x14_tf);
    u8g2.setCursor(95, y - 11);
    if(val < 10) u8g2.print(" "); 
    u8g2.print(val); u8g2.print("%");

    // 3. 게이지 바 (높이를 살짝 줄여 여백 확보)
    u8g2.drawFrame(0, y - 9, 128, 9); 
    u8g2.drawBox(2, y - 7, (val * 124 / 100), 5); 
}

void setup() {
    Serial.begin(115200);
    u8g2.begin();
}

void loop() {
    if (Serial.available() > 0) {
        String data = Serial.readStringUntil('\n');
        int cIdx = data.indexOf("C:");
        int gIdx = data.indexOf(",G:");
        int rIdx = data.indexOf(",R:");
        
        if (cIdx != -1 && gIdx != -1 && rIdx != -1) {
            cpu = data.substring(cIdx + 2, gIdx).toInt();
            gpu = data.substring(gIdx + 3, rIdx).toInt();
            ram = data.substring(rIdx + 3).toInt();

            u8g2.clearBuffer();

            // 상단 가려짐 방지를 위해 첫 시작을 22px로 내림 (22, 43, 64)
            drawBlock(22, "CPU", cpu);
            drawBlock(43, "GPU", gpu);
            drawBlock(64, "RAM", ram);

            u8g2.sendBuffer();
        }
    }
}