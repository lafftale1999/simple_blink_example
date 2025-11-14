#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Library for time related operations - for example delays
#include "include/millis.h"

#define LED_PIN PB5

int main(void) {
    
    // SETUP
    millis_init();
    sei(); // <- Enable global interrupts

    // LED
    DDRB |= (1 << LED_PIN);
    
    PORTB &= ~(1 << LED_PIN);

    // SUPER-LOOP
    while(1) {
        
        PORTB ^= (1 << LED_PIN);

        millis_wait_ms(1000);
    }
}