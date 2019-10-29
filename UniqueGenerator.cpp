#include "UniqueGenerator.h"

#include <random>

using std::mt19937;
using std::uniform_real_distribution;
using std::random_device;


UniqueGenerator::UniqueGenerator(double a1, double b1)
{
	a = a1;
	b = b1;
}

UniqueGenerator::~UniqueGenerator()
{
	contents.clear();
}

double UniqueGenerator::generate_raw() {
	static mt19937 engine(random_device{}());
	auto generator = uniform_real_distribution<double>(0.0, 1.0);
	return generator(engine);
}

double UniqueGenerator::generate() {
	double raw;
	do raw = generate_raw();
	while (contents.find(raw)!=contents.end());
	contents.insert(raw);
	return a + (b - a) * raw;
}