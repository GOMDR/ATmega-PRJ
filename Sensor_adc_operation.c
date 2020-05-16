#include <mega128.h>
#include <delay.h>
#include "Sensor_adc_operation.h"


#define ADC_VREF_TYPE 0x00

unsigned int voltage = 0;
unsigned int Gas = 0;
float fTemp = 0.0; 
float fTSlop = (50.0/1024.0);

void Init_ADC (void)
{  
  // Clock tlequency: 125.000 kHz, VOltage Rerence: AREF pin
   ADMUX=ADC_VREF_TYPE;  
   ADCSRA=0x84;
   
   ACSR=0x80;
   SFIOR=0x00;   
}

// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
   ADMUX=adc_input|ADC_VREF_TYPE;
   // Start the AD conversion
   ADCSRA|=0x40;  // 단일 전압 입력 모드 변환 시작 

  // Wait for the AD conversion to complete
  while ((ADCSRA & 0x10)==0);

  ADCSRA|=0x10;
  
  return ADCW;
}

void Read_ADC_Operation(void)
{     
     //-------------adc2 : 가변전압 --------------//
      voltage = read_adc(2);
      delay_ms(5);   
      voltage = voltage * 0.0048828;  // 참조 전압 5v를 1024분해,10배율

     //-------------adc1 : 온도센서 --------------//
      fTemp = read_adc(0) * fTSlop;               
      delay_ms(5);
       
      //-------------adc0 : 가스센서 --------------//
      Gas = read_adc(1);      
      delay_ms(5);
}