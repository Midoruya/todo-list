#pragma once
#include <string>
#include <vector>
class structure_TODO
{
public:

	std::string name;
	std::string description;
	std::string categories;
	bool is_complete;

	structure_TODO(std::string new_name, std::string new_description, std::string new_categories);

	void update_this_task(std::string new_description, std::string new_categories);

	void complete_this_task();
};

