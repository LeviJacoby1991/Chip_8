#include<iostream>
#include<SDL2/SDL.h>
//#include //library for output, input, and sound
#include "chip8.h"

SDL_Window* window;
SDL_Surface* screen;

//Get sdl poll event and check game controlls are press;
void setkeys();
//draw chip8 on screen
void drawChip8();

chip8 emu;
int main(int argc, char **argv){

	bool quit = false;
	//SDL_Event
	//set up screen
	//initialize chip8
	emu.initialize();
	
	//load game
	emu.loadGame("Pong");
	//initialize SDL	
		//if it doesn't initialize throw error
	//else start running screen
	while(!quit){
		//poll sdl event
			//emulate cycle
			emu.emulateCycle();
			// draw if the draw flag is set, updates screen
			if(emu.drawFlag){}
				drawChip8();//drawGraphics();

			//Store key press state (Press and Release)
			setkeys(/*pass in event */);
	}
}

void setkeys(){
	//check sdl poll event for key up or key down
	//if key up set the corresponding key in the chip8 to 0	
	
	//if key down set the corresponding in the chip8 to 1
}
void drawChip8(){
	//go through the chip8s graphics array and draw to the screen if
	//the bit is set
}
