#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>  
#include <Windows.h>
#include "structure_TODO/structure_TODO.h"
#include <map>

std::vector<std::string> split(std::string strToSplit, char delimeter = ' ')
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
		int i(0);
		WIN32_FIND_DATA wfd;
		HANDLE hFind = FindFirstFile("C:/Users/Midoruya/Desktop/todo-list/x64/Release/*.task", &wfd);
		if (INVALID_HANDLE_VALUE != hFind)
		{
			do
			{
				std::ifstream fin(&wfd.cFileName[0]);
				if (!fin.is_open()) printf("file %s will not open", &wfd.cFileName[0]);
				int file_name_size = strlen(&wfd.cFileName[0]);
				std::string file_data = "";
				std::getline(fin, file_data);
				for (int i = 0; i < file_name_size; i++) {
					if (i > file_name_size - 6)
						wfd.cFileName[i] = NULL;
				}
				auto file_info = split(&wfd.cFileName[i]);
				task_list.insert({ file_info[0], structure_TODO(file_info[0],file_data,file_info[1],file_info[2] == "no" ? false : true) });
				fin.close();
			} while (NULL != FindNextFile(hFind, &wfd));
			FindClose(hFind);
		}

		printf("all task\n");
		std::string input_comman = "";
		printf("Command list :\nadd : add new task to the list\nupdate {name_todo} : update description for current task\ndelete {name_todo} : delete all info about current task\n");
		printf("Please inter you command: \n");
		getline(std::cin, input_comman);
		std::vector<std::string> divided_commands_on_atoms = split(input_comman);
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

				char construct_file_name[0x248];
				sprintf(construct_file_name, "%s %s no.task", name.c_str(), tag.c_str());
				std::ofstream new_file_for_task (construct_file_name);
				new_file_for_task << description << std::endl;
				new_file_for_task.close();

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
				printf("successful update task : %s\nnew description : %s", name.c_str(), description.c_str());
				char construct_file_name[0x248];
				sprintf(construct_file_name, "%s %s %s.task", name.c_str(), find_task_by_name->second.categories.c_str(), find_task_by_name->second.is_complete ? "yes" : "no");
				std::ofstream new_file_for_task(construct_file_name, std::ios::out | std::ios::trunc);
				new_file_for_task << description << std::endl;
				new_file_for_task.close();
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
				char construct_file_name[0x248];
				sprintf(construct_file_name, "%s %s %s.task", name.c_str(), find_task_by_name->second.categories.c_str(), find_task_by_name->second.is_complete ? "yes" : "no");
				std::remove(construct_file_name);
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
