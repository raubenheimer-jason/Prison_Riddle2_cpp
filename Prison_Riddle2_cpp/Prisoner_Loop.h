#pragma once

#include "Prisoner.h"

class Prisoner_Loop :public Prisoner
{
public:
	Prisoner_Loop(const size_t number, const size_t num_prisoners, const size_t max_search_boxes);
	bool search_box(const size_t num_in_box);

};
