#pragma once

#include <string>
#include <unordered_map>
#include <map>

namespace rb {
    namespace utils {

        std::string toLower(const std::string& str);

        /**
         * @brief Get value from map or fallback to default if not found
         *
         * Insired by  from: https://stackoverflow.com/questions/2333728/stdmap-default-value
         */
        template <typename M, typename K, typename V>
        V getOr(const M& m, const K& key, const V& defaultValue) {
            auto it = m.find(toLower(key));
            if (it == m.end()) {
                return defaultValue;
            }
            else {
                return it->second;
            }
        }
    }
}