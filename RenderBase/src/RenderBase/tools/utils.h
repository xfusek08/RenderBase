#pragma once

#include <string>
#include <vector>

#include <functional>

#include <type_traits>

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
    
    // see: https://stackoverflow.com/questions/14294267/class-template-for-numeric-types/14294277
    template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    std::vector<T> genRange(T firstValue, size_t count, T increment = 0) {
        std::vector<T> res = std::vector<T>(count);
        res[0] = firstValue;
        for (int i = 1; i < count; ++i) {
            res[i] = res[i - 1] + increment;
        }
        return move(res);
    }
}
