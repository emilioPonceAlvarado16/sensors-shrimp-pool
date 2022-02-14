#include <stdlib.h> 
#include <stdio.h>
#include <math.h> 
#include <avr/io.h>
#include <util/delay.h> 
#include  "uart.h"


void serial_begin(){
    UCSR0B=0b00011000;//transmisión habilitados a 8 bits
    UCSR0C=0b00000110;//asíncrono, sin bit de paridad, 1 bit de parada a 8 bits
    UBRR0=51;    //para una velocidad de 9600 baudios con un oscilador de 8Mhz
}
unsigned char serial_read_char(){
    if(UCSR0A&(1<<7)){  
     return UDR0;  
    }
    else
    return 0;
}
void serial_print_char(unsigned char caracter){
    while(!(UCSR0A&(1<<5)));    // mientras el registro UDR0 esté lleno espera
    UDR0 = caracter;            //cuando el el registro UDR0 está vacio se envia el caracter
}
void serial_print_str(char* cadena){     
    while(*cadena !=0x00){    
        serial_print_char(*cadena);    
        cadena++;    

     }
}

void ADC_init(){
   
   ADMUX&=~(1<<ADLAR); //Output ajust=right
   
   //Voltage reference = AVCC
   ADMUX |=(1<<REFS0);
   ADMUX &=~(1<<REFS1);
   
   //Frecuency divisor=128-> 16000/128=125Khz
   
   ADCSRA |=(1<<ADPS0);
   ADCSRA |=(1<<ADPS1);
   ADCSRA |=(1<<ADPS2);
   
   
   }
   
int ADCGet(int canal){
   
   //	Selección del canal de 1 ADC
   
   ADMUX &=~0X0F;
   ADMUX |=canal;
   
   //Encendemos el ADC
  ADCSRA  |=(1<<ADEN);
   
   _delay_us(10);//Esperamos a que caliente
 
   //Se manda el muestreo
   
   ADCSRA  |=(1<<ADSC);
   
   //Esperamos a que muestree, leyendo el flag
   
   while( ! ( ADCSRA &(1<<ADIF) ) );
      
      ADCSRA  |=(1<<ADIF); //Reiniciamos el flag
   
   //apagamos el ADC
   ADCSRA  &= ~ (1<<ADEN);
   return ADC;
   

   
   }
   

   
//funcion de inicio del ADC
void iniciarADC(){
   
   ADMUX = 0B01000001; 
   ADCSRA = 0B00000101; 
   ADCSRB = 0B00000000; 
   DIDR0 = 0B00000110; 
}
   
 
 char intToChar(int numero){
    return numero + '0';
}


   
   
   //PWM 
   
   
   void PWM_init(){
   
   DDRD |= 0b01100000;
   TCCR0A = 0b11100011; 
   TCCR0B = 0b00000001;
   OCR0A = 0; //valor inicial de pwm para el pin OC0A
   OCR0B = 0; //valor inicial de pwm para el pin OC0Bs
   
   
   
   }
