///this code is written and tested for ncd.io IoT Long Range Wireless Analog To Digital Converter Transmitter with arduino due
///sensor data structure can be found here https://ncd.io/long-range-iot-wireless-analog-to-digital-converter-product-manual/
/// sensor can be found here https://store.ncd.io/product/iot-long-range-wireless-analog-digital-converter3-3v/

  uint8_t data[29];
  int k = 10;
  int i;
void setup()
{
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial.println("ncd.io IoT Arduino Wireless Analog To Digital Converter Transmitter");
}

void loop()
{
  
  if (Serial1.available())
  {
    data[0] = Serial1.read();
    delay(k);
   if(data[0]==0x7E)
    {
    while (!Serial1.available());
    for ( i = 1; i< 29; i++)
      {
      data[i] = Serial1.read();
      delay(1);
      }
    if(data[15]==0x7F)  /////// to check if the recive data is correct
      {
  if(data[22]==3)  //////// make sure the sensor type is correct
        {
          int adc_ch1 = ((data[24] * 256) + data[25]);   
          int adc_ch2 = ((data[26] * 256) + data[27]); 
  float battery = ((data[18] * 256) + data[19]);
  float voltage = 0.00322 * battery;
  Serial.print("Sensor Number  ");
  Serial.println(data[16]);
  Serial.print("Sensor Type  ");
  Serial.println(data[22]);
  Serial.print("Firmware Version  ");
  Serial.println(data[17]);
  Serial.print("Analog input at Channel One :");
  Serial.println(adc_ch1);
  Serial.print("Analog input at Channel Two :");
  Serial.println(adc_ch2);
  Serial.print("ADC value:");
  Serial.println(battery);
  Serial.print("Battery Voltage:");
  Serial.print(voltage);
  Serial.println("\n");
  if (voltage < 1)
          {
    Serial.println("Time to Replace The Battery");
          }
  
        }
      }
else
{
      for ( i = 0; i< 29; i++)
    {
      Serial.print(data[i]);
      Serial.print(" , ");
      delay(1);
    }
}
    }
  }
 
}
