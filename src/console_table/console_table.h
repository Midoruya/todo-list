#include <vector>
#include <string>

struct table_header
{
    std::string header;
    int column_size;
};

class console_table
{
public:
    console_table(std::vector<table_header> all_headers);
private:
    std::vector<table_header> header_list;
};
