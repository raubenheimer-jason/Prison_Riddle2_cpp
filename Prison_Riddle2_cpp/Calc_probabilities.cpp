#include "Calc_probabilities.hpp"

/*
Calculate the probability of all prisoners finding their number if
they each search using the proposed technique

Longest loop:		1 -> 2 -> 3 -> .... -> 100
Random length loop: 5 -> 99 -> 51 -> ... -> 53

How many permutations could you have?
For the first box: 100 options to choose from
For the second box: 99 options to choose from
Third box: 98...
The last box: 1 option left
-> total permutations = 100*99*98*97*...*1
--> This is the factorial

Therefore we have 100! permutations
-> 100! different ways that you could create a loop of 100 boxes

BUT... some loops repeat.
E.g. 1 -> 2 -> 3 -> 4 -> ... -> 100 -> (back to 1)
		is the same as: 2 -> 3 -> 4 -> ... -> 100 -> 1 -> (back to 2)
So the loop above (100 boxes) can be written 100 different ways, but it is still the same loop

Therefore: the total number of unique loops for 100 boxes is: 100!/100
So... what is the probability that any random arrangement of 100 boxes will contain a loop of length 100:
P(L=100) = # unique loops / total permutations
		 = (100!/100)     / 100!
		 = 1/100
Therefore there is a 1% chance that any random arrangement of 100 boxes will contain a loop of length 100.

This is a general result.
P(L=99) = 1/99, P(L=98) = 1/98, etc.

Therefore the probability that there is a loop longer than 50 (i.e. fail)...
P(L>50) = 1/51 + 1/52 + 1/53 + ... + 1/100
		= 0.69

Therefore there is a 69% chance of failure... or a 31% chance of success...

*/
double loop_probability(const size_t num_boxes)
{
	double p_fail{};
	for (size_t i{ 51 }; i <= num_boxes; ++i)
		p_fail += 1.0 / i;
	return 1.0 - p_fail;
}

/*
Calculate the probability of all prisoners finding their number if
they each search randomly
*/
double random_probability(const size_t num_boxes, const size_t max_search_boxes, const size_t num_prisoners)
{
	double single_prisoner_probability{ static_cast<double>(max_search_boxes) / num_boxes };
	double rand_probability{ pow(single_prisoner_probability, num_prisoners) };
	return rand_probability;

}