#include<iostream>
#include<string>
//#include //library for output, input, and sound
#include<SDL2/SDL.h>
#include "chip8.h"


//Get sdl poll event and check game controlls are press;
void setkeys();
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
	emu.loadGame("Fishie");
	//initialize SDL	
	SDL_Init(SDL_INIT_VIDEO);
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
			//setkeys(/*pass in event */);
	}
}

void setkeys(){
	//check sdl poll event for key up or key down
	//if key up set the corresponding key in the chip8 to 0	
	
	//if key down set the corresponding in the chip8 to 1
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
