#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>

void serial_begin();
unsigned char serial_read_char();
void serial_print_char(unsigned char caracter);
void serial_print_str(char* cadena);
void iniciarADC();
char intToChar(int numero);
void ADC_init();

int ADCGet(int canal);


void PWM_init();