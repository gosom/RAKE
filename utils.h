#ifndef UTILS_H
#define UTILS_H
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <string>
#include <vector>

namespace rake{


inline std::vector<std::string> split(const std::string& text, const boost::regex& regex){
    std::vector<std::string> results;
    boost::sregex_token_iterator i(text.begin(), text.end(), regex, -1);
    boost::sregex_token_iterator end;
    while(i != end){
        std::string token(*i);
        boost::trim(token);
        if(token != "")
            results.push_back(token);
        i++;
    }
    return results;
}

inline std::string lower(const std::string str){
    return boost::to_lower_copy(str);
}

inline std::string join(const std::vector<std::string>& v, std::string c=" "){
    int s = v.size();
    if(s == 0)
        return "";
    std::string res = "";
    for(int i=0; i<s; ++i){
        res += v[i];
        if(i != s-1)
            res += c;
    }
    return res;
}

}
#endif // UTILS_H
