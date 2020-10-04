

#include <io.h>
#include <mega32.h>
#include <alcd.h>
#include <stdlib.h>

int number = 0;

void main(void)
{
    

    lcd_init(16);
    lcd_clear();                                    // lcd initial settings
   
    
    OCR1AH = 0x3D;
    OCR1AL = 0x09;                                  // OCR1A = ox3D09 = 15625 --> 15625 * 64 / 1000000 = 1 second 
    
    #asm("sei");                                    // globally enable interrupts
    TIMSK |= (1 << TOIE1) | (1 << OCIE1A) ;         // enable timer/counter 1 interrupt and timer/counter 1 compare match interrupt  
    
    TCCR1B = 0x0B;                                  // f(t/c) = f(IO) / 64 from prescaler || enable CTC mode and set TOP to OCR1A value
    
   
                                      
    
    
}


interrupt[TIM1_COMPA] void comparematch(void){     // interrupt happens every second
    
    
    char number_string[10];
    
    itoa(number,number_string);                     // convert integer(number) to string(number_string)
    
    lcd_clear();
    lcd_puts(number_string);
    
    number = (number + 1) % 1001;
     
}



