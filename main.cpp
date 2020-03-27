#include<iostream>
//#include //library for output, input, and sound
#include "chip8.h"

chip8 emu;
int main(int argc, char **argv){
	std::cout<<"Hello World\n";
	//set up graphics
	
	//set up screen
	
	//initialize chip8
	emu.initialize();
	
	//load game
	emu.loadGame("Pong");
	
	for(;;){
		//emulate cycle
		emu.emulateCycle();
		// draw if the draw flag is set, updates screen
		if(emu.drawFlag){}
			//drawGraphics();

		//Store key press state (Press and Release)
		emu.setKeys();
	}
}
