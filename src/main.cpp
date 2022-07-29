#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include "command_handler/command_handler.h"
#include "console_table/console_table.h"

struct command_description
{
    std::string name;
    std::string body;
    std::string description;
};

std::vector<table_header> table_header_array = {
    {
        "command",
        22,
    },
    {
        "example",
        60,
    },
    {
        "description",
        60,
    },
};

std::vector<std::vector<table_column>> description_commands = {

    {
        {"add"},
        {"add {name} {descritpion} {tag}"},
        {"add new task to the list"},
    },
    {
        {"update"},
        {"update {name_todo}"},
        {"update description for current task"},
    },
    {
        {"delete"},
        {"delete {name_todo}"},
        {"delete all info about current task"},
    },
};

int main()
{
    while (true)
    {
        console_table new_table_command = console_table();
        new_table_command.set_table_header(table_header_array);
        new_table_command.set_table_columns(description_commands);
        new_table_command.draw_all_table();
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
