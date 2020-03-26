#ifndef __chip8_h
#define __chip8_h
#include<iostream>
#include<string>
#include<fstream>
class chip8{
	private:
		unsigned short opcode;
		unsigned char memory[4096];
		unsigned short _stack[16];
		unsigned short stack_ptr;
		//IR is a 16bit Reg that stores memory address
		unsigned short IR;
		//prgram counter
		unsigned short PC;
		//registers
		unsigned char V[16];
		//graphics system
		unsigned char gfx[64 * 32];
		//timers
		unsigned char sound_timer;
		unsigned char delay_timer;
		//key pad
		unsigned char key[16];
		unsigned char chip8_fontset[80];
	
	public:
		void initialize();
		void loadGame(std::string);
		void emulateCycle();
		void setKeys();
		bool drawFlag;
};
#endif
