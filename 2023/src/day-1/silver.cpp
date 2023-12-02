#include "../../utils/aoc-utils.cpp"

int
get_number(const std::string& s)
{
    auto n1 = *std::find_if(s.begin(), s.end(), isdigit) - '0';
    auto n2 = *std::find_if(s.rbegin(), s.rend(), isdigit) - '0';
    return n1 * 10 + n2;
}

int
main()
{
    auto lines   = read_file_lines("src/day-1/input.txt");
    auto numbers = map_vector<std::string, int>(lines, get_number);
    auto sum     = 0;

    for (auto&& n : numbers)
        sum += n;

    std::cout << sum << std::endl;
}