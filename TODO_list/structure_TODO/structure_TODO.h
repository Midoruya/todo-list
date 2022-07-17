#pragma once
#include <string>
#include <vector>
#include <chrono>

class structure_TODO
{
public:

	std::string name;
	std::string description;
	std::string categories;
	bool is_complete;

	structure_TODO(std::string new_name, std::string new_description, std::string new_categories, bool new_is_complete = false)
	{
		const auto date_time_now = std::chrono::system_clock::now();
		this->name = new_name;
		this->description = new_description;
		this->categories = new_categories;
		this->is_complete = new_is_complete;
	}
};

