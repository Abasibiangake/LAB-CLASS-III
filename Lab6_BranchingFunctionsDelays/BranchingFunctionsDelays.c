// BranchingFunctionsDelays.c Lab 6
// Runs on LM4F120/TM4C123
// Use simple programming structures in C to 
// toggle an LED while a button is pressed and 
// turn the LED on when the button is released.  
// This lab will use the hardware already built into the LaunchPad.
// Daniel Valvano, Jonathan Valvano
// January 8, 2014

// built-in connection: PF0 connected to negative logic momentary switch, SW2
// built-in connection: PF1 connected to red LED
// built-in connection: PF2 connected to blue LED
// built-in connection: PF3 connected to green LED
// built-in connection: PF4 connected to negative logic momentary switch, SW1

//#include "TExaS.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC2_GPIOF      0x00000020  // port F Clock Gating Control
unsigned long In;
unsigned long S;
unsigned long O;

// basic functions defined at end of startup.s
//void DisableInterrupts(void); // Disable interrupts
//void EnableInterrupts(void);  // Enable interrupts
void Delay(void) {unsigned long volatile time;
	time = 727240*200/91;
	while(time){
		time--;
	}
}

int main(void){ unsigned long volatile delay;
//  TExaS_Init(SW_PIN_PF4, LED_PIN_PF2);  // activate grader and set system clock to 80 MHz
  // initialization goes here
	SYSCTL_RCGC2_R |= 0x00000020; // activate the clock for port F
	GPIO_PORTF_AMSEL_R = 0x00;           // 3) disable analog on PF but for P4 and P2 = 0x0B
	GPIO_PORTF_PCTL_R = 0x00000000;       // 4) PCTL GPIO on PF4-0 but for judt P4 and P2 = FFF0F0FF
	GPIO_PORTF_DIR_R = 0x0E;          // PF4,PF0 in, PF3-1 out
	GPIO_PORTF_AFSEL_R = 0x00;        // disable alt funct on PF7-0
	GPIO_PORTF_DEN_R = 0x13;          // enable digital I/O on PF4 and PF2
	GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
	GPIO_PORTF_DATA_R |= 0x04;        // eset PF2 in port F, and led initially ON

  //EnableInterrupts();           // enable interrupts for the grader
  while(1){
    // body goes here
		Delay();
		In = GPIO_PORTF_DATA_R&0x11;
		if (In == 0x00) {
			GPIO_PORTF_DATA_R ^= 0x04;
		}
		else // 0x10 means switch not pressed
		{
			GPIO_PORTF_DATA_R = 0x04;
		}
		
  }
}
