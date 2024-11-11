#include "stdio.h"
#include "stdlib.h"
#include "LPC17xx.h"
#include "KBD.h"
#include "GLCD.h"


#define DELAY_2N 20

int x_position; //horizontal position
int y_position; //vertical position
int size; //size of the body
int head = 0; //current headion
int prev_head = 0; //previous headion
int joystick_val = 0; //current joystick val
int joystick_prev_val = KBD_RIGHT; //previous joystick val
int snake[50][2]; //snake coordinates.
int x_food, y_food; //food coordinates
int collision = 0;
int score = 0;
char text[20];

void food(){  // Food Function
	// Set up food location
	int i;
	x_food = rand()%7;  // randomize food x coordinate
	y_food = rand()%15;	// randomize food y coordinate
	for(i=0;i<size;i++){
		if(x_food == snake[i][0])
			if(y_food == snake[i][1])
				// if food location matches snake coordinates, create more food
				food();  
	}
	GLCD_DisplayChar(x_food,y_food,1,0x81);  // display food as a solid circle
}
// delay function
void delay (int count){
	count <<= DELAY_2N;			
	while(count--);
}

void setbody(){
	int i; //counting
	
	for(i=0;i<size;i++){
		switch(head){
			case 0://right
				snake[i][0] = x_position;
				snake[i][1] = y_position-i;
				break;
			case 1://left
				snake[i][0] = x_position;
				snake[i][1] = y_position+i;
				break;
			case 2://down
				snake[i][0] = x_position+i;
				snake[i][1] = y_position;
				break;
			case 3://up
				snake[i][0] = x_position-1;
				snake[i][1] = y_position;
				break;
		}
	}
}
// increase size of body after eating food
// increase score by 1
void addbody(){
	size++;
	score = score + 1;
}
// check if food has been eaten
// check if snake has collided 
void check(){
	int i;
	
	//food check
	if(x_food == snake[0][0])
		if(y_food == snake[0][1]){
			addbody();
			food();
		}
		
	//tail collision check
	for(i=1;i<size;i++){
		if(snake[0][0] == snake[i][0])
			if(snake[0][1] == snake[i][1])
				collision = 1;
	}
	
}

void updatebody(){
	int i;
	if(head == 0){//move right
		// update back of snake towards the front
		for(i=size;i>0;i--){
			if(i==1){
				snake[0][1] = y_position;  
				snake[0][0] = x_position;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}		
		// display snake
		for(i=1;i<size;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x8B);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x8C);
		}
		delay(5);
	}else if(head == 1){//move left
			// update back of snake towards the front
		for(i=size;i>0;i--){
			if(i==1){
				snake[0][1] = y_position;
				snake[0][0] = x_position;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		// display snake
		for(i=1;i<size;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x89);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x8C);
		}
		delay(5);
	}else if(head == 2){//move down
			// update back of snake towards the front
		for(i=size;i>0;i--){
			if(i==1){
				snake[0][1] = y_position;
				snake[0][0] = x_position;				
			}else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		// display snake
		for(i=1;i<size;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x87);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x8C);
		}
		delay(5);
	}else if(head == 3){//move up
			// update back of snake towards the front
		for(i=size;i>0;i--){
			if(i==1){
				snake[0][1] = y_position;
				snake[0][0] = x_position;				
			}
		else{
				GLCD_DisplayChar(snake[i-1][0],snake[i-1][1],1,' ');
				snake[i-1][1] = snake[i-2][1];
				snake[i-1][0] = snake[i-2][0];
			}
		}
		// display the snake
		for(i=1;i<size;i++){
			GLCD_DisplayChar(snake[0][0],snake[0][1],1,0x85);
			GLCD_DisplayChar(snake[i][0],snake[i][1],1,0x8C);
		}
		delay(5);
	} 
	// check for collision or food
	check();
}

void direct(int stick){
	// change direction of snake according to joystick input 
	switch(stick){
		case KBD_UP:
			// must pick direction adjacent to current direction
			if (joystick_prev_val == KBD_LEFT || joystick_prev_val == KBD_RIGHT){
				x_position--;
				// if you reach a border, appear on the other side
				if (x_position == 0){
					x_position = 9;
				}
				head = 3;
				prev_head = head;
				joystick_prev_val = joystick_val;
				updatebody();
			}
			break;
		case KBD_DOWN:
			// must pick direction adjacent to current direction
			if (joystick_prev_val == KBD_LEFT || joystick_prev_val == KBD_RIGHT){
				x_position++;
				// if you reach a border, appear on the other side
				if (x_position == 9){
					x_position = 0;
				}
				head = 2;
				prev_head = head;
				joystick_prev_val = joystick_val;
				updatebody();
			}
			break;
		case KBD_LEFT:
			// must pick direction adjacent to current direction
			if (joystick_prev_val == KBD_UP || joystick_prev_val == KBD_DOWN){
				y_position--;
				// if you reach a border, appear on the other side
				if (y_position == 0){
					y_position = 20;
				}
				head = 1;
				prev_head = head;
				joystick_prev_val = joystick_val;
				updatebody();
			}
			break;
		case KBD_RIGHT:
			// must pick direction adjacent to current direction
			if (joystick_prev_val == KBD_UP || joystick_prev_val == KBD_DOWN){
				y_position++;
				// if you reach a border, appear on the other side
				if (y_position == 20 ){
					y_position = 0;
				}
				head = 0;
				prev_head = head;
				joystick_prev_val = joystick_val;
				updatebody();
			}
			break;
		default:
			switch(head){
				case 0://right
					y_position++;
				// if you reach a border, appear on the other side
					if (y_position > 20){
						y_position = 0;
					}
					updatebody();
					check();
					break;
				case 1://left
					y_position--;
				// if you reach a border, appear on the other side
					if (y_position < 0){
						y_position = 20;
					}
					updatebody();
					check();
					break;
				case 2://down
					x_position++;
				// if you reach a border, appear on the other side
					if (x_position > 9){
						x_position = 0;
					}
					updatebody();
					check();
					break;
				case 3://up
					x_position--;
				// if you reach a border, appear on the other side
					if (x_position < 0){
						x_position = 9;
					}
					updatebody();
					check();
					break;
			}
			break;
	}	
}

void clearsnake(){
	int i;
	for(i=0;i<size;i++){
		snake[i][0]=1;
		snake[i][1]=1;
	}
}

int snakegame(){
	int check=0;
	GLCD_Init();
	KBD_Init();

	while(!check){
		// set up initial conditions
		head = 0;
		prev_head = 0;
		joystick_val = 0;
		joystick_prev_val = KBD_RIGHT;
		size = 3;
		x_position = 2;
		y_position = 8;
		// set up LCD Screen
		GLCD_Clear(DarkGreen);
		GLCD_SetBackColor(DarkGreen);
		GLCD_SetTextColor(Yellow);
		setbody();
		food();	// create food
		while(collision == 0){
			// check for input from user
			joystick_val = get_button();
			direct(joystick_val); // change direction
			sprintf(text,"     Current Score is: [%d]",score);  // print score
			GLCD_DisplayString(0,9,0,(unsigned char *)text);	
		}
		if(collision == 1){		// if collision occurs, print game over message + score
			GLCD_Clear(DarkGreen);
			GLCD_SetBackColor(DarkGreen);
			GLCD_DisplayString (4, 1, 1, "Thanks for playing!");
			sprintf(text,"     Final Score is: [%d]",score);
			GLCD_DisplayString(0,9,0,(unsigned char *)text);	
			delay(100); // delay 
			check = 1;
			clearsnake();
			collision = 0; // must clear collision to ensure snake game operates accordingly after running once
			return 0;	
			}
	}
}