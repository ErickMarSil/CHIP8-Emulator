#include <iostream>
#include "../Source/Headers/init_SDL_screen.hpp"

using namespace std;

int main(){
	bool content = setup();
	cout << content << "\n";
	return 0;
}
