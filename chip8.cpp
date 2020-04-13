#include "chip8.h"

void chip8::initialize(){
	PC = 0x200;
	opcode = 0;
	IR = 0;
	stack_ptr = 0;
	for(auto &i : gfx)
			i = 0;
	for(auto &i : _stack)
		i = 0;
	for(auto &i : V)
		i = 0;
	for(auto &i : key)
		i = 0;
	for(int i = 0; i != 80; i++)
		memory[i] = chip8_fontset[i];
	for(int i = 0x200; i != 4096; i++)
		memory[i] = 0;

	delay_timer = 0;
	sound_timer = 0;

	drawFlag = true;
	srand(time(NULL));
}

void chip8::loadGame(char* game){
	std::string currGame(game);
	currGame += ".ch8";
	std::ifstream src (currGame, std::ifstream::binary);
	try{
		if(!src){
			throw std::runtime_error("File does not exist\n");
		}else{
			src.seekg(0, src.end);
			int sz = src.tellg();
			src.seekg(0, src.beg);
			char * buffer = new char[sz];
			src.read(buffer,sz);
			for(int i = 0; i != sz; i++){
				memory[0x200 + i] = buffer[i];
			}
			
			delete[] buffer;
		}
	}catch(std::exception &err){
		std::cout<< "try another file\n";
	}
}

void chip8::emulateCycle(){
	opcode = memory[PC] << 8 | memory[PC + 1];

	//switch decodes the opcode and then executes it in case body
	
	//Variables
    i += 1;
	// NN is lower 8 its of opcode
	// X is bits 4 - 8 (big endian)
	// Y is bits 9 - 13 (big endian)
	unsigned char NN = 0x00;
	unsigned char X = 0x00;
	unsigned char Y = 0x00;
	unsigned char N = 0x00;
	unsigned short pixel = 0x0000;
	switch(opcode & 0xF000){
		case 0x1000: // 1NNN: Jumps to address NNN
			PC = opcode & 0x0FFF;
			break;
		case 0x2000: // 2NNN: Calls subroutine at NNN
			_stack[stack_ptr] = PC;
			++stack_ptr;
			PC = opcode & 0x0FFF;
			break;
		case 0x3000: // 3XNN: skips the next instruction if VX == RR
			X = (opcode & 0x0F00) >> 8;
			NN = opcode & 0x00FF;
			if(V[X] == NN){
				PC += 4;
			}else{
				PC += 2;
			}
			break;
		case 0x4000: // 4XNN: skips next instruction if VX != NN
			X = (opcode & 0x0F00) >> 8;
			NN = opcode & 0x00FF;
			if(V[X] != NN)
				PC += 4;
			else
				PC += 2;
			break;
		case 0x5000: // 5XY0: skips next instruction if VX == VY
			X = (opcode & 0x0F00) >> 8;
			Y = (opcode & 0x00F0) >> 4;
			if(V[X] == V[Y])
				PC += 4;
			else
				PC += 2;
			break;
		case 0x6000: // 6XNN: sets VX to NN (VX = NN)
			X = (opcode & 0x0F00) >> 8;
			NN = (opcode & 0x00FF);
			V[X] = NN;
			PC += 2;
			break;
		case 0x7000: // 7XNN: Adds NN to VX (Carry flag is not changed) 
			X = (opcode & 0x0F00) >> 8;
			NN = (opcode & 0x00FF);
			V[X] += NN;
			PC += 2;
			break;
		case 0x8000: //8 has multiiple instructions will need inner switch statement
			switch(opcode & 0x000F){
				case 0x0000: // 8XY0: sets VX to the value of VY
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					V[X] = V[Y];
					PC += 2;
					break;
				case 0x0001: // 8XY1: set VX to VX or VY (Bitwise OR)
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					V[X] = V[X] | V[Y];
					PC += 2;
					break;
				case 0x0002: // 8XY2: set VX to VX and VY (Bitwise AND)
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					V[X] = V[X] & V[Y];
					PC += 2;
					break;
				case 0x0003: // 8XY3: sets VX to VX xor VY
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					V[X] = V[X] ^ V[Y];
					PC += 2;
					break;
				case 0x0004: // 8XY4: adds VY to VX and sets VF to 1 if theres a carry and 0 otherwise
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					if( V[X] + V[Y] > 0xFF){
						V[0x000F] = 1;
						V[X] = V[X] + V[Y];
					}else{
						V[0x000F] = 0;
						V[X] = V[X] + V[Y];
					}
					PC += 2;
					break;
				case 0x0005: // 8XY5: Subtracts VY from VX VF is set to 0 when theres a borrow and 1 otherwise
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					if(V[Y] > V[X]){
						V[X] = V[X] - V[Y];
						V[0x000F] = 0;
					}else{
						V[X] = V[X] - V[Y];
						V[0x000F] = 1;
					}
					PC += 2;
					break;
				case 0x0006: // 8XY6: Store the least significant bit of VX in VF and shift VX to the right by 1
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					V[0x000F] = V[X] & 0x0001;
					V[X] = V[X] >> 1;
					PC += 2;
					break;
				case 0x0007: // 8XY7: Sets VX to VY minus VX. VF is set to 0 when theres a borrow and 1 when there isn't
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					if(V[X] > V[Y]){
						V[X] = V[Y] - V[X];
						V[0x000F] = 0;
					}else{
						V[X] = V[Y] - V[X];
						V[0x000F] = 1;
					}
					PC += 2;
					break;
				case 0x000E: // 8XYE: Stores the most significant bit of VX in VF and shifts VX to the left by 1
					X = (opcode & 0x0F00) >> 8;
					Y = (opcode & 0x00F0) >> 4;
					V[0x000F] = V[X] >> 7;
					V[X] = V[X] << 1;
					PC += 2;
				default:
					std::cout << "Unknown opcode " << std::hex << opcode;
					break;
			}
			break;
		case 0x9000: // 9XY0: Skip next instruction if VX != VY
			X = (opcode & 0x0F00) >> 8;
			Y = (opcode & 0x00F0) >> 4;
			if(V[X] != V[Y])
				PC += 4;
			else
				PC += 2;
			break;
		case 0xA000: // ANNN: Sets IR to the Adress NNN
			//execute
			IR = opcode & 0x0FFF;
			PC += 2;
			break;
		case 0xB000: // BNNN: Jumps to adress NNN plus V0;
			//execute
			PC = V[0x0000] + (opcode & 0x0FFF);
			break;
		case 0xC000: // CXNN: Sets VX to the result of a bitwise AND operation on a random number (0 to 255) and NN
			X = (opcode & 0x0F00) >> 8;
			NN = (opcode & 0x00FF);
			V[X] = NN & (rand() % 0xFF);
			PC += 2;
			break;
		case 0xD000: // DXYN draws a sprite at cord (VX, VY), had width of 8 pixels and height of N pixels see wiki for a more detailed explanation
			X = (opcode & 0x0F00) >> 8;
			Y = (opcode & 0x00F0) >> 4;
			N = opcode & 0x000F; // Height of sprite
			V[0x000F] = 0;
			for(int yline = 0; yline < N; yline++){
				for(int screenbit = 0; screenbit != 8; screenbit++){
					//determine which pixels on screen are getting xor/set
					pixel = memory[IR + yline];
					if((pixel & (0x80 >> screenbit)) != 0){
						
						if (gfx[(V[X] + screenbit) + ((V[Y] + yline) * 64)] != 0){
							V[0x000F] = 1;
						}

						gfx[(V[X] + screenbit) + ((V[Y] + yline) * 64 )] ^= 1;
					}
				}
			}
			drawFlag = true;
			PC += 2;
			break;
		case 0xE000: // Need inner switch Statement
			switch(opcode & 0x00FF){
				case 0x009E: // EX9E: Skip the next instruction if the key stored in VX is pressed
					X = (opcode & 0x0F00) >> 8;
					if(key[V[X]] != 0)
						PC += 4;
					else	
						PC += 2;
					break;
				case 0x00A1: // EXA1: Skips the next if the key stored in VX isn't pressed
					X = (opcode & 0x0F00) >> 8;
					if(key[V[X]] == 0)
						PC += 4;
					else
						PC += 2;
					break;
				default:
					std::cout << "Unknown opcode " << std::hex << opcode;
					break;
			}
			break;
		case 0xF000: // Need inner switch Statement
			switch(opcode & 0x00FF){
				case 0x0007: // FX07: set VX = delay timer
					X = (opcode & 0x0F00) >> 8;
					V[X] = delay_timer;
					PC += 2;
					break;
				case 0x000A: // FX0A store the value of the k in VX
					{					
						bool keyPress = false;
						X = (opcode & 0x0F00) >> 8;
						for(int i = 0; i != 16; ++i){
							if(key[i] != 0){
								V[X] = i;
								keyPress = true;
							}
						}
						if(!keyPress)
							return;
						PC += 2;
					}
					break;
				case 0x0015: // FX15 store the value in VX in the delay timer
					X = (opcode & 0x0F00) >> 8;
					delay_timer = V[X];
					PC += 2;
					break;
				case 0x0018: // FX18 set sound_timer to VX
					X = (opcode & 0x0F00) >> 8;
					sound_timer = V[X];
					PC += 2;
					break;
				case 0x001E: // FX1E set IR to IR + VX
					X = (opcode & 0x0F00) >> 8;
					if(IR + V[X] > 0xFF)
						V[0xF] = 1;
					else
						V[0xF] = 0;
					IR = IR + V[X];
					PC += 2;
					break;
				case 0x0029: // FX29: set I to the location of sprite for digit VX 
					X = (opcode & 0x0F00) >> 8;
					IR = gfx[ V[X] ] * 0x5;
					PC += 2;
					break;
				case 0x0033: // FX33: store BCD representation of VX in memory locations I, I+1, I+2;
					X = (opcode & 0x0F00) >> 8;
					memory[IR] = V[X]/100; // holds hundreds digit
					memory[IR + 1] = (V[X]/10)%10; // holds tens digit
					memory[IR + 2] = (V[X]%100)%10; // holds ones digit
					PC += 2;
					break;
				case 0x0055: // FX55 Stores registers V0 through VX in memory starting at location I
					X = (opcode & 0x0F00) >> 8;
					for(auto i = 0; i != X + 1; i++){
						memory[IR + i] = V[i];
					}
					IR += ((opcode & 0x0F00) >> 8) + 1;
					PC += 2;
					break;
				case 0x0065: // FX65 Reads registers values from memory starting at the locaiton I into V0 to VX
					X = (opcode & 0x0F00) >> 8;
					for(auto i = 0; i != X + 1; i++){
						V[i] = memory[IR + i];
					}
					IR +=  X + 1;
					PC += 2;
					break;
				default:
					std::cout << "Here 0xF" << "\n";
					std::cout << "Unkown opcode " << std::hex << opcode;
					break;
			}
			break;
		case 0x0000:
			switch(opcode & 0x000F){
				case 0x0000: // 0x00E0: Clears the Screen
					/*for(auto &i : gfx)
						i = 0x0;*/
					for(int i = 0; i != 32*64; i++)
						gfx[i] = 0;
					drawFlag = true;
					PC += 2;
					break;
				case 0x000E: // 0x00EE: Returns from sub-routine
					//execute
					--stack_ptr;
					PC = _stack[stack_ptr];
					PC += 2;
					break;
				default:
					std::cout << "Here 0x0" << "\n";
					std::cout << "Unkown opcode " << opcode << std::hex; 
					break;
			}
			break;
			
		default:
			std::cout << "we have not implemented the opcode\n";
			std::cout << "Unkown opcode: 0x" << std::hex << opcode << std::endl; 
            std::cout << " opcode encountered in cycle: " << i << "\n";
			break;
			
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

