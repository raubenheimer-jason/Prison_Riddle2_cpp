#include "Prisoner_Random.h"

// Constructor
Prisoner_Random::Prisoner_Random(const size_t number, const size_t num_prisoners, const size_t max_search_boxes)
	: Prisoner{ number, num_prisoners, max_search_boxes }, random_boxes(num_prisoners, 0)
{
	// initialise random_boxes vector

	// set each value of the vector, starting at 0, and incrementing by 1
	std::iota(random_boxes.begin(), random_boxes.end(), 0);

	// shufle box numbers in boxes vector
	// https://www.youtube.com/watch?v=oW6iuFbwPDg&ab_channel=TopShelfTechnology

	std::ranges::shuffle(random_boxes, rd);

	//std::cout << "random boxes size -- " << random_boxes.size() << std::endl;
}

bool Prisoner_Random::search_box(const size_t num_in_box)
{
	boxes_searched++;
	box_to_search = next_box_to_search(); // for next time
	return is_number_found(num_in_box);
}

/*
Return a random number (that hasnt already been selected)
between 0 and num_boxes-1
*/
size_t Prisoner_Random::next_box_to_search()
{

	size_t temp{ random_boxes.back() };
	//std::cout << "size of random_boxes: " << random_boxes.size() << " -- temp: " << temp << std::endl;
	random_boxes.pop_back();
	return temp;
}
