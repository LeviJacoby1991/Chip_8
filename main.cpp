#include<iostream>
#include<string>
//#include //library for output, input, and sound
#include<SDL2/SDL.h>
#include "chip8.h"


//Get sdl poll event and check game controlls are press;
void setkeys(SDL_Event);
//draw chip8 on screen
void drawChip8();

SDL_Renderer *renderer;
SDL_Window *window;
SDL_Event e;
//representation of pixel for screen
SDL_Rect p;

chip8 emu;

int main(int argc, char **argv){
	
	
	bool quit = false;
	//initialize chip8
	emu.initialize();
	
	//load game
	emu.loadGame(argv[1]);
	//initialize SDL	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	
	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer);
	//texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 8, 8);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	while(!quit){

		//poll sdl event
		SDL_PollEvent(&e);
		if(e.type == SDL_QUIT){
			quit = true;
		}
			SDL_RenderClear(renderer);
			//emulate cycle
			emu.emulateCycle();
			// draw if the draw flag is set, updates screen
			if(emu.drawFlag){
				drawChip8();//drawGraphics();
			}

			//Store key press state (Press and Release)
			setkeys(e);

		SDL_Delay(2);
	}
}

void setkeys(SDL_Event key_event){
	//check sdl poll event for key up or key down
	//if key up set the corresponding key in the chip8 to 0	
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	if(keystate[SDL_SCANCODE_0])
		emu.key[0] = 1;
	else
		emu.key[1] = 0;

	if(keystate[SDL_SCANCODE_1])
		emu.key[1] = 1;
	else
		emu.key[1] = 0;

	if(keystate[SDL_SCANCODE_2])
		emu.key[2] = 1;
	else
		emu.key[2] = 0;
	
	if(keystate[SDL_SCANCODE_3])
		emu.key[3] = 1;
	else
		emu.key[3] = 0;

	if(keystate[SDL_SCANCODE_4])
		emu.key[4] = 1;
	else
		emu.key[4] = 0;

	if(keystate[SDL_SCANCODE_5])
		emu.key[5] = 1;
	else
		emu.key[5] = 0;

	if(keystate[SDL_SCANCODE_Q])
		emu.key[6] = 1;
	else
		emu.key[6] = 0;

	if(keystate[SDL_SCANCODE_E])
		emu.key[7] = 1;
	else
		emu.key[7] = 0;

	if(keystate[SDL_SCANCODE_E])
		emu.key[8] = 1;
	else
		emu.key[8] = 0;

	if(keystate[SDL_SCANCODE_R])
		emu.key[9] = 1;
	else
		emu.key[9] = 0;

	if(keystate[SDL_SCANCODE_A])
		emu.key[10] = 1;
	else
		emu.key[10] = 0;

	if(keystate[SDL_SCANCODE_D])
		emu.key[11] = 1;
	else
		emu.key[12] = 1;

	if(keystate[SDL_SCANCODE_F])
		emu.key[13] = 1;
	else
		emu.key[13] = 0;

	if(keystate[SDL_SCANCODE_J])
		emu.key[14] = 1;
	else
		emu.key[14] = 0;

	if(keystate[SDL_SCANCODE_K])
		emu.key[15] = 1;
	else
		emu.key[15] = 0;
}
void drawChip8(){
	//go through the chip8s graphics array and draw to the screen if
	//SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		for(int y = 0; y != 32; y++){
			for(int x = 0; x != 64; x++){
					p.x =  x*10 + p.w;
					p.y =  y*10 + p.h;
					p.w = 10;
					p.h = 10;
				if(emu.gfx[x + y*64] == 1){
					SDL_RenderDrawRect(renderer, &p);
					SDL_RenderFillRect(renderer, &p);
				}
			}
		} 
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		emu.drawFlag = false;
}
