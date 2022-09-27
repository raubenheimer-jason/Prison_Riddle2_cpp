#ifndef _PRISONER_H_
#define _PRISONER_H_

#include <cstdint> // size_t

class Prisoner
{
private:
	const size_t number;
	const size_t num_prisoners;
	const size_t max_search_boxes;
	size_t boxes_searched;
	bool found_number;
	size_t box_to_search;
	bool is_number_found(const size_t num_in_box);

public:
	Prisoner(const size_t number, const size_t num_prisoners, const size_t max_search_boxes);
	bool search_box(const size_t num_in_box);
	bool still_boxes_left();
	void display() const;
	const size_t get_box_to_search() const;
	const size_t get_number() const;
	const size_t get_boxes_searched() const;
};

#endif // _PRISONER_H_