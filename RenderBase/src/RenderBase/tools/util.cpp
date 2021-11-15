
#include <RenderBase/tools/util.h>

#include <RenderBase/defines.h>

using namespace std;

string rb::implode(const vector<string>& strings, const string& glue)
{
    string res;
    if (glue.size() == 0) {
        for (const auto& s : strings) {
            res += s;
        }
        return res;
    }
    
    uint32 i = 0;
    while (i < strings.size() - 1) {
        res += strings[i] + glue;
        ++i;
    }
    return res + strings[i];
}
