#include "../../utils/aoc-utils.cpp"
#include <unordered_map>

int
main()
{
    std::unordered_map<std::string, std::pair<std::string, std::string>> idToNext;

    auto parse_line = [&idToNext](const auto& s)
    {
        auto split = aoc_utils::split_string(s, " = ");
        auto id    = split[0];
        auto rest  = aoc_utils::split_string(split[1], ", ");
        auto sx    = rest[0];
        auto dx    = rest[1];

        sx.erase(sx.begin());
        dx.erase(dx.end() - 1);
        idToNext[id] = {sx, dx};
    };

    auto input        = aoc_utils::read_file_lines("input/day-08/input.txt");
    auto instructions = input[0];
    std::for_each(input.begin() + 2, input.end(), parse_line);

    auto follow_map = [&idToNext, &instructions](const std::string& start)
    {
        int64_t steps       = 0;
        int64_t iter        = 0;
        auto    pos         = start;
        auto    reset_steps = [&steps, &iter]()
        {steps = 0; iter++; };

        while (pos != "ZZZ")
        {
            if (steps == instructions.size())
                reset_steps();

            pos = (instructions[steps++] == 'L') ? pos = idToNext[pos].first : pos = idToNext[pos].second;
        }
        return steps + steps * iter;
    };

    std::cout << follow_map("AAA") << std::endl;
}
