#include "../../utils/aoc-utils.cpp"

int
main()
{
    auto parse_line = [](const auto& s)
    { return aoc_utils::split_space(s) | std::views::transform(aoc_utils::to_int64); };

    auto input = aoc_utils::read_file_lines("input/day-09/input.txt") | std::views::transform(parse_line);

    auto extrapolate_value = [](const auto& line)
    {
        auto compute_next_layer = [](const auto& currLine)
        {
            std::vector<int64_t> layer;
            layer.reserve(currLine.size() - 2);

            for (size_t i = 0; i < currLine.size() - 1; i++)
                layer.push_back(currLine[i + 1] - currLine[i]);

            return layer;
        };

        auto vec_all_zero = [](const auto& v)
        {
            for (auto&& e : v)
                if (e != 0)
                    return false;

            return true;
        };

        auto to_vec = [](const auto& l)
        {
            std::vector<int64_t> res;
            for (auto&& e : l)
                res.push_back(e);
            return res;
        };

        std::vector<std::vector<int64_t>> finalPyramid;
        finalPyramid.push_back(to_vec(line));

        while (!vec_all_zero(finalPyramid.back()))
            finalPyramid.push_back(compute_next_layer(finalPyramid.back()));

        int tempSum = 0;
        for (int i = finalPyramid.size() - 1; i >= 1; i--)
            tempSum += finalPyramid[i - 1].back();

        return tempSum;
    };

    int64_t sum = 0;
    for (auto&& line : input)
        sum += extrapolate_value(line);

    std::cout << sum << std::endl;
}
