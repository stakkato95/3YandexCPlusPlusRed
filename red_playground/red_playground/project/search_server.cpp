#include "search_server.h"
#include "iterator_range.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>

#include <chrono>
#include <ctime>

using namespace std::chrono;

vector<string> SplitIntoWords(const string& line) {
    istringstream words_input(line);
    return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

SearchServer::SearchServer(istream& document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
    InvertedIndex new_index;
    
    for (string current_document; getline(document_input, current_document); ) {
        new_index.Add(move(current_document));
    }
    
    index = move(new_index);
}

void SearchServer::AddQueriesStream(istream& query_input, ostream& search_results_output) {
    long split = 0;
    long lookup = 0;
    long sort = 0;
    long result = 0;
    
    vector<size_t> docid_count(index.docs.size());
    
    for (string current_query; getline(query_input, current_query); ) {
        
        auto startSplit = system_clock::now();
        const auto words = SplitIntoWords(current_query);
        auto endSplit = system_clock::now();
        split += duration_cast<milliseconds>(endSplit - startSplit).count();
        
        auto startLookup = system_clock::now();
        for (const auto& word : words) {
            for (const size_t docid : index.Lookup(word)) {
                docid_count[docid]++;
            }
        }
        auto endLookup = system_clock::now();
        lookup += duration_cast<milliseconds>(endLookup - startLookup).count();
        
        //        vector<pair<size_t, size_t>> search_results(docid_count.begin(), docid_count.end());
        //        sort(
        //             begin(search_results),
        //             end(search_results),
        //             [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) {
        //                 int64_t lhs_docid = lhs.first;
        //                 auto lhs_hit_count = lhs.second;
        //                 int64_t rhs_docid = rhs.first;
        //                 auto rhs_hit_count = rhs.second;
        //                 return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
        //             }
        //             );
        
        auto startSort = system_clock::now();
        //FIRST use set to sort a map
        //        auto comparator = [](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) { return lhs.second > lhs.first; };
        //        set<pair<size_t, size_t>, decltype(comparator)> search_results(docid_count.begin(), docid_count.end(), comparator);
        
        partial_sort(begin(docid_count),
                     next(begin(docid_count), docid_count.size() / 2),
                     end(docid_count), [](size_t l, size_t r) { return l < r; });
        
        
        auto endSort = system_clock::now();
        sort += duration_cast<milliseconds>(endSort - startSort).count();
        
        auto startResult = system_clock::now();
        search_results_output << current_query << ':';
        for (auto [docid, hitcount] : Head(docid_count, 5)) {
            search_results_output << " {"
            << "docid: " << docid << ", "
            << "hitcount: " << hitcount << '}';
        }
        search_results_output << endl;
        auto endResult = system_clock::now();
        result += duration_cast<milliseconds>(endResult - startResult).count();
        
        docid_count.clear();
    }
    
    cout
    << endl
    << split << " split" << endl
    << lookup << " lookup" << endl
    << sort << " sort" << endl
    << result << " result" << endl
    << endl;
}

void InvertedIndex::Add(const string& document) {
    docs.push_back(document);
    
    const size_t docid = docs.size() - 1;
    for (const auto& word : SplitIntoWords(document)) {
        index[word].push_back(docid);
    }
}

list<size_t> InvertedIndex::Lookup(const string& word) const {
    if (auto it = index.find(word); it != index.end()) {
        return it->second;
    } else {
        return {};
    }
}
