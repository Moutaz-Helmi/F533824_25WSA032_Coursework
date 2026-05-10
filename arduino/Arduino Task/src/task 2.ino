#include <header.h>


const int B = 4275000; // B value of the thermistor
const int R0 = 100000; // R0 = 100k
const int pinTempSensor = A0; // Grove - Temperature Sensor connect to A0

float array_of_temps[60]; // Array length 60 because it reads temperature every 3 seconds for 3 minutes (180 seconds)
const int array_length = (sizeof(array_of_temps) / sizeof(array_of_temps[0]));

float real[array_length];
float imag[array_length];
float frequency[array_length];
float magnitude[array_length];

int collect_temperature_data(float array_of_temps[], int index);
int save_to_array(float temperature, float array_of_temps[], int index);
float* apply_dft(float array_of_temps[], int array_length);
void send_data_to_pc(float array_of_temps[], float frequency[], float magnitude[], int array_length);
int decide_power_mode(float frequency[], int array_length);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  // Collect temperature data every 3 seconds for 3 minutes (60 readings)
  for (int index = 0; index < array_length; index++)
  {
    collect_temperature_data(array_of_temps, index);
    delay(3000);
  }

  // Perform DFT on the collected temperature data
  apply_dft(array_of_temps, array_length);

  send_data_to_pc(array_of_temps, frequency, magnitude, array_length);

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
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // convert to temperature via datasheet
    
    Serial.print(index);
    Serial.print(". temperature = ");
    Serial.println(temperature);
    
    save_to_array(temperature, array_of_temps, index);

    return 0;
}

int save_to_array(float temperature, float array_of_temps[], int index)
{
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
    float time = i * 3.0;

    Serial.print(time, 2);
    Serial.print(",");

    Serial.print(array_of_temps[i], 2);
    Serial.print(",");

    Serial.print(frequency[i], 4);
    Serial.print(",");

    Serial.println(magnitude[i], 4);
  }
}

int decide_power_mode(float frequency[], int array_length)
{
    float sum = 0.0;
    float average_frequency;

    // Calculate average frequency
    for (int i = 0; i < array_length; i++)
    {
      sum += frequency[i];
    }

    average_frequency = sum / array_length;
    Serial.print("Average Frequency: ");
    Serial.print(average_frequency, 4);
    Serial.println(" Hz");

    // Decide mode
    if (average_frequency > 0.5)
    {
      return 1; // ACTIVE mode
    }
    else if (average_frequency > 0.1)
    {
      return 2; // IDLE mode
    }
    else
    {
      return 3; // SLEEP mode
    }
}

