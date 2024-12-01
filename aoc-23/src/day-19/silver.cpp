#include "../../utils/aoc-utils.cpp"
#include <variant>

struct branch
{
    std::string body;

    bool
    isLinked() const
    {
        return body != "A" && body != "R";
    }
};

struct if_case : public branch
{
    char var;
    char op;
    int  val;

    bool
    isGreater() const
    {
        return op == '>';
    }

    bool
    isTrue(int valVar) const
    {
        return isGreater() && valVar > val || !isGreater() && valVar < val;
    }
};

struct else_case : public branch
{
};

int
ratingValue(const auto& rating)
{
    int val = 0;
    for (auto&& [k, v] : rating)
        val += v;
    return val;
}

std::string
validate(auto& workflows, auto& rating, const auto& conditions)
{
    auto& [ifvec, elseBranch] = conditions;

    for (auto&& cond : ifvec)
        if (rating.count(cond.var) && cond.isTrue(rating[cond.var]))
            return cond.isLinked() ? validate(workflows, rating, workflows[cond.body]) : cond.body;

    return elseBranch.isLinked() ? validate(workflows, rating, workflows[elseBranch.body]) : elseBranch.body;
}

int
main()
{
    auto add_workflow = [](auto& workflows, auto s)
    {
        s.pop_back();
        auto keyAndConditions = aoc_utils::split_string(s, "{");

        auto key    = keyAndConditions[0];
        auto conds  = aoc_utils::split_string(keyAndConditions[1], ",");
        auto noCond = conds.back();
        conds.pop_back();

        auto ifVec = std::vector<if_case>();
        for (auto&& c : conds)
        {
            auto parts = aoc_utils::split_string(c, ":");

            auto var = parts[0].front();
            parts[0].erase(parts[0].begin());

            auto op = parts[0].front();
            parts[0].erase(parts[0].begin());

            auto val = aoc_utils::to_int(parts[0]);
            ifVec.push_back(if_case{parts[1], var, op, val});
        }

        workflows[key] = std::make_pair(ifVec, else_case{noCond});
    };

    auto parse_rating = [](auto s)
    {
        s.pop_back();
        s.erase(s.begin());
        auto parts   = aoc_utils::split_string(s, ",");
        auto ratings = std::unordered_map<char, int>();

        for (auto&& p : parts)
        {
            auto keyVal           = aoc_utils::split_string(p, "=");
            ratings[keyVal[0][0]] = aoc_utils::to_int(keyVal[1]);
        }
        return ratings;
    };

    auto input   = aoc_utils::split_string(aoc_utils::read_file("src/day-19/input.txt"), "\n\n");
    auto ratings = aoc_utils::split_line(input[1]) | std::views::transform(parse_rating);

    auto workflows = std::unordered_map<std::string, std::pair<std::vector<if_case>, else_case>>();
    for (auto&& wl : aoc_utils::split_line(input[0]))
        add_workflow(workflows, wl);

    int sum = 0;
    for (auto&& rating : ratings)
    {
        auto res = validate(workflows, rating, workflows["in"]);
        sum += res == "A" ? ratingValue(rating) : 0;
    }

    std::cout << sum << std::endl;
}