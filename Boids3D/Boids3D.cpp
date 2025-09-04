// Boids3D.cpp : Defines the entry point for the application.
//

#include "Boids3D.h"

int main(){

	Application app;

	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::println(stderr, "ERROR [MAIN]: {}", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
