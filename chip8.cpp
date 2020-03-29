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
		case 0x1000: // 1NNN: Jumps to address NNN
			break;
		case 0x2000: // 2NNN: Calls subroutine at NNN
			break;
		case 0x3000: // 3XNN: skips the next instruction if VX == RR
			break;
		case 0x4000: // 4XNN: skips next instruction if VX != NN
			break;
		case 0x5000: // 5XY0: skips next instruction if VX == VY
			break;
		case 0x6000: // 6XNN: sets VX to NN (VX = NN)
			break;
		case 0x7000: // 7XNN: Adds NN to VX (Carry flag is not changed) 
			break;
		case 0x8000: //8 has multiiple instructions will need inner switch statement
			switch(opcode & 0x000F){
				case 0x0000: // 8XY0: sets VX to the value of VY
					break;
				case 0x0001: // 8XY1: set VX to VX or VY (Bitwise OR)
					break;
				case 0x0002: // 8XY2: set VX to VX and VY (Bitwise AND)
					break;
				case 0x0003: // 8XY3: sets VX to VX xor VY
					break;
				case 0x0004: // 8XY4: adds VY to VX and sets VF to 1 if theres a carry and 0 otherwise
					break;
				case 0x0005: // 8XY5: Subtracts VY from VX VF is set to 0 when theres a borrow and 1 otherwise
					break;
				case 0x0006: // 8XY6: Store the least significant bit of VX in VF and shift VX to the right by 1
					break;
				case 0x0007: // 8XY7: Sets VX to VY minus VX. VF is set to 0 when theres a borrow and 1 when there isn't
					break;
				case 0x000E: // 8XYE: Stores the most significant bit of VX in VF and shifts VX to the left by 1
				default:
					std::cout << "Unknown opcode " << std::hex << opcode;
			}
			break;
		case 0x9000:
			break;
		case 0xA000: // ANNN: Sets IR to the Adress NNN
			//execute
			IR = opcode & 0x0FFF;
			PC += 2;
			break;
		case 0xB000: // BNNN: Jumps to adress NNN plus V0;
			//execute
			PC = V[0] ^ (opcode & 0xFFF);
			break;
		case 0xC000: // CXNN: Sets VX to the result of a bitwise AND operation on a random number (0 to 255) and NN
			break;
		case 0xD000: // DXYN draws a sprite at cord (VX, VY), had width of 8 pixels and height of N pixels see wiki for a more detailed explanation
			break;
		case 0xE000: // Need inner switch Statement

			break;
		case 0xF000: // Need inner switch Statement

			break;
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
