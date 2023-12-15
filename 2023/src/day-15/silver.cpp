#include "../../utils/aoc-utils.cpp"

int
main()
{
    auto input = aoc_utils::split_string(aoc_utils::read_file("src/day-15/input.txt"), ",");

    auto hash = [](const auto& str)
    {
        int res = 0;
        for (auto&& c : str)
            res = ((res + c) * 17) % 256;
        return res;
    };

    int sum = 0;
    for (auto&& str : input)
        sum += hash(str);

    std::cout << sum << std::endl;
}