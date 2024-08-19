//int gas_din=2;
int gas_ain=A5;
int ad_value;

//pinMode(gas_din,INPUT);


void detectGas(){
  
  ad_value=analogRead(gas_ain);
 // if(digitalRead(gas_din)==LOW)
 // {
  //  Serial.println("Gas leakage");
  //  Serial.println(ad_value);
  //}
  //else
  //{
   // Serial.println("Gas not leak");
  //}
  delay(500);
}