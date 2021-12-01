#pragma once

#include <RenderBase/defines.h>

#include <map>
#include <queue>

namespace rb::ds {
    
    template <typename T>
    struct Pool {
        using ID   = std::size_t;
        using Item = std::shared_ptr<T>;

        ID add(Item item)
        {
            ID id;
            if (freeIds.size() > 0) {
                id = freeIds.front();
                freeIds.pop();
                items[id] = item;
            } else {
                id = items.size();
                items.push_back(item);
            }
            return id;
        }
        
        void remove(ID id)
        {
            items[id] = nullptr;
            freeIds.push(id);
        }
        
        inline Item       operator[](ID id)       { return items[id]; }
        inline const Item operator[](ID id) const { return items[id]; }
        
        inline std::vector<Item>::iterator begin() { return items.begin(); }
        inline std::vector<Item>::iterator end()   { return items.end(); }
        
        private:
            std::vector<Item> items;
            std::queue<ID>    freeIds;
    };
    
}
