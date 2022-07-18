#include <MQUnifiedsensor.h>

#define         Board                   ("Arduino NANO")
#define         Pin3                     (A0)  //Analog input 0 of your arduino
#define         Pin135                   (A1)  //Analog input 1 of your arduino


#define         RatioMQ3CleanAir          (60) //RS / R0 = 60 ppm 
#define         RatioMQ135CleanAir        (3.6) //RS / R0 = 10 ppm 
#define         ADC_Bit_Resolution        (10) // 10 bit ADC 
#define         Voltage_Resolution        (5) // Volt resolution to calc the voltage
#define         Type                      ("Arduino NANO") //Board used

//Declare Sensor
MQUnifiedsensor MQ3(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin3, Type);
MQUnifiedsensor MQ135(Board, Voltage_Resolution, ADC_Bit_Resolution, Pin135, Type);


void setup() {
  Serial.begin(9600);
  
                       

  MQ3.init();
  MQ3.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ3.setR0(0.45);
 
  MQ135.init();
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^b
  MQ135.setR0(9.03);
 

//While calibrating Your sensor Uncomment this calibration portion and calibrate for R0.
 /*****************************  MQ CAlibration ********************************************
  Serial.print("Calibrating please wait.");
  float  MQ3calcR0 = 0,
         MQ4calcR0 = 0,
         MQ135calcR0 = 0,
         MQ7calcR0 = 0,
         MQ8calcR0 = 0,
         MQ9calcR0 = 0;
  for (int i = 1; i <= 10; i ++)
  {
    //Update the voltage lectures
    MQ3.update();
    MQ4.update();
    MQ135.update();
    MQ7.update();
    MQ8.update();
    MQ9.update();

    MQ3calcR0 += MQ3.calibrate(RatioMQ3CleanAir);
    MQ4calcR0 += MQ4.calibrate(RatioMQ4CleanAir);
    MQ135calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    MQ7calcR0 += MQ7.calibrate(RatioMQ7CleanAir);
    MQ8calcR0 += MQ8.calibrate(RatioMQ8CleanAir);
    MQ9calcR0 += MQ9.calibrate(RatioMQ9CleanAir);

    Serial.print(".");
  }
  MQ3.setR0(MQ3calcR0 / 10);
  MQ4.setR0(MQ4calcR0 / 10);
  MQ135.setR0(MQ135calcR0 / 10);
  MQ7.setR0(MQ7calcR0 / 10);
  MQ8.setR0(MQ8calcR0 / 10);
  MQ9.setR0(MQ9calcR0 / 10);
  Serial.println("  done!.");

  Serial.print("(MQ3 - MQ9):");
  Serial.print(MQ3calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ4calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ135calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ7calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ8calcR0 / 10); Serial.print(" | ");
  Serial.print(MQ9calcR0 / 10); Serial.println(" |");

  /*****************************  MQ CAlibration ********************************************/ 
}

void loop() {
  //Update the voltage lectures
  MQ3.update();
  MQ135.update();  
  

  MQ3.setA(0.3934); MQ3.setB(-1.504); //Alcohol
float Alcohol = MQ3.readSensor(); 

  MQ3.setA(4.8387); MQ3.setB(-2.68); //Benzene
float Benzene = MQ3.readSensor(); 
  
  MQ3.setA(7585.3); MQ3.setB(-2.849); //Hexane
float Hexane = MQ3.readSensor(); 

MQ3.setA(1012.7); MQ3.setB(-2.786); //CH4
float CH4 = MQ3.readSensor(); 

  
  
 MQ135.setA(102.2 ); MQ135.setB(-2.473); //NH3 
float NH3 = MQ135.readSensor(); 

MQ135.setA(976.97); MQ135.setB(-0.688); // H2
float H2 = MQ135.readSensor();


 MQ135.setA(30000000); MQ135.setB(-8.308); //smoke 
float Smoke = MQ135.readSensor();  

  MQ135.setA(99.042); MQ135.setB(-1.518); //CO
float CO = MQ135.readSensor(); 


  Serial.print("MQ3     Alcohol:  "); Serial.println(Alcohol);
  Serial.print("MQ3     Hexane:   "); Serial.println(Hexane);
  Serial.print("MQ3     Methane:  "); Serial.println(CH4);
  Serial.print("MQ135   Benzene:  "); Serial.println(Benzene);
  Serial.print("MQ135   Smoke:    "); Serial.println(Smoke);
  Serial.print("MQ135   CO:       "); Serial.println(CO);
  Serial.print("MQ137   Ammonia:  "); Serial.println(NH3); 
  Serial.print("TGS2600 H2:       "); Serial.println(H2);
  Serial.println("--------------------------------------------------------");
delay (10000);
}
