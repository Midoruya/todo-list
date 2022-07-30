#include "console_table.h"
#include <vector>
#include <iostream>
#include <algorithm>

void console_table::set_table_header(std::vector<table_header> new_header_list)
{
    this->header_list = new_header_list;
}

void console_table::set_table_columns(std::vector<std::vector<table_column>> new_columns_list)
{
    this->column_list = new_columns_list;
}

void console_table::draw_table_header()
{
    for (int g = 0; g < 3; g++)
    {
        for (int i = 0; i < this->header_list.size(); i++)
        {
            int calculae_stacing = this->header_list[i].column_size / 2 - this->header_list[i].header.size() / 2;
            char get_spacing_word = g != 1 ? '-' : ' ';
            if (i == 0)
                std::printf("|");

            std::printf("%s", std::string(calculae_stacing, get_spacing_word).c_str());
            if (g == 1)
                std::printf("%s", this->header_list[i].header.c_str());
            else
                std::printf("%s", std::string(this->header_list[i].header.size(), '-').c_str());
            std::printf("%s", std::string(calculae_stacing, get_spacing_word).c_str());
            std::printf("|");
        }
        std::printf("\n");
    }
}

void console_table::draw_table_columns()
{
    for (int i = 0; i < this->column_list.size(); i++)
    {
        for (int g = 0; g < this->column_list[i].size(); g++)
        {
            int calculae_stacing = this->header_list[g].column_size / 2 - this->column_list[i][g].column_data.size() / 2;
            if (g == 0)
                std::printf("|");

            std::printf("%s", std::string(calculae_stacing, ' ').c_str());
            std::printf("%s", this->column_list[i][g].column_data.c_str());
            std::printf("%s", this->column_list[i][g].column_data.size() & 1 ? "" : " ");
            std::printf("%s", std::string(calculae_stacing, ' ').c_str());
            std::printf("|");
        }
        std::printf("\n");
    }
    for (int i = 0; i < this->header_list.size(); i++)
    {
        int calculae_stacing = this->header_list[i].column_size / 2 - this->header_list[i].header.size() / 2;
        if (i == 0)
            std::printf("|");

        std::printf("%s", std::string(calculae_stacing, '-').c_str());
        std::printf("%s", std::string(this->header_list[i].header.size(), '-').c_str());
        std::printf("%s", std::string(calculae_stacing, '-').c_str());
        std::printf("|");
    }
    std::printf("\n");
}

void console_table::draw_all_table()
{
    this->draw_table_header();
    this->draw_table_columns();
}
