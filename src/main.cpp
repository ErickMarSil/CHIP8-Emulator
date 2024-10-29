#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

bool SDL_setup(){
	Uint32 flags = (SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);	
	return SDL_Init(flags);
}

int main(){
	bool content = SDL_setup();
	cout << content << "\n";
	return 0;
}
