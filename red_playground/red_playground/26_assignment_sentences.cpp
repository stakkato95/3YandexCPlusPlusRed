//
//  26_assignment_sentences.cpp
//  red_playground
//
//  Created by Artsiom Kaliaha on 3/21/20.
//  Copyright © 2020 Artsiom Kaliaha. All rights reserved.
//

#include <iostream>

#include <cassert>

#include <vector>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    // Напишите реализацию функции, не копируя объекты типа Token
    
    vector<Sentence<Token>> sentences;
    sentences.push_back(vector<Token>());
    bool isPreviousTokenPunctuation = false;
    
    for (Token& token : tokens) {
        bool isCurrentTokenPunctuation = token.IsEndSentencePunctuation();
        
        if (isPreviousTokenPunctuation && !isCurrentTokenPunctuation) {
            sentences.push_back(vector<Token>());
            isPreviousTokenPunctuation = false;
        }
        
        isPreviousTokenPunctuation = isCurrentTokenPunctuation;
        sentences[sentences.size() - 1].push_back(move(token));
    }
    
    return sentences;
}


struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;
    
    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting() {
    auto result1 = SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}}));
    assert(result1 == vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));
    
    auto result3 = SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}}));
    assert(result3 == vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));
    
    auto result4 =
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}}));
    auto a4 = vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}}, {{"Without"}, {"copies"}, {".", true}}});
    assert(result4 == a4);
}

int main26() {
    TestSplitting();
    return 0;
}
