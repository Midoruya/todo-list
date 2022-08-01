#include "command_handler.h"
#include "../utilities/utilities.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <ctime>

void command_handler::handle_new_command()
{
    std::string input_comman = "";
    getline(std::cin, input_comman);
    this->command_argument = utilities::splite_string(input_comman);
}

void command_handler::search_all_task()
{
    std::filesystem::path current_directory = std::filesystem::current_path();
    current_directory.append(current_directory.string() + "/" + this->save_in_folder);
    if (std::filesystem::exists(current_directory.string()) == false)
        std::filesystem::create_directory(current_directory.string());
    this->create_new_task("test", "first", "asdasdasdasdadasdasd");
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

void command_handler::create_new_task(std::string name, std::string tag, std::string description)
{
    std::time_t get_data_time_now = std::time(NULL);
    std::tm *local_time = std::localtime(&get_data_time_now);
    std::string date_time_str = "";
    date_time_str.append(std::to_string(1900 + local_time->tm_year));
    date_time_str.append("-");
    date_time_str.append(std::to_string(1 + local_time->tm_mon));
    date_time_str.append("-");
    date_time_str.append(std::to_string(local_time->tm_mday));
    std::filesystem::path current_directory = std::filesystem::current_path();
    current_directory.append(current_directory.string() + "/" + this->save_in_folder + "/");
    char new_filename[0x248];
    sprintf_s(new_filename, "%s %s %s %s%s", name.c_str(), date_time_str.c_str(), tag.c_str(), "no", this->file_format.c_str());
    current_directory.append(new_filename);

    std::ofstream new_file(current_directory);
    if (!new_file.is_open())
        std::cout << "[Error] open and write in file" << std::endl;
    new_file << description << std::endl;
    new_file.close();
}