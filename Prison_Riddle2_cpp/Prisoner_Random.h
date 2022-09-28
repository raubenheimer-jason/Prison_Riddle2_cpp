#pragma once

#include <vector>
#include "Prisoner.h"

class Prisoner_Random :public Prisoner
{
protected:
	std::vector<size_t> searched_boxes;

public:
	Prisoner_Random(const size_t number, const size_t num_prisoners, const size_t max_search_boxes);
	bool search_box(const size_t num_in_box);
};