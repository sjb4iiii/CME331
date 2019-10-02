// CME331
// Modified SystTick.c that uses default 16MHz clock, systick interrupt disabled
// No need to include PLL
// Original code from http://users.ece.utexas.edu/~valvano/arm

#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010)) // p.133, SysTick control and status
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014)) // p.135, 24-bit start value of SysTick
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018)) // p.136, 24-bit current value of SysTick

// Initialize SysTick with busy wait running at bus clock.
void Systick_Init(void)
{

  NVIC_ST_CTRL_R = 0x00;                                        // p. 133 disable SysTick during setup
    NVIC_ST_RELOAD_R = 16000000-1;                          // p.135, clock is 16MHz, Maximum is 0x00FFFFFF = 16,777,215 (dec)
    NVIC_ST_CURRENT_R = 0;                          // any write to current clears it
  NVIC_ST_CTRL_R |= 0x05;                           //  p. 133 enable SysTick , system clock as clock source, disable sysTick interrupt
 }


// Time delay using busy wait.
// The delay parameter is in units of the core clock. (units of 62.5 nsec for 16 MHz clock)
// 1 Systick is equal to 62.5nS
void Systick_Wait(unsigned long delay){
  volatile unsigned long elapsedTime;
  unsigned long startTime = NVIC_ST_CURRENT_R;
  do{
    elapsedTime = (startTime-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(elapsedTime <= delay);
}
// Time delay using busy wait.
// This assumes 16 MHz system clock.
void Systick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    Systick_Wait(160000);  // wait 10ms (assumes 16 MHz clock), 1 Systick is equal to 62.5nS, so to get 10ms, we need ( 1/62.5nS)*10mS =160000
  }
}
// Time delay using busy wait.
// This assumes 16 MHz system clock.
void Systick_Wait1ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    Systick_Wait(16000);   // wait 1ms (assumes 16 MHz clock) 1 Systick is equal to 62.5nS, so to get 1ms, we need ( 1/62.5nS)*1mS =16000
  }
}
