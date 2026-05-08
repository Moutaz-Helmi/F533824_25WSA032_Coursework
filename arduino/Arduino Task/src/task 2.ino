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
  const float fs = 3.0; // sampling frequency in Hz is 3.0 because temperature is read every 3 seconds
  

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

    Serial.print("DFT[");
    Serial.print(k);
    Serial.print("] f=");
    Serial.print(frequency[k], 4);
    Serial.print(" Hz magnitude=");
    Serial.println(magnitude[k], 4);
  }

  return frequency;
}


