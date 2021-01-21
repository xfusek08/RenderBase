
#include <RenderBase/tools/utils.h>

#include <algorithm>

using namespace std;

string rb::utils::toLower(const string& str) {
    string res = str;
    transform(str.begin(), str.end(), res.begin(), ::tolower);
    return res;
}
