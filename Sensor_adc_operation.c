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
   ADCSRA|=0x40;  // ���� ���� �Է� ��� ��ȯ ���� 

  // Wait for the AD conversion to complete
  while ((ADCSRA & 0x10)==0);

  ADCSRA|=0x10;
  
  return ADCW;
}

void Read_ADC_Operation(void)
{     
     //-------------adc2 : �������� --------------//
      voltage = read_adc(2);
      delay_ms(5);   
      voltage = voltage * 0.0048828;  // ���� ���� 5v�� 1024����,10����

     //-------------adc1 : �µ����� --------------//
      fTemp = read_adc(0) * fTSlop;               
      delay_ms(5);
       
      //-------------adc0 : �������� --------------//
      Gas = read_adc(1);      
      delay_ms(5);
}