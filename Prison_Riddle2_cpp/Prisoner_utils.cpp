
#include "Prisoner_utils.h"

/*
For random prisoners
*/
void deallocate_prisoners_rand(std::vector<Prisoner_Random*>& vec)
{
	// Deallocate heap memory
	for (auto p : vec)
		delete p;
	vec.clear();
}


/*
For loop prisoners
*/
void deallocate_prisoners_loop(std::vector<Prisoner_Loop*>& vec)
{
	// Deallocate heap memory
	for (auto p : vec)
		delete p;
	vec.clear();
}


void initialise_prisoners_rand(size_t num_prisoners, size_t max_search_boxes, std::vector<Prisoner_Random*>& vec)
{
	for (size_t i{}; i < num_prisoners; ++i)
	{
		Prisoner_Random* p = new Prisoner_Random{ i, num_prisoners, max_search_boxes };
		vec.push_back(p);
		// need to deallocate this onece the sim is done
	}
}


void initialise_prisoners_loop(size_t num_prisoners, size_t max_search_boxes, std::vector<Prisoner_Loop*>& vec)
{
	for (size_t i{}; i < num_prisoners; ++i)
	{
		Prisoner_Loop* p = new Prisoner_Loop{ i, num_prisoners, max_search_boxes };
		vec.push_back(p);
		// need to deallocate this onece the sim is done
	}
}


bool search_boxes_loop(const std::vector<size_t>& boxes, Prisoner_Loop* prisoner)
{
	bool found{ false };
	while (!found && prisoner->still_boxes_left())
	{
		size_t num_in_box = boxes.at(prisoner->get_box_to_search());
		found = prisoner->search_box(num_in_box);
	}

	return found;
}


/*
Need to search random boxes, dont search the same box more than once
*/
bool search_boxes_random(const std::vector<size_t>& boxes, Prisoner_Random* prisoner)
{
	bool found{ false };
	while (!found && prisoner->still_boxes_left())
	{
		size_t num_in_box = boxes.at(prisoner->get_box_to_search());
		found = prisoner->search_box(num_in_box);
	}

	return found;
}


//void display_prisoners(const std::vector<Prisoner*>& vec)
//{
//	std::cout << "\n=== Prisoners ===" << std::endl;
//	std::cout << std::boolalpha;
//	for (const auto prisoner : vec)
//		prisoner->display();
//}
