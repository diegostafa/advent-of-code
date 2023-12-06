#include "../../utils/aoc-utils.cpp"
#include <ranges>

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
    auto sum = 0;

    for (auto&& n : aoc_utils::read_file_lines("input/day-01/input.txt") | std::views::transform(get_number))
        sum += n;

    std::cout << sum << std::endl;
}