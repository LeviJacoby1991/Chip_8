#ifndef __chip8_h
#define __chip8_h
#include<string>
class chip8{
	private:
		unsigned short opcode;
		//Memory of Chip
		unsigned char memory[4096];
		//stack
		unsigned short _stack[16];
		//stack pointer
		unsigned short stack_ptr;
		//IR is a 16bit Reg that stores memory address
		unsigned short IR;
		//prgram counter
		unsigned short PC;
		//registers
		unsigned char V[16];
		//graphics system
		unsigned char gfx[64 * 32];
		//timers for sound and delay
		unsigned char sound_timer;
		unsigned char delay_timer;
		//key pad
		unsigned char key[16];
		//chip8 font set
		unsigned char chip8_fontset[80];
	
	public:
		void initialize();
		void emulateCycle();
		void loadGame(std::string);
		bool drawFlag;
};
#endif
