#ifndef __chip8_h
#define __chip8_h
class chip8{
	private:
		unsigned short opcode;
		//IR is a 16bit Reg that stores memory address
		unsigned short IR;
		//Memory of Chip
		unsigned char memory[4096];
		//stack
		unsigned short stack[16];
		//prgram counter
		unsigned short PC;
		//registers
		unsigned char V0;
		unsigned char V1;
		unsigned char V2;
		unsigned char V3;
		unsigned char V4;
		unsigned char V5;
		unsigned char V6;
		unsigned char V7;
		unsigned char V8;
		unsigned char V9;
		unsigned char VA;
		unsigned char VB;
		unsigned char VC;
		unsigned char VD;
		unsigned char VE;
		//special register for certain opcodes
		unsigned char VF;
		//timers for sound and delay
		unsigned char sound_timer;
		unsigned char delay_timer;
	
	public:
		void initialize();
		void emulateCycle();
		bool drawFlag;
};
#endif
