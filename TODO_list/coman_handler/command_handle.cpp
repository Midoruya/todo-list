#define _CRT_SECURE_NO_WARNINGS

#include "command_handle.h"
#include "../other.h"
#include <fstream>
#include <Windows.h>

void command_handle::handle_new_command()
{
	std::string input_comman = "";
	getline(std::cin, input_comman);
	this->command_argument = split(input_comman);
}

void command_handle::search_all_task()
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
			this->task_list.insert({ file_info[0], structure_TODO(file_info[0],file_data,file_info[1],file_info[2] == "no" ? false : true) });
			fin.close();
		} while (NULL != FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
}

void command_handle::handling_command_add()
{
	if (this->command_argument[0] == "add")
	{
		if (this->command_argument.size() != 4)
		{
			printf("add has too samll or too many parametrs");
			return;
		}
		std::string name = this->command_argument[1];
		auto find_task_by_name = this->task_list.find(name.c_str());
		if (find_task_by_name != this->task_list.end())
		{
			printf("task : %s is already there\n", name.c_str());
		}
		else
		{
			std::string description = this->command_argument[2];
			std::string tag = this->command_argument[3];
			structure_TODO new_todo = structure_TODO(name, description, tag);

			char construct_file_name[0x248];
			sprintf(construct_file_name, "%s %s no.task", name.c_str(), tag.c_str());
			std::ofstream new_file_for_task (construct_file_name);
			new_file_for_task << description << std::endl;
			new_file_for_task.close();

			printf("successful crete new task : %s\n", name.c_str());
		}
	}
}

void command_handle::handling_command_update()
{
	if (this->command_argument[0] == "update")
	{
		if (this->command_argument.size() != 3)
		{
			printf("update has too samll or too many parametrs");
			return;
		}
		std::string name = this->command_argument[1];
		std::string description = this->command_argument[2];
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
}

void command_handle::handling_command_delete()
{
	if (this->command_argument[0] == "delete")
	{
		if (this->command_argument.size() != 2)
		{
			printf("delete has too samll or too many parametrs");
			return;
		}
		std::string name = this->command_argument[1];
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
}

void command_handle::handling_command_select()
{
	if (this->command_argument[0] == "select")
	{
		std::string second_parametr = this->command_argument[1];
		if (second_parametr == "*")
		{
			for (auto var : task_list)
			{
				printf("task : %s | %s | %s\n", var.second.name.c_str(), var.second.description.c_str(), var.second.is_complete ? "yes" : "no");
			}
		}
		else if (second_parametr == "where")
		{
			for (int i = 1; i++; i < this->command_argument.size())
			{
				std::string parametr = this->command_argument[i];
				std::string equal = this->command_argument[i + 1];
				std::string argument = this->command_argument[i + 2];
				bool is_and = i + 3 > this->command_argument.size() - 1 ? false : this->command_argument[i + 4] == "and" ? true : false ;
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
}

void command_handle::handling_command_done()
{
	if (this->command_argument[0] == "done")
	{
		if (this->command_argument.size() != 2)
		{
			printf("done has too samll or too many parametrs");
			return;
		}
		std::string name = this->command_argument[1];
		auto find_task_by_name = task_list.find(name.c_str());
		if (find_task_by_name != task_list.end()) 
		{
			char old_construct_file_name[0x248];
			char new_construct_file_name[0x248];
			sprintf(old_construct_file_name, "%s %s no.task", name.c_str(), find_task_by_name->second.categories.c_str());
			sprintf(new_construct_file_name, "%s %s yes.task", name.c_str(), find_task_by_name->second.categories.c_str());
			rename(old_construct_file_name, new_construct_file_name);
			printf("successful complete task : %s\n", name.c_str());

		}
		else printf("task : %s not found\n", name.c_str());
	}
}
