#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

namespace aoc_utils
{
    std::vector<std::string>
    split_string(const std::string& str, const std::string& delimiter)
    {
        size_t                   pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string              token;
        std::vector<std::string> res;

        while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos)
        {
            token     = str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(str.substr(pos_start));
        return res;
    }

    std::vector<std::string>
    read_file_lines(const std::string& path)
    {
        std::ifstream            file(path);
        std::string              line;
        std::vector<std::string> lines;

        if (!file)
            std::cerr << "err reading " << path << std::endl;

        while (std::getline(file, line))
            lines.push_back(line);

        return lines;
    }

    std::string
    read_file(const std::string& path)
    {
        std::ifstream ifs(path);
        return std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    }
}