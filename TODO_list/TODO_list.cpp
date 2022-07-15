// TODO_list.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include "structure_TODO/structure_TODO.h"
#include <map>

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
	std::stringstream ss(strToSplit);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (std::getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}

std::map<std::string ,structure_TODO> task_list;

int main()
{
	while (true)
	{
		printf("all task\n");
		std::string input_comman = "";
		printf("Command list :\nadd : add new task to the list\nupdate {name_todo} : update description for current task\ndelete {name_todo} : delete all info about current task\n");
		printf("Please inter you command: \n");
		getline(std::cin, input_comman);
		std::vector<std::string> divided_commands_on_atoms = split(input_comman, ' ');
		std::string header_query = divided_commands_on_atoms[0];
		int header_query_size = divided_commands_on_atoms.size();
		if (header_query == "add") 
		{
			if (header_query_size != 4) 
			{
				printf("add has too samll or too many parametrs");
				goto update_cmd;
			}
			std::string name = divided_commands_on_atoms[1];
			auto find_task_by_name = task_list.find(name.c_str());
			if (find_task_by_name != task_list.end())
			{
				printf("task : %s is already there\n", name.c_str());
			}
			else
			{
				std::string description = divided_commands_on_atoms[2];
				std::string tag = divided_commands_on_atoms[3];
				structure_TODO new_todo = structure_TODO(name, description, tag);
				task_list.insert({ name,new_todo });
				printf("successful crete new task : %s\n", name.c_str());
			}
		}
		else if (header_query == "update") 
		{
			if (header_query_size != 3) 
			{
				printf("update has too samll or too many parametrs");
				goto update_cmd;
			}
			std::string name = divided_commands_on_atoms[1];
			std::string description = divided_commands_on_atoms[2];
			auto find_task_by_name = task_list.find(name.c_str());
			if (find_task_by_name != task_list.end()){
				find_task_by_name->second.update_this_task(description.c_str(), "");
				printf("successful update task : %s\nnew description : %s", name.c_str(), description.c_str());

			}
			else  printf("task : %s not found\n", name.c_str());
		}
		else if (header_query == "delete") 
		{
			if (header_query_size != 2) 
			{
				printf("delete has too samll or too many parametrs");
				goto update_cmd;
			}
			std::string name = divided_commands_on_atoms[1];
			auto find_task_by_name = task_list.find(name.c_str());
			if (find_task_by_name != task_list.end()) 
			{
				task_list.erase(find_task_by_name);
				printf("successful delete task : %s\n", name.c_str());

			}
			else  printf("task : %s not found\n", name.c_str());
		}
		else if (header_query == "done") 
		{
			if (header_query_size != 2) 
			{
				printf("done has too samll or too many parametrs");
				goto update_cmd;
			}
			std::string name = divided_commands_on_atoms[1];
			auto find_task_by_name = task_list.find(name.c_str());
			if (find_task_by_name != task_list.end()) 
			{
				find_task_by_name->second.complete_this_task();
				printf("successful complete task : %s\n", name.c_str());

			}
			else  printf("task : %s not found\n", name.c_str());
		}
		else if (header_query == "select") 
		{
			std::string second_parametr = divided_commands_on_atoms[1];
			if (second_parametr == "*")
			{
				for (auto var : task_list)
				{
					printf("task : %s | %s | %s\n", var.second.name.c_str(), var.second.description.c_str(), var.second.is_complete ? "yes" : "no");
				}
			}
			else if (second_parametr == "where")
			{
				for (int i = 1; i++; i < divided_commands_on_atoms.size())
				{
					std::string parametr = divided_commands_on_atoms[i];
					std::string equal = divided_commands_on_atoms[i + 1];
					std::string argument = divided_commands_on_atoms[i + 2];
					bool is_and = i + 3 > divided_commands_on_atoms.size() - 1 ? false : divided_commands_on_atoms[i + 4] == "and" ? true : false ;
					if (parametr == "name")
					{
						if (equal == "==")
						{
							auto find_task_by_name = task_list.find(argument.c_str());
							if (find_task_by_name != task_list.end())
							{
								printf("task : %s | %s | %s\n", find_task_by_name->second.name.c_str(), find_task_by_name->second.description.c_str(), find_task_by_name->second.is_complete ? "yes" : "no");
							}
							else
							{
								printf("This task not found");
							}
						}
						else printf("segmentation error on select query:)\nPlese input correct command");
					}
					else if (parametr == "description")
					{
						if (equal == "==")
						{
							for (auto var : task_list)
							{
								if (var.second.description == argument)
									printf("task : %s | %s | %s\n", var.second.name.c_str(), var.second.description.c_str(), var.second.is_complete ? "yes" : "no");
							}
						}
						else printf("segmentation error on select query:)\nPlese input correct command");
					}
					else if (parametr == "status")
					{
						if (equal == "==")
						{
							for (auto var : task_list)
							{
								bool is_comp = argument == "yes" ? true : false;
								if (var.second.is_complete == is_comp)
									printf("task : %s | %s | %s\n", var.second.name.c_str(), var.second.description.c_str(), var.second.is_complete ? "yes" : "no");
							}
						}
						else printf("segmentation error on select query:)\nPlese input correct command");
					}
					if (!is_and)
						break;
				}
			}
			else 
			{
				printf("segmentation error on select query:)\nPlese input correct command");
			}
		}
		else
		{
			printf("segmentation error :)\nPlese input correct command");
		}

		update_cmd:
		system("pause");
		system("cls");
	}
}