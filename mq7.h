
int gas_ain=A5;
int ad_value;

int detect_gas(){
  
  ad_value=analogRead(gas_ain); //avg is 47. Assume 50 = 0.2 ppm. ad_value/250 = ppm
  
  return ad_value;
}
float ppm_value() //Typ nåt sånt.
{
  float ppm=detect_gas()/250;
  return ppm;
}