#include "../../utils/aoc-utils.cpp"
#include <numeric>

int
main()
{
    auto input = aoc_utils::split_string(aoc_utils::read_file("src/day-15/input.txt"), ",");
    auto hash  = [](auto acc, const auto& str)
    {
        auto hashOp = [](auto acc, auto c)
        { return ((acc + c) * 17) % 256; };

        return acc + std::accumulate(str.begin(), str.end(), 0, hashOp);
    };
    auto sum = std::accumulate(input.begin(), input.end(), 0, hash);
    std::cout << sum << std::endl;
}