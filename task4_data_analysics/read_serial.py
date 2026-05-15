import serial
import time

SERIAL_PORT = "COM7"
BAUD_RATE = 9600
FILE = "temperatures.txt"

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
time.sleep(2)  # Wait for the serial connection to initialize

file = open(FILE, "w")
line = ""
while (ser.readline() != line): # Check if the last line is same as the currently read line, if not continue running, if yes writting to file will stop
    line = ser.readline()
    if not line:
        continue
    s = line.decode(errors="ignore").rstrip('\r\n')
    print(s)

    if file:
        file.write(s + "\n")
        file.flush()

file.close()
ser.close()

