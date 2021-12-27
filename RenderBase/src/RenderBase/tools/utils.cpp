
#include <RenderBase/tools/utils.h>

#include <RenderBase/defines.h>

using namespace std;

string rb::utils::implode(const vector<string>& strings, const string& glue)
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

string rb::utils::toLower(const string& str) {
    string res = str;
    transform(str.begin(), str.end(), res.begin(), ::tolower);
    return res;
}
