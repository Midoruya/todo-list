#include "command_handler.h"
#include "../utilities.h"
#include <iostream>

void command_handler::handle_new_command()
{
    std::string input_comman = "";
    getline(std::cin, input_comman);
    this->command_argument = utilities::splite_string(input_comman);
}