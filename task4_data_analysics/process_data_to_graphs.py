import matplotlib.pyplot as plt

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

    return time, temperature, frequency, magnitude

def plot_graphs(time, temperature, frequency, magnitude):
    plt.figure(figsize=(12, 10))

    # Draw plot 1
    plot_1(time, temperature)

    # Draw plot 2
    plot_2(frequency, magnitude)
    
    plt.tight_layout()
    plt.show()

def plot_1(time, temperature):
    plt.subplot(2, 1, 1)

    plt.plot(time, temperature)

    plt.title("Temperature vs Time")
    plt.xlabel("Time (s)")
    plt.ylabel("Temperature (°C)")
    plt.grid(True)


def plot_2(frequency, magnitude):
    plt.subplot(2, 1, 2)

    plt.plot(frequency, magnitude)

    plt.title("Magnitude vs Frequency")
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Magnitude")
    plt.grid(True)


# Read data from the file
data = read_file(FILE)
#print(data)

# Split data into separate lists
time, temperature, frequency, magnitude = split_data(data)

#print("Time:", time)
#print("Temperature:", temperature)
#print("Frequency:", frequency)
#print("Magnitude:", magnitude)

# Plot all graphs
plot_graphs(time, temperature, frequency, magnitude)

