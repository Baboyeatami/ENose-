/*

 * Program to measure gas in ppm using MQ sensor

 * Program by: B.Aswinth Raj

 * Website: www.circuitdigest.com

 * Dated: 28-12-2017

 */

#define RL 47  //The value of resistor RL is 47K
#define m -0.243 //Enter calculated Slope 
#define b 0.39 //Enter calculated intercept
#define Ro 20 //Enter found Ro value 
#define MQ_sensor A2 //Sensor is connected to A2


void setup() {

  Serial.begin(9600); //Baud rate 
}


void loop() {


  float VRL; //Voltage drop across the MQ sensor

  float Rs; //Sensor resistance at gas concentration 

  float ratio; //Define variable for ratio

   

  VRL = analogRead(MQ_sensor)*(5.0/1023.0); //Measure the voltage drop and convert to 0-5V

  Rs = ((5.0*RL)/VRL)-RL; //Use formula to get Rs value

  ratio = Rs/Ro;  // find ratio Rs/Ro

 

  float  ppm = pow(10, ((log10(ratio)-b)/m)); //use formula to calculate ppm

  Serial.print("NH3 (ppm) = "); Serial.println(ppm); //Display a ammonia in ppm
  //Serial.print(ppm);
  //Serial.println("--------------------------------------------------------");
  Serial.print("Voltage = "); Serial.println(VRL); //Display a intro message
  
  delay (1000);
  
  //Serial.print("NH3:       ppm"); //Serial.println(NH3);
  //Serial.print("Voltage:       "); //Serial.println(Voltage);
  Serial.println("--------------------------------------------------------");
//delay (70);
}
