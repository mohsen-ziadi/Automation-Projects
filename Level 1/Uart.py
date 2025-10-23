import serial
import time

# گرفتن ورودی از کاربر
com_port = input("Enter COM port (e.g., COM7): ")
baud_rate = input("Enter baud rate (e.g., 115200): ")

try:
    ser = serial.Serial(com_port, int(baud_rate), timeout=1)
    time.sleep(2)  # صبر برای راه‌اندازی سریال
    print(f"Connected to {com_port} at {baud_rate} baud.")
except Exception as e:
    print("Error connecting to serial port:", e)
    exit()

# حلقه تعاملی
while True:
    cmd = input("Enter command to send (or 'exit' to quit): ")
    if cmd.lower() == "exit":
        break

    ser.write((cmd + '\n').encode())  # ارسال دستور به آردوینو

    # خواندن پاسخ
    try:
        response = ser.readline().decode().strip()
        if response:
            print("Arduino says:", response)
        else:
            print("No response.")
    except Exception as e:
        print("Error reading from serial:", e)

ser.close()
print("Serial connection closed.")
