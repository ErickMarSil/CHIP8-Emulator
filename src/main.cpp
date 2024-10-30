#include <iostream>
extern "C" {
	#include <SDL.h>
}

using namespace std;

int main(){
	bool content = setup();
	cout << content << "\n";
	return 0;
}
