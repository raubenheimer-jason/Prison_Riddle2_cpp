#include "Prisoner_Loop.h"

// Constructor
Prisoner_Loop::Prisoner_Loop(const size_t number, const size_t num_prisoners, const size_t max_search_boxes)
	: Prisoner{ number, num_prisoners, max_search_boxes }
{
}

bool Prisoner_Loop::search_box(const size_t num_in_box)
{
	boxes_searched++;
	box_to_search = num_in_box; // for next time
	return is_number_found(num_in_box);
}