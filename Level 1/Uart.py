import serial
import time
import threading

com_port = input("Enter COM port (e.g., COM7): ")
baud_rate = input("Enter baud rate (e.g., 115200): ")

try:
    ser = serial.Serial(com_port, int(baud_rate), timeout=1)
    time.sleep(2)
    print(f"Connected to {com_port} at {baud_rate} baud.")
except Exception as e:
    print("Error connecting:", e)
    exit()

def read_serial():
    while True:
        try:
            response = ser.readline().decode().strip()
            if response:
                print("Arduino:", response)
        except:
            break

threading.Thread(target=read_serial, daemon=True).start()

while True:
    cmd = input()
    if cmd.lower() == "exit":
        break
    ser.write((cmd + '\n').encode())

ser.close()
