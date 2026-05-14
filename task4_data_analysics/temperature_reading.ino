#include <header.h>

const int B = 4275000; // B value of thermistor
const int R0 = 100000; // R0 = 100k
const int pinTempSensor = A0;

const unsigned long sampling_interval = 1000; // 1 reading every 1 second

const int recording_time_seconds = 180; // 3 minutes total
const int total_samples = recording_time_seconds / (sampling_interval / 1000);

float collect_temperature_data();
void send_data_to_pc(float time, float temperature);

void setup()
{
    Serial.begin(9600);

    Serial.println("Time,Temperature");
}

void loop()
{
    // Collect and send data directly to PC
    for (int index = 0; index < total_samples; index++) {
        float time = index * (sampling_interval / 1000.0);

        float temperature = collect_temperature_data();
        send_data_to_pc(time, temperature);
        delay(sampling_interval);
    }

    // Stop repeating
    while (1);
}

float collect_temperature_data()
{
    int a = analogRead(pinTempSensor);
    float R = 1023.0 / a - 1.0;
    R = R0 * R;
    float temperature = 1.0 / (log(R / R0) / B + 1 / 298.15) - 273.15;

    return temperature;
}

void send_data_to_pc(float time, float temperature)
{
    Serial.print(time, 2);
    Serial.print(",");

    Serial.println(temperature, 2);
}