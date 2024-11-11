/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: COE 718 Final Project
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
                  
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */
#include "string.h"
#include "GLCD.h"
#include "LED.h"
#include "KBD.h"
#include "PHOTO_VIEWER.h"
#include "usbdmain.h"
#include "snake.h"

extern int audio_main (void);


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) 
{  	/* Main Program                       */
	int select = 0; 							//selector to see what the user is currently choosing
																//'1' for photo viewer, '2' for audio file, '3' for game
	int joystick_val = 0;   			//track the current joystick value
	int joystick_prev = 0;  			//track the previous value for the joystick
	
	KBD_Init();
  GLCD_Init();

  GLCD_Clear  (Navy); 					// Setting up background screen
  SysTick_Config(SystemCoreClock/100); 
	GLCD_SetBackColor(Navy);
  GLCD_SetTextColor(Yellow);
	GLCD_DisplayString (0, 0, 1, "COE 718 Project Demo");
	GLCD_DisplayString (5, 8, 1, "MENU");

  while(1)		// Program will loop forever and refresh the screen
	{
			joystick_val = get_button();	// read the joystick
			
			if (joystick_val !=joystick_prev)	// user has moved the joystick
			  {
					if (joystick_val == KBD_LEFT)
						{ //Photo
							select = 1;	// user has picked photos
						}
					else if (joystick_val == KBD_RIGHT)
						{ //Audio
							select = 2; // user has picked audio
						}
					else if (joystick_val == KBD_DOWN) {
							// Game
							select = 3; // user has picked snake game
					}
					else if(joystick_val == KBD_SELECT)
							{
								if (select == 1)
								{
									photo_viewer(1);	// start photo viewer 
									select = 0;      	// clear the screen
									GLCD_Clear(Navy); 
									GLCD_SetBackColor(Navy);
									GLCD_SetTextColor(Yellow);
									GLCD_DisplayString (0, 0, 1, "COE 718 Project Demo");
									GLCD_DisplayString (5, 8, 1, "MENU");
									select = 0;
								}
								else if (select == 2)
								{
									audio_main(); // start the audio player
									//delay(10);
									GLCD_Clear(Navy);
									GLCD_SetBackColor(Navy);
									GLCD_SetTextColor(Yellow);
									GLCD_DisplayString (0, 0, 1, "COE 718 Project Demo");
									GLCD_DisplayString (5, 8, 1, "MENU");									
									select =0; // refresh selector option
								}
								else if(select ==3)
								{
									//GLCD_Clear(Navy);
									snakegame(); // start the snake game
									GLCD_Clear(Navy);
									GLCD_SetBackColor(Navy);
									GLCD_SetTextColor(Yellow);
									GLCD_DisplayString (0, 0, 1, "COE 718 Project Demo");
									GLCD_DisplayString (5, 8, 1, "MENU");
									select = 0; // refresh the selector option
								}
							}
					joystick_prev = joystick_val;	// 
			}
			
			/*this is to update the LCD each time the user interfaces with the joystick*/
			if (select == 1)	//for displaying now
				{
						GLCD_SetBackColor(Green);                  // Refresh screen if user has moved joystick + make selector option hover over photo
						GLCD_SetTextColor(Yellow);									
						GLCD_DisplayString(5,0,1, "Photo");
						GLCD_SetBackColor(Navy);
						GLCD_SetTextColor(Yellow);
						GLCD_DisplayString(5,15,1, "Audio");
						GLCD_SetBackColor(Navy);
						GLCD_SetTextColor(Yellow);
						GLCD_DisplayString(9,8,1, "Snake");
						
				}
			else if(select == 2)
				{
						GLCD_SetBackColor(Navy);										 // Refresh screen if user has moved joystick
						GLCD_SetTextColor(Yellow);
						GLCD_DisplayString(5,0,1, "Photo");
						GLCD_SetBackColor(Green);											// Make selector option hover over audio
						GLCD_SetTextColor(Yellow);
						GLCD_DisplayString(5,15,1, "Audio");
						GLCD_SetBackColor(Navy);	
						GLCD_SetTextColor(Yellow);
						GLCD_DisplayString(9,8,1, "Snake");
				}
			else if(select == 3)
				{
						GLCD_SetBackColor(Navy);											 // Refresh screen if user has moved joystick
						GLCD_SetTextColor(Yellow);
						GLCD_DisplayString(5,0,1, "Photo");
						GLCD_DisplayString(5,15,1, "Audio");
						GLCD_SetBackColor(Navy);
						GLCD_SetTextColor(Yellow);
						GLCD_SetBackColor(Green);												// Make selector option hover over snake
						GLCD_SetTextColor(Yellow);
						GLCD_DisplayString(9,8,1, "Snake");
				}
			else
				{
						GLCD_SetBackColor(Navy);												 // Refresh screen if user has moved joystick
						GLCD_SetTextColor(Yellow);
						GLCD_DisplayString(5,0,1, "Photo");
						GLCD_DisplayString(5,15,1, "Audio");
						GLCD_DisplayString(9,8,1, "Snake");
				}
			} 

}

