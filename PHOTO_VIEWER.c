/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: Photo Viewer 
	 Name: Imran Warfa
	 ID: 500899229
 * Note(s): 
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2008-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <LPC17xx.H> /* LPC17xx definitions */
#include "PHOTO_VIEWER.h"
#include "GLCD.h"
#include "KBD.h"



extern unsigned char ClockLEDOn;
extern unsigned char ClockLEDOff;
extern unsigned char ClockANI;
extern unsigned int counter;

extern unsigned char blackhole[];     // Black hole Image
extern unsigned char harold[]; 				// Harold Meme
extern unsigned char king[];					// Famous Person Picture



void display_pic(int pic)		//function for displaying image
{
	if (pic==0)
	{
		GLCD_Clear(Blue);
		GLCD_Bitmap(80,60,160,120,blackhole);
		GLCD_DisplayString (9, 1, 1, "PRESS STICK TO EXIT");
	}
	else if (pic==1)
	{
		GLCD_Clear(Blue);
		GLCD_Bitmap(80,60,160,120,harold);
		GLCD_DisplayString (9, 1, 1, "PRESS STICK TO EXIT");
	}
	else if (pic==2)
	{
		GLCD_Clear(Blue);
		GLCD_Bitmap(80,60,160,120,king);
		GLCD_DisplayString (9, 1, 1, "PRESS STICK TO EXIT");
	}
}

void photo_viewer (int mode)
{	
	int pic     =  0;	//variable that saves which picture to display
	int check   =  0;  // Check if user wants to exit 
	int joystick_prev = get_button();
	int joystick_val = get_button();
	display_pic(pic);
	while (check <1)		//if the joystick has been pressed, exit photo viewer
	{	
		joystick_val = get_button();		// read the joystick
		if (joystick_val != joystick_prev)	// user has moved stick
			{
				if (joystick_val == KBD_RIGHT)
					{
							pic = pic+1; //increment pic
							pic = pic%3;	
						  display_pic(pic);	//display whatever image
					}
				else if (joystick_val ==KBD_LEFT)
					{
						pic = pic-1; //decrement pic
						if (pic < 0)
								pic = 2;			
						display_pic(pic);	//display whatever image
					}
				else if (joystick_val ==KBD_SELECT)
				{
					check ++;
				}
			  joystick_prev = joystick_val;
		}
	}
	check = 0;	// before exiting, change the check back to normal so we can run photo viewer again
	GLCD_Clear(White);
	GLCD_DisplayString (0, 0, 1, "COE 718 Project Demo");
	GLCD_DisplayString (1, 6, 1, "MAIN MENU");
}





