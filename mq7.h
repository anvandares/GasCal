
int gas_ain=A5;
int ad_value;

int detectGas(){
  
  ad_value=analogRead(gas_ain); //avg is 47. Assume 50 = 0.2 ppm. ad_value/250 = ppm
  
  return ad_value;
}
float ppmValue() //Typ nåt sånt.
{
  float ppm=detectGas()/250;
  return ppm;
}