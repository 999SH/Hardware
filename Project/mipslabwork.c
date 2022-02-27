/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2022-02-26 by Aayush Gupta and Viktor Salomonsson 

   For copyright and licensing, see file COPYING 
*/


#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declarations for these labs */

int mytime = 0x0000; // The starting time, needs to be 1 so ticks == leds

char textstring[] = "text, more text, and even more text!";


int timeoutcount = 0;

// We need to declare the pointers as volatile because we want to avoid
// unintentional compiler optimization that could render the pointers static
volatile int *tris_E;
volatile int *port_E;



/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

void labinit( void )
{
  // Cast their respective adress as they were declared as volatile
  // TRISE contains the bits that determine if Port bits are input or output
  // PORTE contains the data that decideds what input/output
  tris_E = (volatile int*) 0xbf886100; // Address of TRISE register
  port_E = (volatile int*) 0xbf886110; // Address of PORTE register


  *tris_E = *tris_E & 0xffffff00; // To mask out the 8 LSBs

  *port_E = 0x00000000; // Set PORTE to 0 so we can see the ticks better

  // e)
  TRISD = TRISD | 0x0fe0; // OR to keep values at 11-5 bits

  T2CON = 0x0000;          // Stop the clock 
  T2CONSET = 0x70;         // Set 0111 0000 = 1:256 prescaling
  TMR2 = 0x0;              // Set time register to 0; 
  PR2 = (80000000/256)/10; // 31 250 = 

  T2CONSET = 0x8000; // Bit 15 decides if the timer is on or off

  return;
}


void labwork( void )
{
  //
  int switches = getsw();
	int buttons = getbtns();

  // The buttons need to have following if conditions since we want to be able
  // to press several buttons at the same time. For example: Button 2 and 4
  // would be 101 (5), and so we declare that 5 is a condition for both buttons
  // since the code executes each button if-statement.

  // Button 2 (001)
  if(buttons & 1){
    // Mask out the bits that represent 10th seconds
    mytime = mytime & 0xff0f;
    // Take the value from switches, shift to correct position then add (OR) them
    // to mytime.
    mytime = (switches << 4) | mytime;
  }

  // Button 3 (010)
  if(buttons & 2){
    mytime = mytime & 0xf0ff;
    mytime = (switches << 8) | mytime;

  }

  // Button 4 (100)
  if(buttons & 4){
    mytime = mytime & 0x0fff;
    mytime = (switches << 12) | mytime;

  }

if(IFS(0) & 0x100){       //if flag is triggered, I.e If bit 8 is 1. 
	timeoutcount++;
	IFSCLR(0) = 0x100; // Clear the flag this is done by setting bit 8 to 1.



if (timeoutcount == 10){

 // delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);
  timeoutcount = 0; //Set counter to 0 again
}
  *port_E = *port_E + 0x00000001; // d) Increment the value per tick
	}
}
