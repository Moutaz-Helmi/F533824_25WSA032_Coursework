import serial
import time

SERIAL_PORT = "COM7"
BAUD_RATE = 9600
FILE = "task4_data_analysics\\temperatures.csv"

ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=3)
time.sleep(2)  # Wait for the serial connection to initialize


file = open(FILE, "w")
s = ""
while (s != "START"): # Check if the first line is "START", if not continue running, if yes writting to file will start
    line = ser.readline()
    if not line:
        continue
    s = line.decode(errors="ignore").rstrip('\r\n')
    print(s)
while (s != "END"): # Check if the last line is "END", if not continue running, if yes writting to file will stop
    line = ser.readline()
    if not line:
        continue
    s = line.decode(errors="ignore").rstrip('\r\n')
    print(s)

    if (len(s.split(",")) == 4): # Check if line has 4th indexes, if yes then write line to file, if not then ignore the line
        if file and s != "END": # If the file is open and the line is not "END", write the line to the file
            file.write(s + "\n")
            file.flush()

file.close()
ser.close()