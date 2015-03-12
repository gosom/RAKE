#include "rake.h"
#include "utils.h"
#include <fstream>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace rake{


Rake::Rake(std::string stopwords_fname,
           regex phrase_delimiters, regex word_delimiters){
    _load_stopwords(stopwords_fname);
    _word_delim = word_delimiters;
    _phrase_delim = phrase_delimiters;

}

void Rake::_load_stopwords(std::string stopwords_fname){
    std::ifstream stopwords_file(stopwords_fname);
    if(!stopwords_file){
        throw std::exception();
    }
    std::string line;
    while(stopwords_file>>line)
        _stopwords.insert(line);
}

std::vector<std::string> Rake::extract(const std::string& text){
    auto ltext = lower(text);
    std::vector<std::string> sentences = split(ltext, _phrase_delim);
    std::vector<phrase> candidates;
    for(auto& s: sentences){
        auto v = split_sentence(s);
        for(auto& phr: v)
            if(phr.size() > 0)
                candidates.push_back(phr);
    }
    auto scores = wordscores(candidates);

    std::vector<std::pair<std::string, float>> phrase_scores;
    for(auto& phr: candidates){
        auto phrase_val = join(phr, " ");
        auto val = phrasescore(phr, scores);
        phrase_scores.push_back(make_pair(phrase_val, val));
    }
    std::stable_sort(phrase_scores.begin(), phrase_scores.end(),
              [](const std::pair<std::string, float> &x, const std::pair<std::string, float>& y){
                        return x.second > y.second;
                }
    );
    auto picknum = phrase_scores.size()/3;
    std::vector<std::string> result;
    for(int i=0; i<picknum; ++i)
        result.push_back(phrase_scores[i].first);
    return result;
}

float Rake::phrasescore(const phrase &phr,
                        const std::unordered_map<std::string, float> ws){
    float score = 0.0f;
    for(auto& word: phr)
        score += ws.at(word);
    return score;
}

std::unordered_map<std::string, float> Rake::wordscores(const std::vector<phrase> &p){
    std::unordered_map<std::string, int> deg, freq;
    for(auto& phr: p){
        int phrase_len = phr.size();
        for(auto& word: phr){
            freq[word]++;
            deg[word] += phrase_len;
        }
    }
    std::unordered_map<std::string, float> scores;
    for(auto it=freq.begin(); it != freq.end(); ++it){
        auto word = it->first;
        auto frequency = (float) it->second;
        auto degree = (float) deg[word];
        scores[word] = degree/frequency;
    }
    return scores;
}

std::vector<phrase> Rake::split_sentence(const std::string &sentence){
    std::vector<std::string> words = split(sentence, _word_delim);
    std::vector<phrase> res;
    std::vector<std::string> tmp;
    for(auto& w: words){
        if(_stopwords.find(w) != _stopwords.end()){
            if(tmp.size() > 0){
                res.push_back(tmp);
                tmp.clear();
            }
        }else
           tmp.push_back(w);
    }
    if(tmp.size() > 0)
        res.push_back(tmp);
    return res;
}


}
