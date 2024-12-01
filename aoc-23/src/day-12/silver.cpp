#include "../../utils/aoc-utils.cpp"
#include <chrono>
#include <numeric>
#include <set>
#include <thread>
#include <tuple>
#include <unordered_set>

bool
can_satisfy_constraints(const auto& str, auto maxDmg)
{
    int currDmg     = 0;
    int currUnknown = 0;

    for (auto&& c : str)
    {
        if (c == '#')
            currDmg++;
        else if (c == '?')
            currUnknown++;
    }

    if (currDmg > maxDmg)
        return false;

    if (currDmg + currUnknown < maxDmg)
        return false;

    return true;
}

bool
satisfies_constraints(const auto& springs, const auto& constraints)
{
    int  pos     = 0;
    int  dmgReps = 0;
    auto size    = springs.size();

    for (int i = 0; i < size; ++i)
    {
        auto c = springs[i];

        if (dmgReps == 0 && c != '#')
            continue;

        if (c == '#')
            dmgReps++;
        else
        {
            if (dmgReps != constraints[pos])
                return false;

            dmgReps = 0;
            pos++;
        }
    }

    if (dmgReps == 0 && pos == constraints.size())
        return true;

    if (dmgReps != 0 && pos == constraints.size() - 1 && dmgReps == constraints[pos])
        return true;

    return false;
}

int
count_arrangements(auto springs, const auto& unknowns, const auto& constraints, auto& maxDmg, auto varLeft)
{
    if (varLeft == 0)
        return satisfies_constraints(springs, constraints) ? 1 : 0;

    if (!can_satisfy_constraints(springs, maxDmg))
        return 0;

    auto u        = unknowns[varLeft - 1];
    springs[u]    = '#';
    auto totLeft  = count_arrangements(springs, unknowns, constraints, maxDmg, varLeft - 1);
    springs[u]    = '.';
    auto totRight = count_arrangements(springs, unknowns, constraints, maxDmg, varLeft - 1);

    return totLeft + totRight;
}

int
main()
{
    auto parse_line = [](const auto& s)
    {
        auto record      = aoc_utils::split_space(s);
        auto springs     = record[0];
        auto dmgInfo     = aoc_utils::split_string(record[1], ",");
        auto unknowns    = std::vector<int>();
        auto constraints = std::vector<int>();

        for (int i = 0; i < springs.size(); i++)
            if (springs[i] == '?')
                unknowns.push_back(i);

        std::transform(dmgInfo.begin(), dmgInfo.end(), std::back_inserter(constraints), aoc_utils::to_int);
        auto maxDmg = std::accumulate(constraints.begin(), constraints.end(), 0);

        return std::make_tuple(springs, unknowns, constraints, maxDmg);
    };

    auto input = aoc_utils::read_file_lines("src/day-12/input.txt") | std::views::transform(parse_line);

    int sum = 0;
    for (auto&& [springs, unknowns, constraints, maxDmg] : input)
        sum += count_arrangements(springs, unknowns, constraints, maxDmg, unknowns.size());

    std::cout << sum << std::endl;
}