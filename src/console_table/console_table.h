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

    /**
     * @brief Set the table header array
     *
     * @param new_header_list New table header array
     */
    void set_table_header(std::vector<table_header> new_header_list);

    /**
     * @brief Set the table columns array
     *
     * @param new_columns_list New table column array
     */
    void set_table_columns(std::vector<std::vector<table_column>> new_columns_list);

    /**
     * @brief This function is drawing all table. Column and header.
     *
     */
    void draw_all_table();

private:
    /**
     * @brief This function is drawing only header line in table
     *
     */
    void draw_table_header();

    /**
     * @brief This function is drawing only all columnsin the table
     *
     */
    void draw_table_columns();

    std::vector<table_header> header_list;
    std::vector<std::vector<table_column>> column_list;
};
