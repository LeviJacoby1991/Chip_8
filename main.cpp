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
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Event e;
SDL_Rect p;

chip8 emu;

int main(int argc, char **argv){

	bool quit = false;
	//SDL_Event
	//set up screen
	//initialize chip8
	emu.initialize();
	
	//load game
	emu.loadGame("Pong");
	//initialize SDL	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
	SDL_CreateWindowAndRenderer(640, 320, SDL_WINDOW_RESIZABLE, &window, &renderer);
	//texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 8, 8);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
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
	if(key_event.type == SDL_KEYDOWN){
		switch(key_event.key.keysym.sym){
			case SDLK_0:
				emu.key[0] = 1;
				break;
			case SDLK_1:
				emu.key[1] = 1;
				break;
			case SDLK_2:
				emu.key[2] = 1;
				break;
			case SDLK_3:
				emu.key[3] = 1;
				break;
			case SDLK_4:
				emu.key[4] = 1;
				break;
			case SDLK_q:
				emu.key[5] = 1;
				break;
			case SDLK_w:
				emu.key[6] = 1;
				break;
			case SDLK_e:
				emu.key[7] = 1;
				break;
			case SDLK_r:
				emu.key[8] = 1;
				break;
			case SDLK_a:
				emu.key[9] = 1;
				break;
			case SDLK_s:
				emu.key[10] = 1;
				break;
			case SDLK_d:
				emu.key[11] = 1;
				break;
			case SDLK_f:
				emu.key[12] = 1;
				break;
			case SDLK_j:
				emu.key[13] = 1;
				break;
			case SDLK_k:
				emu.key[14] = 1;
				break;
			case SDLK_l:
				emu.key[15] = 1;
				break;
			default:
				break;
		}
	}
	//if key up set the corresponding in the chip8 to 1
	if(key_event.type == SDL_KEYUP){
		switch(key_event.key.keysym.sym){
			case SDLK_0:
				emu.key[0] = 0;
				break;
			case SDLK_1:
				emu.key[1] = 0;
				break;
			case SDLK_2:
				emu.key[2] = 0;
				break;
			case SDLK_3:
				emu.key[3] = 0;
				break;
			case SDLK_4:
				emu.key[4] = 0;
				break;
			case SDLK_q:
				emu.key[5] = 0;
				break;
			case SDLK_w:
				emu.key[6] = 0;
				break;
			case SDLK_e:
				emu.key[7] = 0;
				break;
			case SDLK_r:
				emu.key[8] = 0;
				break;
			case SDLK_a:
				emu.key[9] = 0;
				break;
			case SDLK_s:
				emu.key[10] = 0;
				break;
			case SDLK_d:
				emu.key[11] = 0;
				break;
			case SDLK_f:
				emu.key[12] = 0;
				break;
			case SDLK_j:
				emu.key[13] = 0;
				break;
			case SDLK_k:
				emu.key[14] = 0;
				break;
			case SDLK_l:
				emu.key[15] = 0;
				break;
			default:
				break;
		}
	}
}
void drawChip8(){
	//go through the chip8s graphics array and draw to the screen if
	//SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	p.w = 10;
	p.h = 10;
		for(int y = 0; y != 32; y++){
			for(int x = 0; x != 64; x++){
					p.x =  x*10 + p.w;
					p.y =  y*10 + p.h;
				if(emu.gfx[x + y*64] == 1){
					SDL_RenderDrawRect(renderer, &p);
					SDL_RenderFillRect(renderer, &p);
					std::cout<< "1";
				}else
					std::cout << "0";
			}
			std::cout << "\n";
		} 
		std::cout << "\n";
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		emu.drawFlag = false;
}
