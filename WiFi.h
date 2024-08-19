
#include "WiFiS3.h"
////------------------------------------------------------------NEEDS TO BE CHANGED WHEN SWITCHING WIFI-ADRESS----------------------------------------------------
#include "arduino_secrets.h"  
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;
IPAddress server(IP_ADRESS); //IPAdress for Server/WiFi. 
uint16_t port = PORT_NUMB; //Portnumber
String servStr= server.toString(); //To add IP-adress to sprintf and print to client 

void printWifiStatus();
void read_request();
void connectToWiFi();


// Initialize the WiFi client library
WiFiClient client;

/* -------------------------------------------------------------------------- */
void read_request() {
/* -------------------------------------------------------------------------- */  
  uint32_t received_data_num = 0;

  while (client.available()) 
  {
    /* actual data reception */
    char c = client.read();
    /* print data to serial port */
    Serial.print(c);

    /* wrap data to 80 columns*/
    received_data_num++;
    if(received_data_num % 80 == 0) 
    { 
      
    }
    
  } 

}
void printWifiStatus() {
/* -------------------------------------------------------------------------- */ 


  // print the SSID of the network you're attached to:

  Serial.print("SSID: ");   
  Serial.println(WiFi.SSID());

  //print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");

}
void connectToWiFi()
{
  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    
    // wait 10 seconds for connection:
    delay(10000);

  }
  // you're connected now, so print out the status:
  printWifiStatus();


}
 
// this method makes a HTTP connection to the server:
/* -------------------------------------------------------------------------- */
void httpRequest(String printToClient) {
/* -------------------------------------------------------------------------- */  
  // close any connection before send a new request.
  // This will free the socket on the NINA module
  client.stop();
  char buffer[100]; //For printing host 

  // if there's a successful connection:
  if (client.connect(server, port)) {
    
    Serial.println("\nconnecting...");
    
    // send the HTTP GET request:
    client.println(printToClient);
    client.println("GET / HTTP/1.1");
    
    sprintf(buffer, "Host: %s:/%d HTTP/1.1\n", servStr, port); 
    client.print(buffer); //PRINTS HOST  
   
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    
    
    client.println();


   
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
   
  }
}


