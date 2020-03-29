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
		case 0xA000: // ANNN: Sets IR to the Adress NNN
			//execute
			IR = opcode & 0x0FFF;
			PC += 2;
			break;
		case 0xB000: // BNNN: Jumps to adress NNN plus V0;
			//execute
			PC = V[0] ^ (opcode & 0xFFF);
			break;
		//in the event we cant rely on the first four bits to see what the opcode means
		case 0x0000:
			switch(opcode & 0x000F){
				case 0x0000: // 0x00E0: Clears the Screen
					//execute
					PC += 2;
					break;
				case 0x000E: // 0x00EE: Returns from sub-routine
					//execute
					PC += 2;
					break;
				default:
					std::cout << "Unkown opcode " << std::hex << opcode;
			}
		default:
			std::cout << "Unkown opcode: " << std::hex << opcode;
	}

	if(delay_timer > 0)
		--delay_timer;
	if(sound_timer > 0){
		if(sound_timer == 1){
			//sound is played
		}
		--sound_timer;
	}
}

void chip8::setKeys(){
	;
}
