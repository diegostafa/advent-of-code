#include "../../utils/aoc-utils.cpp"
#include <numeric>
#include <ranges>

int
main()
{
    auto get_number = [](const auto& s)
    {
        auto n1 = *std::find_if(s.begin(), s.end(), isdigit) - '0';
        auto n2 = *std::find_if(s.rbegin(), s.rend(), isdigit) - '0';
        return n1 * 10 + n2;
    };

    auto numbers = aoc_utils::read_file_lines("src/day-01/input.txt") | std::views::transform(get_number);
    std::cout << std::accumulate(numbers.begin(), numbers.end(), 0) << std::endl;
}