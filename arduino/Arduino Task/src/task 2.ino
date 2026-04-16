#include <header.h>


const int B = 4275000; // B value of the thermistor
const int R0 = 100000; // R0 = 100k
const int pinTempSensor = A0; // Grove - Temperature Sensor connect to A0

int index = 0;
float array_of_temps[180];

int collect_temperature_data(float array_of_temps[], int index);
int save_to_array(float temperature, float array_of_temps[], int index);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
  while (index <= (sizeof(array_of_temps) / sizeof(array_of_temps[0])))
  {
    collect_temperature_data(array_of_temps, index);
    index++;
    delay(1000);
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