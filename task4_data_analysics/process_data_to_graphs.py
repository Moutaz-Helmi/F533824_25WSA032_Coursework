FILE = "task4_data_analysics\\temperatures.csv"

def read_file(FILE):
    data = []
    file = open(FILE, "r")
    
    for line in file:
        data.append(line.strip().split(","))
    
    file.close()
    return data

def split_data(data):
    time = []
    temperature = []
    frequency = []
    magnitude = []

    for row in data:
        time.append(float(row[0]))
        temperature.append(float(row[1]))
        frequency.append(float(row[2]))
        magnitude.append(float(row[3]))

    return time, temperature, magnitude, frequency

data = read_file(FILE)
#print(data)

time, temperature, magnitude, frequency = split_data(data)

#print("Time:", time)
#print("Temperature:", temperature)
#print("Magnitude:", magnitude)
#print("Frequency:", frequency)