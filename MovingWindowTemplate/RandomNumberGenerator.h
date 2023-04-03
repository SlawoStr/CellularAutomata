#pragma once
#include <random>

class RandomNumberGenerator
{
private:
	std::random_device rd;
	std::mt19937 generator;
	std::uniform_int_distribution<>uniShortDistr;
	std::uniform_int_distribution<>uniLongDistr;
public:
	RandomNumberGenerator(int smin = 0, int smax = 1, int lmin = 0, int lmax = 1) : generator(rd()), uniShortDistr(smin, smax), uniLongDistr{ lmin,lmax }{}
	int getShortDistr() { return uniShortDistr(generator); };
	int getLongDistr() { return uniLongDistr(generator); };
};