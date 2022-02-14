#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#define VARI 19

 //void avanzar1();
 //void avanzar2() ;
 float volts_2_ph(float voltaje);
 volatile float ph=0.0;
unsigned int voltaje1=0;
volatile float valor_real=0.0;
char buf[5]={0};
int leer();
char intToChar(int numero);
 int diferente=0;
void avanzar2() ;
void avanzar1() ;
 float temp=0;
char buf2[5]={0};

unsigned int voltaje2=0;
volatile float valor_real2=0.0;
int leer2();
float temp2=0;
int diferente2=0;
/*
 ISR(TIMER0_OVF_vect){
 PORTB |= (1<<PB0); //encender bit 0 del puerto B
_delay_ms(500);
PORTB &= ~(1<<PB0); //apagar bit 0 del puerto B
_delay_ms(500);
   TCNT0 = VARI;      
   }*/
int main()

{
   serial_begin();
 /*
  cli();
    
   TCCR0B = 0b00000101;  
   TIMSK0 = 0b00000001;

 
   sei();*/
   
 DDRD |= 0b01100000; //Salidas para los pwms
 DDRB |=0b00000011;  //Salidas para los leds
TCCR0A = 0b11110011;
TCCR0B = 0b00000011;
OCR0A = 0; //valor inicial de pwm para el pin OC0A
OCR0B = 0; //valor inicial de pwm para el pin OC0B
 

 DDRB |= ((1<<0)|(1<<1));
ADC_init();




while(1){

   diferente=leer();

   
   if(diferente){
      serial_print_str(buf);
      serial_print_str("\r\n");
      }
      diferente2=leer2();
    if(diferente2){
     serial_print_str(buf2);
      serial_print_str("\r\n");
      }
   
   
}
 return 0;
}
int leer(){
   
     temp=valor_real;

      voltaje1=ADCGet(1);//ph
   
      valor_real=voltaje1*5.0/1023;
   
   /*
   
   *** valor aceptable del ph en una piscina camaronera es de 6.5 a 9 ***
   
   Fuente: https://www.awamantenimiento.com/cual-es-nivel-ph-piscina/#:~:text=El%20pH%20siempre%20debe%20estar%20entre%207.2%20y%207.6&text=Si%20el%20nivel%20de%20pH,%2C4%20a%207%2C6.
   
   */
      ph=volts_2_ph(valor_real);
   
   if(ph<6.5 || ph>9){
      if(ph<6.5){//pH bajo para los camarones, entonces aumentar pH
	 TCCR0A  &=~(1<<5); 
	   TCCR0A  &=~(1<<4); 
	    PORTD&= ~(1<<PD5);  //El de disminuir pH: OFF
	    PORTB&= ~(1<<PB1);  //El de disminuir pH: OFF
	//PB1 LED DE DISMINUIR   PD5
	 //PB0 LED DE AUMENTAR PD6
	
	TCCR0A  |=(1<<6); 
	    TCCR0A  |=(1<<7); 
	 PORTD |= (1<<PD6);//El de aumentar pH: ON
	  _delay_ms(20);
	    PORTB|= (1<<PB0);  //El de disminuir pH: OFF
	 
	 }else if(ph>9){//pH muy alto para los camarones, entonces disminuir pH
	      TCCR0A  |=(1<<5); 
	    TCCR0A  |=(1<<4); 
	   PORTD |= (1<<PD5); //Diminuyendo pH: ON
	   	  _delay_ms(20);
	       PORTB|= (1<<PB1);  //El de disminuir pH: ON

	    TCCR0A  &=~(1<<6); 
	   TCCR0A  &=~(1<<7); 
	    PORTD&= ~(1<<PD6);  //El de aumentar pH: OFF
    
	   //    PORTB&= ~(1<<PB1);  //El de disminuir pH: OFF
	       PORTB&= ~(1<<PB0);  //El de disminuir pH: OFF
	    }
      
      
      }else{
	    TCCR0A  &=~(1<<6); 
	   TCCR0A  &=~(1<<7); 
	    PORTD&= ~(1<<PD6);  //El de aumentar pH: OFF
	 	 TCCR0A  &=~(1<<5); 
	   TCCR0A  &=~(1<<4); 
	    PORTD&= ~(1<<PD5);  //El de disminuir pH: OFF
	 
	 
	       PORTB&= ~(1<<PB1);  //El de disminuir pH: OFF
	       PORTB&= ~(1<<PB0);  //El de disminuir pH: OFF
	 }
    
       
   
      //float_2_string(ph,buf);
     // float_2_string(valor_real,buf);
     if(ph>=10){
	 dtostrf(ph, 5,2,buf);
	}else{
	   dtostrf(ph, 4,2,buf);
	   }
     
      if(temp!=valor_real){
	
	 
	 return 1;}

    return 0;
     

   }
   
   
int leer2(){

    temp2=valor_real2;
    voltaje2=ADCGet(2);
    valor_real2=voltaje2*5.0*100/1023;
     
       
   dtostrf(valor_real2, 4,2,buf2);
     if(temp2!=valor_real2){
	
	 
	 return 1;}
   
   
   return 0;
   }    
 
float volts_2_ph(float voltaje){
   
   float ph=voltaje/0.357;
   return ph;
   }