#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    if (abs(len1 - len2) > 1) return false;
    int count = 0, i = 0, j = 0;
    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            if (++count > d) return false;
            if (len1 > len2) i++;
            else if (len1 < len2) j++;
            else { i++; j++; }
        } else {
            i++; j++;
        }
    }
    return (count + abs(len1 - len2)) <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        print_word_ladder(ladder);
        string last_word = ladder.back();
        
        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && !visited.count(word)) {
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                visited.insert(word);
                if (word == end_word) return new_ladder;
                ladder_queue.push(new_ladder);
            }
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < ladder.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << ladder[i];
    }
    cout << endl;
}


