#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <cmath>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>
#include "../engine/ecs/IComponent.hpp"
#include "../engine/ecs/Entity.hpp"
#include "../engine/ecs/components/Renderer.hpp"

#define maxPrimeIndex 10

class MapGenerator : public IComponent {
  public:
	int numX, numY;
	int numOctaves = 7;
	double persistence = 0.68;
	std::vector<unsigned int> tileVertices;

	MapGenerator(int numX, int numY) : numX(numX), numY(numY) {};

	void Start() override {
		Generate();
		entity->GetComponent<Renderer>()->model.fillSSBO(entity->GetComponent<MapGenerator>()->tileVertices);
	}

	void Generate() {
		for (int y = 0; y < numY; y++) {
			for (int x = 0; x < numX; x++) {
				double noise = ValueNoise_2D(x, y);

				// std::cout << noise << std::endl;
				if (noise > 0.3) {
					continue;
				} else {
					unsigned int vertex1 = (static_cast<uint32_t>(x)) |
										   (static_cast<uint32_t>(y) << 16);
					unsigned int vertex2 = (static_cast<uint32_t>(0)) |
										   (static_cast<uint32_t>(1 << 16)) |
										   (static_cast<uint32_t>(1 << 24));
					tileVertices.push_back(vertex1);
					tileVertices.push_back(vertex2);
				}
			}
		}
	};

  private:
	int primeIndex = 0;

	int primes[maxPrimeIndex][3] = {
		{995615039, 600173719, 701464987},
		{831731269, 162318869, 136250887},
		{174329291, 946737083, 245679977},
		{362489573, 795918041, 350777237},
		{457025711, 880830799, 909678923},
		{787070341, 177340217, 593320781},
		{405493717, 291031019, 391950901},
		{458904767, 676625681, 424452397},
		{531736441, 939683957, 810651871},
		{997169939, 842027887, 423882827}};

	double Noise(int i, int x, int y) {
		int n = x + y * 57;
		n = (n << 13) ^ n;
		int a = primes[i][0], b = primes[i][1], c = primes[i][2];
		int t = (n * (n * n * a + b) + c) & 0x7fffffff;
		return 1.0 - (double)(t) / 1073741824.0;
	}

	double SmoothedNoise(int i, int x, int y) {
		double corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) +
						  Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) /
						 16,
			   sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) +
						Noise(i, x, y + 1)) /
					   8,
			   center = Noise(i, x, y) / 4;
		return corners + sides + center;
	}

	double Interpolate(double a, double b, double x) { // cosine interpolation
		double ft = x * 3.1415927,
			   f = (1 - cos(ft)) * 0.5;
		return a * (1 - f) + b * f;
	}

	double InterpolatedNoise(int i, double x, double y) {
		int integer_X = x;
		double fractional_X = x - integer_X;
		int integer_Y = y;
		double fractional_Y = y - integer_Y;

		double v1 = SmoothedNoise(i, integer_X, integer_Y),
			   v2 = SmoothedNoise(i, integer_X + 1, integer_Y),
			   v3 = SmoothedNoise(i, integer_X, integer_Y + 1),
			   v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1),
			   i1 = Interpolate(v1, v2, fractional_X),
			   i2 = Interpolate(v3, v4, fractional_X);
		return Interpolate(i1, i2, fractional_Y);
	}

	double ValueNoise_2D(double x, double y) {
		double total = 0,
			   frequency = pow(2, numOctaves),
			   amplitude = 1;
		for (int i = 0; i < numOctaves; ++i) {
			frequency /= 2;
			amplitude *= persistence;
			total += InterpolatedNoise((primeIndex + i) % maxPrimeIndex,
									   x / frequency, y / frequency) *
					 amplitude;
		}
		return total / frequency;
	}
};
#endif
