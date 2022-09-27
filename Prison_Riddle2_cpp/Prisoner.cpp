#include "Prisoner.h"
#include <iostream>

// Constructor
Prisoner::Prisoner(const size_t number, const size_t num_prisoners, const size_t max_search_boxes)
	: number{ number }, num_prisoners{ num_prisoners }, max_search_boxes{ max_search_boxes }, boxes_searched{}, found_number{ false }, box_to_search{ number }
{
}


bool Prisoner::search_box(const size_t num_in_box)
{
	boxes_searched++;
	box_to_search = num_in_box; // for next time
	return is_number_found(num_in_box);
}

// method that checks if the number in the box is the prisoners number
bool Prisoner::is_number_found(const size_t num_in_box)
{
	if (num_in_box == number) {
		found_number = true;
	}

	return found_number;
}

bool Prisoner::still_boxes_left()
{
	return (boxes_searched < max_search_boxes);
}

void Prisoner::display() const
{
	std::cout << "Prisoner " << number << ":\t" << found_number << std::endl;
}

const size_t Prisoner::get_box_to_search() const
{
	return box_to_search;
}

const size_t Prisoner::get_number() const
{
	return number;
}

const size_t Prisoner::get_boxes_searched() const
{
	return boxes_searched;
}
