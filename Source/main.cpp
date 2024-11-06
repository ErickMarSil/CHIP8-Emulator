#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(){
	bool teste = SDL_Init(SDL_INIT_AUDIO) > 0;
	cout << teste << "\n";
	return 0;
}
