#include <iostream>
#include <istream>
#include <ostream>
#include "rake.h"
#include "utils.h"

using namespace rake;

int main()
{
    std::cin >> std::noskipws;
    std::string line;
    std::istream_iterator<char> it(std::cin);
    std::istream_iterator<char> end;
    std::string doc(it, end);

    std::string stopfile = "/home/giorgos/projects/RAKE/stopwords.txt";
    regex phrase_delim(R"([.!?,\t\(\)\r])");
    regex word_delim(R"([^A-Za-z0-9_\+\-]+)");
    Rake rake(stopfile, phrase_delim, word_delim);

    std::vector<std::string> keywords = rake.extract(doc);
    std::cout << join(keywords, ",") << std::endl;

    return 0;
}

