#include "Box_utils.hpp"


void initialise_boxes(std::vector<size_t>& vec)
{
	// set each value of the vector, starting at 0, and incrementing by 1
	std::iota(vec.begin(), vec.end(), 0);

	// shufle box numbers in boxes vector
	// https://www.youtube.com/watch?v=oW6iuFbwPDg&ab_channel=TopShelfTechnology

	std::random_device rd;
	std::ranges::shuffle(vec, rd);
}


void display_boxes(const std::vector<size_t>& vec)
{
	size_t i{};
	std::cout << "\n=== Boxes ===" << std::endl;
	for (auto box : vec)
		std::cout << "Box " << i++ << ":\t" << box << std::endl;
}
