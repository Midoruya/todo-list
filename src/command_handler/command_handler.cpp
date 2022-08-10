#include "command_handler.h"
#include "../utilities/utilities.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <ctime>

std::string task_construct::get_file_name()
{
    std::string filename;
    filename.append(this->name);
    filename.append(" ");
    filename.append(this->date);
    filename.append(" ");
    filename.append(this->tag);
    filename.append(" ");
    filename.append(this->is_complete ? "yes" : "no");
    filename.append(this->file_format);
    return filename;
}

void command_handler::handle_new_command()
{
    std::string input_comman = "";
    std::printf("Please inter you command: \n");
    getline(std::cin, input_comman);
    this->command_argument = utilities::splite_string(input_comman);
    this->add_task();
    this->delete_task();
}

void command_handler::add_task()
{
    std::vector<std::string> command = this->command_argument;

    if (command[0] != "add")
        return;

    if (command.size() != 4)
    {
        std::printf("You don't enter all the arguments of this command or you enter extra arguments\n");
        return;
    }

    std::time_t get_data_time_now = std::time(NULL);
    std::tm *local_time = std::localtime(&get_data_time_now);

    std::string date_time_str = "";
    date_time_str.append(std::to_string(1900 + local_time->tm_year));
    date_time_str.append("-");
    date_time_str.append(std::to_string(1 + local_time->tm_mon));
    date_time_str.append("-");
    date_time_str.append(std::to_string(local_time->tm_mday));

    task_construct new_task = task_construct(command[1], command[2], date_time_str, command[3], false);

    this->create_new_task_file(new_task);
}

void command_handler::search_all_task()
{
    std::filesystem::path current_directory = std::filesystem::current_path();
    current_directory.append(current_directory.string() + "/" + this->save_in_folder);
    if (std::filesystem::exists(current_directory.string()) == false)
        std::filesystem::create_directory(current_directory.string());
    for (const auto &task : std::filesystem::directory_iterator(current_directory.string()))
    {
        std::string filename = task.path().stem().string();
        std::vector<std::string> splite_filename = utilities::splite_string(filename);
        bool is_complete = splite_filename[3] == "no" ? false : true;
        std::string task_name = splite_filename[0];
        std::string task_tag = splite_filename[2];
        std::string task_date = splite_filename[1];
        std::string task_description = "";
        std::fstream new_file(task.path());
        std::getline(new_file, task_description);
        task_construct new_task = task_construct(task_name, task_description, task_date, task_tag, is_complete);
        this->task_list.push_back(new_task);
    }
}

void command_handler::create_new_task_file(task_construct task)
{
    std::string current_directory = this->get_work_directory();
    current_directory.append(task.get_file_name());
    std::ofstream new_file(current_directory);
    if (!new_file.is_open())
        std::cout << "[Error] open and write in file" << std::endl;
    new_file << task.description.c_str() << std::endl;
    new_file.close();
}

std::string command_handler::get_work_directory()
{
    std::filesystem::path current_directory = std::filesystem::current_path();
    current_directory.append(current_directory.string() + "/" + this->save_in_folder + "/");
    return current_directory.string();
}

void command_handler::delete_task()
{
    std::vector<std::string> command = this->command_argument;

    if (command[0] != "delete")
        return;

    if (command.size() != 2)
    {
        std::printf("You don't enter all the arguments of this command or you enter extra arguments\n");
        return;
    }

    std::string task_name = command[1];

    for (task_construct task : this->task_list)
    {
        if (task.name == task_name)
            std::remove(std::string(this->get_work_directory() + task.get_file_name()).c_str());
    }
}