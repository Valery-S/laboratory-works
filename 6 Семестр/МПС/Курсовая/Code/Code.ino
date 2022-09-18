#include <LiquidCrystal.h> 
LiquidCrystal LCD( 12, 11, 3, 2,1 ,0 ); 

int Multiplexer_A = 6;
int Multiplexer_B = 5;  
int Multiplexer_C = 4; 


float r2=10000.0;
float r3=10000.0;
float r4=25000.0;
float r5=1315.0;
float r6=50000.0;
float r7=1020.0;

float tv,rv;
int k;
float read_A0_adc(){
  int adc_voltage=analogRead(A0); 
  float tmp_voltage=(adc_voltage/1023.0)*5.0;
  return tmp_voltage;  
}
float real_voltage_calculation(int chanel,float tmp_voltage){
  float R_f,R_s,real_voltage;
  if(chanel==3){R_f=r6; R_s=r7;}
  if(chanel==2){R_f=r4; R_s=r5;}
  if(chanel==1){R_f=r2; R_s=r3;}
  real_voltage=tmp_voltage*(R_f+R_s)/R_s;
  return real_voltage;
}

void setup() {
  LCD.begin(16,2);
  pinMode(A0,INPUT);
  pinMode(Multiplexer_A,OUTPUT);
  pinMode(Multiplexer_B,OUTPUT);
  pinMode(Multiplexer_C,OUTPUT);
}

void loop() {
  digitalWrite(Multiplexer_A, HIGH); 
  digitalWrite(Multiplexer_B, HIGH); 
  digitalWrite(Multiplexer_C, LOW); 
  
  tv=read_A0_adc();
  rv=real_voltage_calculation(3,tv);
  k=50;
  
  if(rv<100){
      digitalWrite(Multiplexer_A, LOW);
      tv=read_A0_adc();
      rv=real_voltage_calculation(2,tv); 
      k=25;
      if (rv<10){
         digitalWrite(Multiplexer_A, HIGH); 
         digitalWrite(Multiplexer_B, LOW);
          tv=read_A0_adc();
          rv=real_voltage_calculation(1,tv); 
          k=2;
          if(rv<5){
            digitalWrite(Multiplexer_A, LOW);
            tv=read_A0_adc();
            rv=tv;
            k=1;
          }
      }
  }
  LCD.setCursor(0,0);
  LCD.print("                            ");
  LCD.setCursor(0,0);
  LCD.print(rv);
  LCD.setCursor(0,1);
  LCD.print("Divider k=");
  LCD.print(k);
  delay(300);
}
