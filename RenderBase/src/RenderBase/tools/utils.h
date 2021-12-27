#pragma once

#include <string>
#include <vector>

#include <functional>

namespace rb::utils {
    std::string implode(const std::vector<std::string>& strings, const std::string& glue = "");
    
    template<class T, class Func>
    std::vector<T> map(const std::vector<T>& array, Func op)
    {
        std::vector<T> res;
        std::transform(array.begin(), array.end(), std::back_inserter(res), op);
        return std::move(res);
    }
    
    std::string toLower(const std::string& str);

    /**
     * @brief Get value from map or fallback to default if not found
     *
     * Insired by  from: https://stackoverflow.com/questions/2333728/stdmap-default-value
     */
    template <typename M, typename K, typename V>
    V getOr(const M& m, const K& key, const V& defaultValue) {
        auto it = m.find(key);
        if (it == m.end()) {
            return defaultValue;
        }
        else {
            return it->second;
        }
    }
}
