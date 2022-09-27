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

//const size_t num_prisoners{ 4 };
//const size_t num_boxes{ num_prisoners };
//const size_t max_search_boxes{ 2 };

void initialise_boxes(std::vector<size_t>& vec);
void initialise_prisoners(std::vector<Prisoner*>& vec);
void display_boxes(const std::vector<size_t>& vec);
void display_prisoners(const std::vector<Prisoner*>& vec);
bool search_boxes(const std::vector<size_t>& boxes, Prisoner* prisoner);

double run_sim();

int main()
{
	std::cout << std::boolalpha;

	double total{};

	for (size_t i{}; i < num_sims; ++i)
	{
		if (i % 1000 == 0)
			std::cout << "Sim: " << i << std::endl;
		total += run_sim();
	}

	std::cout << std::endl;

	double avg{ total / num_sims };

	std::cout << "Average success for " << num_sims << " simulations: " << avg << std::endl;

	return 0;
}

double run_sim()
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
			//std::cout << "SEARCH" << std::endl;
			if (search_boxes(boxes, p))
				num_found++;
		}
		//std::cout << std::boolalpha;
		//search_boxes(boxes, prisoners.at(76));
	}

	//delete[] prisoners;
	for (auto p : prisoners)
	{
		delete p;
	}
	prisoners.clear();

	// display prisoners
	//display_prisoners(prisoners);

	double perc_found{ (static_cast<double>(num_found) / num_prisoners) * 100 };
	//std::cout << std::setprecision(4) << "perc_found: " << perc_found << std::endl;
	return perc_found;
	//std::cout << __cplusplus << std::endl;
}

void initialise_boxes(std::vector<size_t>& vec)
{
	// set each value of the vector, starting at 0, and incrementing by 1
	std::iota(vec.begin(), vec.end(), 0);
	// shufle box numbers in boxes vector
	// auto rng = std::default_random_engine{0};time(0)
	// auto rng = std::default_random_engine{time(0)};

	// // Initialise. Do this once (not for every random number).
	// std::random_device rd;
	// std::mt19937_64 gen(rd());

	// /* This is where you define the number generator for unsigned long long: */
	// std::uniform_int_distribution<unsigned long long> dis;

	// https://www.youtube.com/watch?v=oW6iuFbwPDg&ab_channel=TopShelfTechnology

	std::random_device rd;
	// std::mt19937 mt(rd());
	// std::uniform_real_distribution<size_t> dist(1, 10);

	// for (int i = 0; i < 16; ++i)
	//     std::cout << dist(mt) << "\n";

	// std::shuffle(vec.begin(), vec.end(), dist(mt));
	std::ranges::shuffle(vec, rd);
}

void initialise_prisoners(std::vector<Prisoner*>& vec)
{
	for (size_t i{}; i < num_prisoners; ++i)
	{
		//vec.push_back(Prisoner{ i, num_prisoners, max_search_boxes });

		//Prisoner p{ i, num_prisoners, max_search_boxes };
		//vec.push_back(p);


		Prisoner* p = new Prisoner{ i, num_prisoners, max_search_boxes };
		vec.push_back(p);
		//delete p;
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
	//std::cout << "searching prisoner num: " << prisoner.get_number() << std::endl;
	bool found{ false };
	//std::cout << "Before search..... " << prisoner->still_boxes_left() << std::endl;
	while (!found && prisoner->still_boxes_left())
	{
		//std::cout << "prisoner num: " << prisoner->get_number() << ", boxes searched: " << prisoner->get_boxes_searched() << ", searching box " << prisoner->get_box_to_search();
		size_t num_in_box = boxes.at(prisoner->get_box_to_search());
		//std::cout << ", num in box: " << num_in_box;
		found = prisoner->search_box(num_in_box);
		//std::cout << ", found: " << found << std::endl;

		//if (found)
			//std::cout << prisoner->get_number() << "  FOUND ------ " << prisoner->get_number() << std::endl;

		//std::cout << !found << " " << prisoner.still_boxes_left() << std::endl;
	}

	return found;

	//std::cout << std::endl;

	// select box at current prisoners number

	// see if the number in that box == prisoners number

	// next box
}