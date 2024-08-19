
#include "DHT_Async.h"
#define DHT_SENSOR_TYPE DHT_TYPE_11

static const int DHT_SENSOR_PIN = 2;
DHT_Async dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
//float temperature, humidity;

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
float temperature, humidity;
int temp,hum;
static bool measure_environment(float *temperature, float *humidity) {
    static unsigned long measurement_timestamp = millis();

    /* Measure once every four seconds. */
    if (millis() - measurement_timestamp > 4000ul) {
        if (dht_sensor.measure(temperature, humidity)) {
            measurement_timestamp = millis();
            return (true);
        }
    }

    return (false);
}

void getTempHum()
{     
    /* Measure temperature and humidity.  If the functions returns
       true, then a measurement is available. */
    if (measure_environment(&temperature, &humidity)) {
    

        Serial.print("T = ");
        Serial.print(temperature, 1);
        Serial.print(" deg. C, H = ");
        Serial.print(humidity, 1);
        Serial.println("%");
    }
 temp =int(temperature);

   hum=int(humidity);

}
