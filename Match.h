#pragma once
#include "bitSequence.h"
using namespace std;

class match
{
public:
	size_t abMatch(size_t A, size_t B, size_t mask);
	vector<vector<size_t>> newbitMatchNomutily(query a, vector<vector<size_t>> bitSequence, unordered_map<string, int> eventmap, int timeContainer);
	vector<vector<size_t>> newbitMatch(query a, vector<vector<size_t>> bitSequence, unordered_map<string, int> eventmap, int timeContainer);
};

