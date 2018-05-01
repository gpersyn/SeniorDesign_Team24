//mq-7 time setup
int time_scale = 8; /
int Buzzer=5;
int GreenLED=9;
int RedLED=10;
int COThreshhold=200;
int MethaneThreshhold=10;
int ButaneThreshhold=100;
unsigned long previousMillis1=0;
unsigned long previousMillis2=0;
unsigned long previousMillis3=0;
unsigned long previousMillis4=0;
int Buzzerlevel = 0;
int GreenLEDlevel=LOW;
int RedLEDlevel=LOW;
long time1000=1000;
long time500=500;
long time100=100;
long time50=50;

//mq=2 defines
#define         MQ_PIN                       (3)     //analog input used
#define         RL_VALUE                     (5)     //load resistane in Kohm
#define         RO_CLEAN_AIR_FACTOR          (9.83)  //RO_CLEAR_AIR_FACTOR=(Sensor resistance in clean air)/RO,
                                                     // derived from datasheet

/***********************Software Related Macros************************************/
#define         CALIBARAION_SAMPLE_TIMES     (50)    //how many samples in the calibration phase
#define         CALIBRATION_SAMPLE_INTERVAL  (500)   //time interval(in milisecond) between each samples in the
                                                     //cablibration phase
#define         READ_SAMPLE_INTERVAL         (50)    //how many samples in normal operation
#define         READ_SAMPLE_TIMES            (5)     //define the time interal(in milisecond) between each samples in 
                                                     //normal operation

/**********************Application Related Macros**********************************/
#define         GAS_Butane                      (0) //defined as butane but same result for propane
#define         GAS_Methane                       (1)


/*****************************Globals***********************************************/
float           ButaneCurve[3]  =  {2.3,0.21,-0.47};   //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent"
                                                    //to the original curve. 
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.21), point2: (lg10000, -0.59) 
float           MethaneCurve[3]  =  {2.3,0.72,-0.34};    //two points are taken from the curve. 
                                                    //with these two points, a line is formed which is "approximately equivalent" 
                                                    //to the original curve.
                                                    //data format:{ x, y, slope}; point1: (lg200, 0.72), point2: (lg10000,  0.15                                   
float           Ro           =  10;                 //Ro is initialized to 10 kilo ohms

//mq-7 all before void setup

void setTimer2PWM(byte chA, byte chB) //pins D11 and D3
{
  TCCR2A = 0b10100011; //OCA,OCB, fast pwm
  TCCR2B = 0b001; //no prescaler
  OCR2A = chA; //0..255
  OCR2B = chB;
}

float opt_voltage = 0;
byte opt_width = 240; //default reasonable value

void pwm_adjust()
// function tries various PWM cycle widths and prints resulting voltage for each attempt, then selects best fitting one and
{
  float previous_v = 5.0; //voltage at previous attempt
  float raw2v = 5.0 / 1024.0;//coefficient to convert Arduino's 
  //analogRead result into voltage in volts
  for(int w = 0; w < 250; w++)
  {
    setTimer2PWM(0, w);
    float avg_v = 0;
    for(int x = 0; x < 100; x ++) //measure over about 100ms to ensure stable result
    {
      avg_v += analogRead(A1);
      delay(time_scale);
    }
    avg_v *= 0.01;
    avg_v *= raw2v;
    Serial.print("adjusting PWM w=");
    Serial.print(w);
    Serial.print(", V=");
    Serial.println(avg_v);
    if(avg_v < 3.6 && previous_v > 3.6) //optimal width
    {
      float dnew = 3.6 - avg_v; //current width
      float dprev = previous_v - 3.6;//previous width
      if(dnew < dprev) //if new is closer to 1.4 then return it
      {
        opt_voltage = avg_v;
        opt_width = w;
        return;
      }
      else //else return previous
      {
        opt_voltage = previous_v;
        opt_width = w-1;
        return;
      }
    }
    previous_v = avg_v;
  }
}

float reference_resistor_kOhm = 10.0; //fill correct resisor value if you are using not 10k reference
float sensor_reading_clean_air = 620; //fill with clean air measurement before heating
float sensor_reading_100_ppm_CO = -1; //update later with known measurement for calibration
float sensor_100ppm_CO_resistance_kOhm; //calculated from sensor_reading_100_ppm_CO variable
float sensor_base_resistance_kOhm; //calculated from sensor_reading_clean_air variable
byte phase = 0; //1 - high voltage, 0 - low voltage, we start from measuring
unsigned long prev_ms = 0; //milliseconds in previous cycle
unsigned long sec10 = 0; //this timer is updated 10 times per second,
unsigned long high_on = 0; //time when we started high temperature cycle
unsigned long low_on = 0; //time when we started low temperature cycle
unsigned long last_print = 0; //time when we last printed message in serial

float sens_val = 0; //current smoothed sensor value
float last_CO_ppm_measurement = 0; //CO concentration at the end of previous measurement cycle

float raw_value_to_CO_ppm(float value)
{
  if(value < 1) return -1; //wrong input value
  sensor_base_resistance_kOhm = reference_resistor_kOhm * 1023 / sensor_reading_clean_air - reference_resistor_kOhm;
  if(sensor_reading_100_ppm_CO > 0)
  {
    sensor_100ppm_CO_resistance_kOhm = reference_resistor_kOhm * 1023 / sensor_reading_100_ppm_CO - reference_resistor_kOhm;
  }
  else
  {
    sensor_100ppm_CO_resistance_kOhm = sensor_base_resistance_kOhm * 0.5;

  }
  float sensor_R_kOhm = reference_resistor_kOhm * 1023 / value - reference_resistor_kOhm;
  float R_relation = sensor_100ppm_CO_resistance_kOhm / sensor_R_kOhm;
  float CO_ppm = 100 * (exp(R_relation) - 1.648);
  if(CO_ppm < 0) CO_ppm = 0;
  return CO_ppm;
}

void startMeasurementPhase()
{
  phase = 0;
  low_on = sec10;
  setTimer2PWM(0, opt_width);
}

void startHeatingPhase()
{
  phase = 1;
  high_on = sec10;
  setTimer2PWM(0, 255);
}

//////
void setup() {
  pinMode(GreenLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(Buzzer,OUTPUT);
   //mq-7 setup
  pinMode(3, OUTPUT); //return to VVcircuit
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A0, INPUT); 
  pinMode(A1, INPUT);
  analogReference(DEFAULT);

 //mq-2 setup
                               //UART setup, baudrate = 9600bps
  Serial.begin(9600);
  Serial.print("Calibrating...\n");                
  Ro = MQCalibration(MQ_PIN);                       //Calibrating the sensor. make sure the sensor is in clean air 
                                                    //when you perform the calibration                    
  Serial.print("Calibration is done...\n"); 
  Serial.print("Ro=");
  Serial.print(Ro);
  Serial.print("kohm");
  Serial.print("\n");
  


  pwm_adjust();

  Serial.print("PWM result: width ");
  Serial.print(opt_width);
  Serial.print(", voltage ");
  Serial.println(opt_voltage);
  
 /////
   analogWrite(Buzzer,150);
  delay(100);
  analogWrite(Buzzer,0);
  delay(100);
  analogWrite(Buzzer,150);
  delay(100);
  analogWrite(Buzzer,0);
  delay(100);
  analogWrite(Buzzer,150);
  delay(100);
  analogWrite(Buzzer,0);
  delay(100);
  analogWrite(Buzzer,150);
  delay(100);
  analogWrite(Buzzer,0);
  delay(300);
  //canneck
  analogWrite(Buzzer,150);
  delay(100);
  analogWrite(Buzzer,0);
  delay(100);
  analogWrite(Buzzer,150);
  delay(100);
  analogWrite(Buzzer,0);
  delay(300);
  //canneck
  analogWrite(Buzzer,150);
  delay(100);
  analogWrite(Buzzer,0);
  delay(100);
  analogWrite(Buzzer,150);
  delay(100);
  analogWrite(Buzzer,0);
  delay(800);
 /////
    startMeasurementPhase(); //start from measurement
}

void loop() 
{
 

   unsigned long currentMillis = millis();

  int dt = currentMillis - prev_ms;

  if(dt > 100 || dt < 0) 
  {
    prev_ms = currentMillis; //store previous cycle time
    sec10++; //increase 0.1s counter
  }
  if(phase == 1 && sec10 - high_on > 600) //60 seconds of heating ended?
    startMeasurementPhase();
  if(phase == 0 && sec10 - low_on > 900) //90 seconds of measurement ended?
  {
    last_CO_ppm_measurement = raw_value_to_CO_ppm(sens_val);
    startHeatingPhase();
  }

  float v = analogRead(A0); //reading value
  sens_val *= 0.999; //applying exponential averaging using formula
  sens_val += 0.001*v; // average = old_average*a + (1-a)*new_reading
  if(sec10 - last_print > 9) //print measurement result into serial 2 times per second
  {
    last_print = sec10;
    Serial.print("Raw A0 Value:");
    Serial.print(sens_val);
    Serial.print(" V");
    Serial.print(" ");
    Serial.print("Heating on/off (.1=off 1000-on):");
    Serial.print(0.1 + phase*1000);
    Serial.print(" ppm");
    Serial.print(" ");
    Serial.print(last_CO_ppm_measurement);
    Serial.print(" ppm");
    Serial.print("\n");
    Serial.print("Butane:"); 
    Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_Butane) );
    Serial.print( "ppm" );
    Serial.print("    ");   
    Serial.print("Methane:"); 
    Serial.print(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_Methane) );
    Serial.print( "ppm" );
    Serial.print("\n");
  }
  //flash green while good
  if (last_CO_ppm_measurement<COThreshhold && MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_Butane) < ButaneThreshhold && MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_Butane) < ButaneThreshhold)
{
  if(currentMillis-previousMillis1>=1000)
   {
        previousMillis1=currentMillis;
    if(GreenLEDlevel==LOW)
        {
          GreenLEDlevel=HIGH;
        }
        else
        {
          GreenLEDlevel=LOW;
        }
        digitalWrite(GreenLED,GreenLEDlevel);
   }
  digitalWrite(Buzzer,LOW); 
}
//carbon monoxide
        
if(last_CO_ppm_measurement>COThreshhold)//high CO case
{ 
    if(currentMillis-previousMillis2>=200)
      {
        previousMillis2=currentMillis;
        if(Buzzerlevel==5)
        {
          Buzzerlevel=100;
        }
        else
        {
          Buzzerlevel=5;
        }
        analogWrite(Buzzer,Buzzerlevel);
        if(RedLEDlevel==LOW)
        {
          RedLEDlevel=HIGH;
        }
        else
        {
          RedLEDlevel=LOW;
        }
        digitalWrite(RedLED,RedLEDlevel);
        digitalWrite(GreenLED,LOW);
      }

}

///Methane

if(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_Butane) > ButaneThreshhold)
{

    if(currentMillis-previousMillis2>=500)
      {
        previousMillis2=currentMillis;
        if(Buzzerlevel==50)
        {
          Buzzerlevel=100;
        }
        else
        {
          Buzzerlevel=50;
        }
        analogWrite(Buzzer,Buzzerlevel);
        if(RedLEDlevel==LOW)
        {
          RedLEDlevel=HIGH;
        }
        else
        {
          RedLEDlevel=LOW;
        }
        digitalWrite(RedLED,RedLEDlevel);
        digitalWrite(GreenLED,LOW);
      }
}
///Butane

if(MQGetGasPercentage(MQRead(MQ_PIN)/Ro,GAS_Butane) > ButaneThreshhold)
{

    if(currentMillis-previousMillis2>=200)
      {
        previousMillis2=currentMillis;
        if(Buzzerlevel==0)
        {
          Buzzerlevel=100;
        }
        else
        {
          Buzzerlevel=0;
        }
        analogWrite(Buzzer,Buzzerlevel);
        if(RedLEDlevel==LOW)
        {
          RedLEDlevel=HIGH;
        }
        else
        {
          RedLEDlevel=LOW;
        }
        digitalWrite(RedLED,RedLEDlevel);
        digitalWrite(GreenLED,LOW);
      }
}
}
//mq-2 post loop
/****************** MQResistanceCalculation ****************************************/
float MQResistanceCalculation(int raw_adc)
{
  return ( ((float)RL_VALUE*(1023-raw_adc)/raw_adc));
}

/***************************** MQCalibration11 ****************************************/ 
float MQCalibration(int mq_pin)
{
  int i;
  float val=0;

  for (i=0;i<CALIBARAION_SAMPLE_TIMES;i++) {            //take multiple samples
    val += MQResistanceCalculation(analogRead(mq_pin));
    delay(CALIBRATION_SAMPLE_INTERVAL);
  }
  val = val/CALIBARAION_SAMPLE_TIMES;                   //calculate the average value

  val = val/RO_CLEAN_AIR_FACTOR;                        //divided by RO_CLEAN_AIR_FACTOR yields the Ro 
                                                        //according to the chart in the datasheet 

  return val; 
}
/*****************************  MQRead *********************************************/ 
float MQRead(int mq_pin)
{
  int i;
  float rs=0;

  for (i=0;i<READ_SAMPLE_TIMES;i++) {
    rs += MQResistanceCalculation(analogRead(mq_pin));
    
  }

  rs = rs/READ_SAMPLE_TIMES;

  return rs;  
}

/*****************************  MQGetGasPercentage **********************************/ 
int MQGetGasPercentage(float rs_ro_ratio, int gas_id)
{
  if ( gas_id == GAS_Butane ) {
     return MQGetPercentage(rs_ro_ratio,ButaneCurve);
  } else if ( gas_id == GAS_Methane ) {
     return MQGetPercentage(rs_ro_ratio,MethaneCurve);
  }    

  return 0;
}

/*****************************  MQGetPercentage **********************************/ 
int  MQGetPercentage(float rs_ro_ratio, float *pcurve)
{
  return (pow(10,( ((log(rs_ro_ratio)-pcurve[1])/pcurve[2]) + pcurve[0])));
}
