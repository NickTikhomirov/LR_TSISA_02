#pragma once

#include <unordered_set>

using std::unordered_set;

class UniqueGenerator
{
	unordered_set<double> contents;
	static double generate_raw();
	double a;
	double b;
public:
	double generate();
	UniqueGenerator(double, double);
	~UniqueGenerator();
};

