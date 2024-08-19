#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int dhtTemp()
{
    float t = dht.readTemperature();
    int tempInt=int(t);
    return tempInt;

}
int dhtHum(){
float h = dht.readHumidity();
int humInt=int(h);
return humInt;
}
