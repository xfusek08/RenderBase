#pragma once

#include <string>
#include <vector>

#include <functional>

namespace rb {
    std::string implode(const std::vector<std::string>& strings, const std::string& glue = "");
    
    template<class T, class Func>
    std::vector<T> map(const std::vector<T>& array, Func op)
    {
        std::vector<T> res;
        std::transform(array.begin(), array.end(), std::back_inserter(res), op);
        return std::move(res);
    }
}
