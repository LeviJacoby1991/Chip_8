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
	std::string currGame = game + ".ch8";
	std::ifstream src;
	//open game as ifstream in binary mode
	src.open(currGame,std::ios::in | std::ios::binary);	
	//get file size
	src.seekg(0, std::ios::end);
	int filesz = (int) src.tellg();

	src.seekg(0, std::ios::beg);

	char buff[filesz];
	src.read(buff, filesz);

	for(int i = 0; i != filesz; i++){
		memory[i + 512] = buff[i];
	}
	src.close();
}

void chip8::emulateCycle(){
	opcode = memory[PC] << 8 | memory[PC + 1];

	//switch decodes the opcode and then executes it in case body
	switch(opcode & 0xF000){
		case 0xA000:
			IR = opcode & 0x0FFF;
			PC += 2;
			break;
		default:
			std::cout << "Unkown opcode: " << std::hex << opcode;
	}
}

void chip8::setKeys(){
	;
}
