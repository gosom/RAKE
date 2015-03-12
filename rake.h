#ifndef RAKE_H
#define RAKE_H
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <boost/regex.hpp>

namespace rake{


typedef boost::regex regex;
typedef std::vector<std::string> phrase;

class Rake
{
public:
    Rake(std::string stopwords_fname, regex phrase_delimiters,
         regex word_delimiters);

    std::vector<std::string> extract(const std::string& text);
private:
    std::set<std::string> _stopwords;
    regex _phrase_delim;
    regex _word_delim;

    void _load_stopwords(std::string stopwords_fname);
    std::unordered_map<std::string, float> wordscores(const std::vector<phrase> &p);
    float phrasescore(const phrase& phr, const std::unordered_map<std::string, float> ws);
    std::vector<phrase> split_sentence(const std::string& sentence);
};

}
#endif // RAKE_H
