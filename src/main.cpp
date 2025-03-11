#include "engine/Simplex.hpp"
#include "scenes/MainScene.hpp"

int main() {
	Simplex::CreateWindow("Industria", 1280, 720);

	Simplex::SetScene(MainScene());

	Simplex::Loop();

	return 0;
}
