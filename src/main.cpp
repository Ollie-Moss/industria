#include "engine/Simplex.hpp"
#include "scenes/MainScene.hpp"

int main() {
	Simplex::CreateWindow("Industria", 1280-190, 720-160);

	Simplex::SetScene(MainScene());

	Simplex::Loop();

	return 0;
}
