# pip install psutil pyserial
import psutil
import serial
import time
import subprocess
import re

# 본인의 COM 포트 번호로 수정
ser = serial.Serial('COM3', 115200)

def get_amd_gpu_usage():
    try:
        # 윈도우 성능 카운터에서 모든 GPU 엔진의 사용률을 한 번에 조회합니다.
        # 이 명령어는 AMD, NVIDIA 가리지 않고 윈도우가 인식하는 수치를 가져옵니다.
        cmd = 'typeperf "\\GPU Engine(*)\\Utilization Percentage" -sc 1'
        output = subprocess.check_output(cmd, shell=True).decode('utf-8', errors='ignore')
        
        # 출력 내용 중 숫자값(소수점 포함)들만 다 찾아냅니다.
        usage_values = re.findall(r'"(\d+\.\d+)"', output)
        
        if usage_values:
            # 여러 엔진(3D, Video 등) 중 가장 높은 사용률을 가진 값을 선택합니다.
            # Fish Bowl은 보통 '3D' 엔진 수치를 높게 올립니다.
            return int(float(max(usage_values, key=float)))
        return 0
    except:
        return 0

print("모니터링 시작 (부하 테스트 대응)...")

while True:
    # 1. CPU: interval을 줘서 0으로 고정되는 현상 방지
    cpu = int(psutil.cpu_percent(interval=0.5))
    
    # 2. GPU: AMD 전용 로직
    gpu = get_amd_gpu_usage()
    
    # 3. RAM
    ram = int(psutil.virtual_memory().percent)
    
    # 데이터 전송
    payload = f"C:{cpu},G:{gpu},R:{ram}\n"
    ser.write(payload.encode())
    
    print(f"전송: {payload.strip()}      ", end='\r')
    # 위에서 CPU 측정에 0.5초를 썼으므로 추가 sleep은 짧게 줍니다.
    time.sleep(0.1)