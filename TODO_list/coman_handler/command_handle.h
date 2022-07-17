#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "../structure_TODO/structure_TODO.h"

class command_handle
{

public:

	std::vector<std::string> command_argument;
	std::map<std::string, structure_TODO> task_list;

	command_handle() {};

	void handle_new_command();

	void search_all_task();

	void handling_command_add();
	void handling_command_update();
	void handling_command_delete();
	void handling_command_select();
	void handling_command_done();

private:

};

