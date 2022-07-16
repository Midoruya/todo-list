#include "structure_TODO.h"
#include <format>
#include <chrono>

void structure_TODO::update_this_task(std::string new_description, std::string new_categories)
{
	this->description = new_description.c_str();
	this->categories = new_categories.c_str();
}

void structure_TODO::complete_this_task()
{
	this->is_complete = true;
}
