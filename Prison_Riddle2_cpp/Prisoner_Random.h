#pragma once

#include <vector>
#include <random>
#include <numeric> // iota
#include <ranges>
#include <algorithm>
#include <iostream>

#include "Prisoner.h"

class Prisoner_Random :public Prisoner
{
private:
	std::vector<size_t> random_boxes;
	size_t next_box_to_search();
	std::random_device rd;

public:
	Prisoner_Random(const size_t number, const size_t num_prisoners, const size_t max_search_boxes);
	bool search_box(const size_t num_in_box);
};