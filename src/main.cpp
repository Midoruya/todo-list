#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <sstream>
#include "command_handler/command_handler.h"
#include <iomanip>

struct command_description
{
    std::string name;
    std::string body;
    std::string description;
};

std::vector<command_description> description_commands = {
    {
        "command",
        "example",
        "description",
    },
    {
        "add",
        "add {name} {descritpion} {tag}",
        "add new task to the list",
    },
    {
        "update",
        "update {name_todo}",
        "update description for current task",
    },
    {
        "delete",
        "delete {name_todo}",
        "delete all info about current task",
    },
};

int main()
{
    while (true)
    {
        auto print_command_description = [](command_description description)
        {
            std::string print = "";
            std::string table_name = description.name;
            std::string table_description = description.description;
            std::string table_body = description.body;
            int first_column_buffer = 22;
            int second_column_buffer = 60;
            int third_column_buffer = 60;
            std::cout << "|"
                      << std::string(first_column_buffer / 2 - table_name.size() / 2, ' ')
                      << table_name
                      << std::string(first_column_buffer / 2 - table_name.size() / 2, ' ')
                      << (table_name.size() & 1 ? "" : " ")
                      << "|"
                      << std::string(second_column_buffer / 2 - table_description.size() / 2, ' ')
                      << table_description
                      << std::string(second_column_buffer / 2 - table_description.size() / 2, ' ')
                      << (table_description.size() & 1 ? "" : " ")
                      << "|"
                      << std::string(third_column_buffer / 2 - table_body.size() / 2, ' ')
                      << table_body
                      << std::string(third_column_buffer / 2 - table_body.size() / 2, ' ')
                      << (table_body.size() & 1 ? "" : " ")
                      << "|"
                      << std::endl;
        };
        std::for_each(description_commands.begin(), description_commands.end(), print_command_description);
        std::printf("Please inter you command: \n");
        command_handler handler_command = command_handler();
        handler_command.handle_new_command();
        auto test = [](std::string str)
        { std::printf("%s\n", str.c_str()); };
        std::for_each(handler_command.command_argument.begin(), handler_command.command_argument.end(), test);
#ifdef _WIN32
        system("pause");
        system("cls");
#else
        system("read");
        system("clear");
#endif
    }

    return 0;
}
