// Arduino_Thermistor_Reader.
// Voltage Bias - the Blog.
// Gilbert Waltoon, Oct 2016

// Released under a GNU General Public License v3.0 

// PURPOSE: Reads the voltage of a thermistor voltage divider
//          and converts to temperature.

// Input pin for thermistor voltage measurement
#define THERMISTORPIN A5

// the value of the bias resistor
#define BIAS_RESISTOR 9926

 //beta of thermistor 
#define BCOEFFICIENT 3933 //RComponents, type 151-237

// thermistor resistance R0 from datasheet
#define R0 10000 

//...at temperature
#define T0 25

//declare the function we'll use
float getThermistorTemperature(void);

//////////////////////////////////////////////////////////////

void setup() {
  //start the serial monitor for printing to screen
  Serial.begin(9600);
  }
 
////////////////////////////////////////////////////////////
void loop() {
  float msgData = getThermistorTemperature();
  Serial.print("Temperature="); Serial.println(msgData);
  delay(2000);
}

/////////////////////////////////////////////////////////////
// define the function getThermistorTemperature()
float getThermistorTemperature(void) {
  float fTemperature;
  float fADCReading;
  float fThermistance; //thermistor resistance
 
  fADCReading = analogRead(THERMISTORPIN);
 
  // get the thermistor resistance from ADC reading
  fThermistance = BIAS_RESISTOR/((1023 / fADCReading)  - 1);

  // convert resistance to temperature using the Beta equation
  // see https://en.wikipedia.org/wiki/Thermistor

  fTemperature = fThermistance / R0;                      
  fTemperature = log(fTemperature);             
  fTemperature /= BCOEFFICIENT;                          // 1/Beta * ln(R/R0)
  fTemperature += 1.0 / (T0 + 273.15);                   // ...+ (1/To)
  fTemperature = 1.0 / fTemperature         ;            // ...invert
  fTemperature -= 273.15;                                // ...convert to 'C

  return fTemperature;
}



