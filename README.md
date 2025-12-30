**📊 Usage Monitor (ESP32-C3 & OLED)**

ESP32-C3와 OLED 디스플레이를 활용하여 PC의 리소스(CPU, GPU, RAM) 사용량을 실시간으로 모니터링하는 대시보드입니다. 특히 AMD GPU 환경에서 아드레날린(Adrenalin) 수치와 동기화되도록 설계되었습니다.

**✨ 주요 기능 (Features)**
실시간 모니터링: CPU, GPU, RAM 사용량을 0.5초 단위로 갱신

가독성 특화 UI: 큰 숫자와 가로형 게이지 바를 통한 직관적인 디자인

AMD GPU 최적화: 윈도우 성능 카운터를 활용하여 AMD 그래픽카드 부하 정확히 측정

경량 시스템: Python 스크립트와 ESP32 간의 가벼운 시리얼 통신

**🛠 하드웨어 구성 (Hardware)**
MCU: ESP32-C3 SuperMini

Display: SSD1306 128x64 I2C OLED

Pin Map: | OLED Pin | ESP32-C3 Pin | | :--- | :--- | | VCC | 3.3V | | GND | GND | | SDA | GPIO 8 | | SCL | GPIO 9 |

**🚀 시작하기 (Getting Started)**

1. 전제 조건 (Prerequisites)
PC에 Python 3.x가 설치되어 있어야 합니다.

2. 라이브러리 설치 (Installation)
PC 터미널(CMD/PowerShell)에서 아래 명령어를 실행하여 필요한 라이브러리를 설치합니다.

Bash

pip install psutil pyserial
3. ESP32 펌웨어 업로드 (Firmware)
VS Code에서 PlatformIO를 실행합니다.

src/main.cpp 코드를 ESP32-C3에 업로드합니다.

platformio.ini에 U8g2 라이브러리가 포함되어 있는지 확인하세요.

4. 실행 (Running)
esp32.py 파일을 엽니다.

자신의 PC 환경에 맞는 COM 포트 번호를 수정합니다. (예: COM3)

스크립트를 실행합니다:

Bash

python esp32.py

**📝 참고 사항 (Notes)**
가독성 이슈: OLED 상단 가려짐 현상을 방지하기 위해 UI 좌표를 하단으로 오프셋 조정하였습니다.

줄바꿈 경고: 윈도우 환경에서 git add 시 발생하는 CRLF 경고는 무시해도 무방합니다.
