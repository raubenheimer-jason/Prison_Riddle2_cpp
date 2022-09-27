#include <iostream>
#include <iomanip> // setprecision
#include <vector>
#include <algorithm>
#include <ranges>
#include <random>
#include <numeric> // iota

#include "Prisoner.h"

const bool random_search{ false }; // set to true to search boxes randomly
const size_t num_sims{ 100000 };

const size_t num_prisoners{ 100 };
const size_t num_boxes{ num_prisoners };
const size_t max_search_boxes{ num_boxes / 2 };

void initialise_boxes(std::vector<size_t>& vec);
void initialise_prisoners(std::vector<Prisoner*>& vec);
void display_boxes(const std::vector<size_t>& vec);
void display_prisoners(const std::vector<Prisoner*>& vec);
bool search_boxes(const std::vector<size_t>& boxes, Prisoner* prisoner);

double run_sim(const bool random_search);

int main()
{
	std::cout << std::boolalpha;

	double total{};

	for (size_t i{}; i < num_sims; ++i)
	{
		if (i % 1000 == 0)
			std::cout << "Sim: " << i << std::endl;
		total += run_sim(random_search);
	}

	std::cout << std::endl;

	double avg{ total / num_sims };

	std::cout << "Average success for " << num_sims << " simulations: " << avg << std::endl;

	return 0;
}

double run_sim(const bool random_search)
{
	// vector of size_t, num_boxes in size, all initialised to 0
	std::vector<size_t> boxes(num_boxes, 0);
	initialise_boxes(boxes);
	// display shuffled boxes
	//display_boxes(boxes);

	// vector of prisoners
	std::vector<Prisoner*> prisoners;
	initialise_prisoners(prisoners);
	// display initialised prisoners
	// display_prisoners(prisoners);

	size_t num_found{};

	if (random_search)
	{
		// search randomly
	}
	else
	{
		// search using proposed technique
		// loop over each prisoner and search for their number
		for (auto p : prisoners)
		{
			if (search_boxes(boxes, p))
				num_found++;
		}
	}

	// Deallocate heap memory
	for (auto p : prisoners)
		delete p;
	prisoners.clear();

	// display prisoners
	//display_prisoners(prisoners);

	double perc_found{ (static_cast<double>(num_found) / num_prisoners) * 100 };

	return perc_found;
}

void initialise_boxes(std::vector<size_t>& vec)
{
	// set each value of the vector, starting at 0, and incrementing by 1
	std::iota(vec.begin(), vec.end(), 0);

	// shufle box numbers in boxes vector
	// https://www.youtube.com/watch?v=oW6iuFbwPDg&ab_channel=TopShelfTechnology

	std::random_device rd;
	std::ranges::shuffle(vec, rd);
}

void initialise_prisoners(std::vector<Prisoner*>& vec)
{
	for (size_t i{}; i < num_prisoners; ++i)
	{
		Prisoner* p = new Prisoner{ i, num_prisoners, max_search_boxes };
		vec.push_back(p);
		// need to deallocate this onece the sim is done
	}
}

void display_boxes(const std::vector<size_t>& vec)
{
	size_t i{};
	std::cout << "\n=== Boxes ===" << std::endl;
	for (auto box : vec)
		std::cout << "Box " << i++ << ":\t" << box << std::endl;
}

void display_prisoners(const std::vector<Prisoner*>& vec)
{
	std::cout << "\n=== Prisoners ===" << std::endl;
	std::cout << std::boolalpha;
	for (const auto prisoner : vec)
		prisoner->display();
}

bool search_boxes(const std::vector<size_t>& boxes, Prisoner* prisoner)
{
	bool found{ false };
	while (!found && prisoner->still_boxes_left())
	{
		size_t num_in_box = boxes.at(prisoner->get_box_to_search());
		found = prisoner->search_box(num_in_box);
	}

	return found;
}