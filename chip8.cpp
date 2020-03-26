#include "chip8.h"

void chip8::initialize(){
	PC = 0x200;
	opcode = 0;
	IR = 0;
	stack_ptr = 0;
	for(auto i : gfx)
		i = 0;
	for(auto i : _stack)
		i = 0;
	for(auto i : V)
		i = 0;
	for(int i = 0; i != 80; i++)
		memory[i] = chip8_fontset[i];
	for(int i = 0x200; i != 4096; i++)
		memory[i] = 0;
}

void chip8::loadGame(std::string game){
	;
}

void chip8::emulateCycle(){
	;
}

void chip8::setKeys(){
	;
}
