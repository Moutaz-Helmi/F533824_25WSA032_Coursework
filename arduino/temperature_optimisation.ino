#include <header.h>

const int B = 4275000; // B value of the thermistor
const int R0 = 100000; // R0 = 100k
const int pinTempSensor = A0; // Grove - Temperature Sensor connect to A0

float array_of_temps[180]; // Array length 180 because it reads temperature every 3 seconds for 3 minutes (180 seconds)
const int array_length = (sizeof(array_of_temps) / sizeof(array_of_temps[0]));

float real[array_length];
float imag[array_length];
float frequency[array_length];
float magnitude[array_length];

float variation_history[10];
int stable_cycles = 0;

float sampling_frequency = 1.0; // Initial sampling frequency
unsigned long sampling_interval = 3000; // Initial sampling interval

int collect_temperature_data(float array_of_temps[], int index);
float* apply_dft(float array_of_temps[], int array_length);
void send_data_to_pc(float array_of_temps[], float frequency[], float magnitude[], int array_length);
int decide_power_mode(float frequency[], int array_length);
float calculate_variation(float array_of_temps[], int array_length);
float calculate_moving_average(float variation);
float find_dominant_frequency(float frequency[], float magnitude[], int array_length);
void update_sampling_rate(int mode, float dominant_frequency);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Collect temperature data, intervals decided with update_sampling_rate() function returning sampling_interval
  for (int index = 0; index < array_length; index++)
  {
    collect_temperature_data(array_of_temps, index);
    delay(sampling_interval);
  }
  Serial.println("END");

  // Perform DFT on the collected temperature data
  apply_dft(array_of_temps, array_length);

  // Send data to PC
  send_data_to_pc(array_of_temps, frequency, magnitude, array_length);

  // Decide power mode based on the analysis of the temperature data
  int mode = decide_power_mode(frequency, array_length);

  if (mode == 1) {
    Serial.println("ACTIVE MODE");
  }
  else if (mode == 2) {
    Serial.println("IDLE MODE");
  }
  else {
    Serial.println("POWER DOWN MODE");
  }
}

int collect_temperature_data(float array_of_temps[], int index)
{
    int a = analogRead(pinTempSensor);
    float R = 1023.0/a-1.0;
    R = R0*R;
    float time = index * (sampling_interval / 1000.0); // convert to seconds
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
    array_of_temps[index] = temperature;
    return 0;
}

float* apply_dft(float array_of_temps[], int array_length)
{
  const float fs = 1.0 / 3.0; // sampling frequency in Hz is 1 / 3 because temperature is read once every 3 seconds
  
  for (int k = 0; k < array_length; k++) {
    real[k] = 0.0;
    imag[k] = 0.0;

    for (int n = 0; n < array_length; n++) {
      float angle = 2.0 * PI * k * n / array_length;
      real[k] += array_of_temps[n] * cos(angle);
      imag[k] -= array_of_temps[n] * sin(angle);
    }

    magnitude[k] = sqrt(real[k] * real[k] + imag[k] * imag[k]);
    frequency[k] = (k * fs) / array_length;

    // Commented out, used for debugging
    //Serial.print("DFT[");
    //Serial.print(k);
    //Serial.print("] f=");
    //Serial.print(frequency[k], 4);
    //Serial.print(" Hz magnitude=");
    //Serial.println(magnitude[k], 4);
  }

  return frequency;
}

void send_data_to_pc(float array_of_temps[], float frequency[], float magnitude[], int array_length)
{
  Serial.println("Time,Temperature,Frequency,Magnitude");

  for (int i = 0; i < array_length; i++)
  {
    float time = i * (sampling_interval / 1000.0);

    Serial.print(time, 2);
    Serial.print(",");

    Serial.print(array_of_temps[i], 2);
    Serial.print(",");

    Serial.print(frequency[i], 4);
    Serial.print(",");

    Serial.println(magnitude[i], 4);
  }
}

float calculate_variation(float array_of_temps[], int array_length)
{
  float total_difference = 0.0;

  for (int i = 1; i < array_length; i++) {
    total_difference += abs(array_of_temps[i] - array_of_temps[i - 1]);
  }

  return total_difference / (array_length - 1);
}

float calculate_moving_average(float variation)
{
  float sum = 0.0;

  for (int i = 0; i < 9; i++) {
    variation_history[i] = variation_history[i + 1];
  }

  variation_history[9] = variation;

  for (int i = 0; i < 10; i++) {
    sum += variation_history[i];
  }

  return sum / 10.0;
}

float find_dominant_frequency(float frequency[], float magnitude[], int array_length)
{
  int dominant_index = 1;

  float max_magnitude = magnitude[1];

  // Ignore DC component at k = 0
  for (int i = 2; i < array_length / 2; i++){
    if (magnitude[i] > max_magnitude) {
      max_magnitude = magnitude[i];

      dominant_index = i;
    }
  }

  return frequency[dominant_index];
}

void update_sampling_rate(int mode, float dominant_frequency)
{
  // Nyquist theorem
  float minimum_sampling_frequency = dominant_frequency * 2.0;

  // Clamp sampling frequency
  if (minimum_sampling_frequency < 0.5) {
    minimum_sampling_frequency = 0.5;
  }

  if (minimum_sampling_frequency > 4.0) {
    minimum_sampling_frequency = 4.0;
  }

  if (mode == 1) {
    // ACTIVE MODE
    sampling_frequency = minimum_sampling_frequency;

    if (sampling_frequency < 1.0) {
      sampling_frequency = 1.0;
    }
  }
  else if (mode == 2){
    // IDLE MODE
    sampling_frequency = 0.5;
  }
  else{
    // POWER DOWN MODE
    sampling_frequency = 0.1;
  }

  sampling_interval = (1000.0 / sampling_frequency);

  Serial.print("Sampling Frequency: ");
  Serial.print(sampling_frequency, 4);
  Serial.println(" Hz");
  Serial.print("Sampling Interval: ");
  Serial.print(sampling_interval);
  Serial.println(" ms");
}

int decide_power_mode(float frequency[], int array_length)
{
  float variation = calculate_variation(array_of_temps, array_length);
  float moving_average = calculate_moving_average(variation);
  float dominant_frequency = find_dominant_frequency(frequency, magnitude, array_length);
  int mode;

  Serial.print("Temperature Variation: ");
  Serial.println(variation, 4);
  Serial.print("Moving Average: ");
  Serial.println(moving_average, 4);
  Serial.print("Dominant Frequency: ");
  Serial.print(dominant_frequency, 4);
  Serial.println(" Hz");

  // Decide mode
  if (moving_average > 0.5)
  {
    mode = 1; // ACTIVE mode
    stable_cycles = 0;
  }
  else if (moving_average > 0.1)
  {
    mode = 2; // IDLE mode
    stable_cycles = 0;
  }
  else
  {
    stable_cycles++;

    if (stable_cycles >= 5){
      mode = 3; // SLEEP mode
    }
    else {
      mode = 2; // IDLE mode
    } 
  }
  update_sampling_rate(mode, dominant_frequency);
  return mode;
}

