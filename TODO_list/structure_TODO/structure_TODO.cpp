#include "structure_TODO.h"
#include <format>
#include <chrono>

structure_TODO::structure_TODO(std::string new_name, std::string new_description, std::string new_categories)
{
	const auto date_time_now = std::chrono::system_clock::now();
	this->name = new_name;
	this->description = new_description;
	this->categories = new_categories;
	this->is_complete = false;
}

void structure_TODO::update_this_task(std::string new_description, std::string new_categories)
{
	this->description = new_description.c_str();
	this->categories = new_categories.c_str();
}

void structure_TODO::complete_this_task()
{
	this->is_complete = true;
}
