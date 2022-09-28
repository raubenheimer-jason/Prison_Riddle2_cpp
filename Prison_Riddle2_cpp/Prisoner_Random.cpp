#include "Prisoner_Random.h"

// Constructor
Prisoner_Random::Prisoner_Random(const size_t number, const size_t num_prisoners, const size_t max_search_boxes)
	: Prisoner{ number, num_prisoners, max_search_boxes }, searched_boxes{}
{
}

bool Prisoner_Random::search_box(const size_t num_in_box)
{
	boxes_searched++;
	box_to_search = num_in_box; // for next time
	return is_number_found(num_in_box);
}