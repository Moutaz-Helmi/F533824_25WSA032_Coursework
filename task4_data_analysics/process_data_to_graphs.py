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

def moving_average(data, window_size):
    smoothed = []

    for i in range(len(data)):
        start = max(0, i - window_size + 1)
        window = data[start:i + 1]
        average = sum(window) / len(window)

        smoothed.append(average)

    return smoothed

def plot_graphs(time, temperature, frequency, magnitude):
    plt.figure(figsize=(15, 15))

    # Draw plot 1
    plot_1(time, temperature)

    # Draw plot 2
    plot_2(frequency, magnitude)

    # Draw plot 3
    plot_3(time, temperature)
    
    plt.tight_layout()
    plt.subplots_adjust(hspace=0.5, wspace=0.3, top=0.95, right= 0.97) # Adjust spacing between subplots
    plt.show()

def plot_1(time, temperature):
    plt.subplot(3, 2, 1)

    plt.plot(time, temperature)

    plt.title("Temperature vs Time (Plot 1)")
    plt.xlabel("Time (s)")
    plt.ylabel("Temperature (°C)")
    plt.grid(True)


def plot_2(frequency, magnitude):
    plt.subplot(3, 2, 2)

    plt.plot(frequency, magnitude)

    plt.title("Magnitude vs Frequency (Plot 2)")
    plt.xlabel("Frequency (Hz)")
    plt.ylabel("Magnitude")
    plt.grid(True)

def plot_3(time, temperature):
    # Calculate smoothed temperature using moving average
    smoothed_temperature = moving_average(temperature, window_size=5)   

    plt.subplot(3, 2, 3)

    plt.plot(time, temperature, label="Original Temperature")
    plt.plot(time, smoothed_temperature, label="Smoothed Temperature")

    plt.title("Smoothed Temperature vs Time (Plot 3)")
    plt.xlabel("Time (s)")
    plt.ylabel("Temperature (°C)")
    plt.legend()
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

