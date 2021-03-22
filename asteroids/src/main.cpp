#include <iostream>
#include "draw_application.h"
int main(int argc, char* argv[]) {
	std::cout << "Main\n";
	draw_application{}.run(argc, argv);
}