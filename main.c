/* code template for CME331 Lab 2 (2018-19) - using LaunchPad, LM4F120
Khan Wahid, Sept 18, 2018
using quad 7-segment and switches, simple display
*/

// Display connected to PB0-PB7, 8-bits, Latch enable to PA4-PA7
// see schematics: https://www.engr.usask.ca/classes/CME/331/WebNotes_2014/Drawing_dev_board.jpg
// Uses SW1 (connected to pin PF4)

#include "Systick_16.h"  // Include to use Systick timer, p.118
#include "tm4c123gh6pm.h"
#include "led/led.h"
//**********************************Mapping registers************************************
// p.424, clock gating for GPIO
#define SYSCTL_RCGC2            (*((volatile unsigned long *)0x400FE108))

#define GPIO_LOCK_KEY           0x4C4F434B  // p. 637, unlocks the GPIO_CR register

//declare functions
void init_gpio (void);
void wait_for_sw1 (void);
void display_uofs (void);
void display_num (void);
void delay (void);


// Look-up table (LUT) for 7-segment, ***active low***
// This LUT effectively becomes the driver for the 7-segment display
// PortB pins       :       7-6-5-4-3-2-1-0
// led segments :   1-e-d-c-b-a-f-g

const char lut_uofs [4] =   {
                                                                0x85,  // U  10000101 (lut entry 0 <=> lut_uofs [0])
                                                                0x81,  // O  10000001 (lut entry 1)
                                                                0xB8,  // F  10111000 (lut entry 2)
                                                                0xC8,  // S  11001000 (lut entry 3)
                                                                };

// add lut_num for "1234" below




//  initialize ports
void init_gpio (void) {
    volatile unsigned long delay_clk; // delay for clock, must have 3 sys clock delay, p.424
    SYSCTL_RCGC2 |= 0x23;             ; // find value for clock gating enable for ports A, B, F, p.424
    delay_clk = SYSCTL_RCGC2; // just a delay for the clock to settle, no-operation

    // the following two lines are needed to unlock SW2
    GPIO_PORTF_LOCK  |= 0x4C4F434B; // to unlock SW2, p.637-8
    GPIO_PORTF_CR |= 0x01; // to unlock SW2

    // add more initialization code here for PortF and other ports...
    //B and A are outputs, F is input
    // A,B,F are digital
    //AFSel off for a,b,f
    //Shouldnt need to change pctl double check though
    GPIO_PORTF_DIR |= 0xE;     //On reset all set to zero 0 is in 1 is out

    GPIO_PORTF_AFSEL &= ~0x1F;   //on reset no default set to zero
    GPIO_PORTF_DEN |= 0x1F;      //on reset no default set to 1 for digital enable
    GPIO_PORTF_PCTL &= ~0x1F;    //on reset no default set to zero
//    GPIO_PORTF_PUR |= 0x1F;      //on reset no default set to 1 for digital enable


}

// other functions
// displays UOFS on display board
void display_uofs (void) {
    GPIO_PORTB_DATA = 0xFF; // turns off all 7-segment, LED
    // Note: you may also use GPIO_PORTB_DATA |= 0xFF; but here "=" is preferred over "|="...
    // ...because you will be using the entire portB (all 8-bits) to update the data value...
    // ...so there is no risk of changing other pins unintentionally when "=" is used
    GPIO_PORTA_DATA |= 0xF0; // latch enable for all 4 displays, make PA4-PA7 high
    GPIO_PORTA_DATA &= ~0xF0; // latch disable for all 4 displays, make PA4-PA7 low
    delay (); // good to add some delay

    GPIO_PORTB_DATA = lut_uofs [0]; // it will write lut entry 0 to Port B so 'U' is displayed...
    // ...for the same reason as above "=" is used instead of "|="
    GPIO_PORTA_DATA |= 0x10; // make PA4 (LE0) high to write to display0
    GPIO_PORTA_DATA &= ~0x10; // make PA4 low so that no change on display0

// complete the rest...

}



// displays static number on display board
void display_num (void) {
// add your code...


}


// this is polling SW 1
void wait_for_sw1 (void) {
// add your code here...


}


void delay (void) {
    long unsigned i;
    for (i = 0; i < 1000000; i++);

}

int main (void) {
    init_led ();

    while (1) {
        //display_uofs ();
        red_on();
        // add more lines as needed...

        }
}
