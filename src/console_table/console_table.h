#include <vector>
#include <string>

struct table_header
{
    std::string header;
    int column_size;
};

struct table_column
{
    std::string column_data;
};

class console_table
{
public:
    console_table() {}

    void set_table_header(std::vector<table_header> new_header_list);

    void set_table_columns(std::vector<std::vector<table_column>> new_columns_list);

    void draw_table_header();
    void draw_table_columns();

    void draw_all_table();

private:
    std::vector<table_header> header_list;
    std::vector<std::vector<table_column>> column_list;
};
