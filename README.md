# READ ME

This file is in the 'root of your project.
You can use this to provide top-level documentation of your project

# Steps to run the project:

- First make sure that you have the necessary libraries installed in your Arduino IDE and Python environment.
- For Arduino, you will need to install the Arduino IDE.
- For Python, you will need to install libraries such as pyserial and matplotlib.

## Task 2:
- Open temperature_optimisation.ino from src folder
- Copy contents of the file and paste it into Arduino IDE
- Delete the first line of the code which is #include "header.h"
- Connect your Arduino board to your computer
- Select the correct board and port from the tools menu
- Click on the upload button to upload the code to the Arduino board
- Make sure the Arduino Shield and Temperature Sensor are properly connected to the Arduino board
- Once the code is uploaded, the Arduino board will start reading temperature data from the sensor and sending it to the serial monitor
- The serial monitor will display the temperature readings in real-time, also frequency and magnitude once calculated, and power mode once decided

## Task 4:
- Follow the same steps as Task 2 to upload the code to the Arduino board
- Navigate to the read_serial.py file in the task4_data_analysis folder
- Run the read_serial.py file using Python to read the serial data from the Arduino board
- The data will be live printed in the console as it is received from the Arduino board
- Wait for 3 minutes to pass, the code will automatically end when all the data is written in the file
- Data can be seen in the temperatures.csv file in the task4_data_analysis folder
- Next, open the process_data_to_graphs.py file in the task4_data_analysis folder
- Run the process_data_to_graphs.py file using Python to process the data and generate graphs
- The graphs will appear on your screen using matplotlib library
- An image file of my readings is saved in the task4_data_analysis folder with the name Figure_1.png if the graphs do not appear fully / clearly