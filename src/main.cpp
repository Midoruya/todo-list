#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include "command_handler/command_handler.h"
#include "console_table/console_table.h"

std::vector<table_header> table_header_array = {
    {
        "command",
        15,
    },
    {
        "example",
        40,
    },
    {
        "description",
        40,
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
        command_handler handler_command = command_handler();
        handler_command.search_all_task();
        handler_command.handle_new_command();
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
