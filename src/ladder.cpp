#include "ladder.h"

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int len1 = str1.size(), len2 = str2.size();
    
    if (abs(len1 - len2) > d) return false;  // If the length difference is more than d, return false

    int i = 0, j = 0, count = 0;

    while (i < len1 && j < len2) {
        if (str1[i] != str2[j]) {
            count++;
            if (count > d) return false;  // More than `d` differences found

            // Handle insertions, deletions, or substitutions
            if (len1 > len2) i++;    // Deletion in str1
            else if (len1 < len2) j++; // Insertion in str1
            else { i++; j++; }        // Substitution
        } else {
            i++; j++;
        }
    }

    // If one word is longer, count the remaining characters
    count += abs(len1 - len2);

    return count <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.size(), len2 = word2.size();
    if (abs(len1 - len2) > 1) return false;  

    int i = 0, j = 0, diff = 0;
    
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++diff > 1) return false;  
            if (len1 > len2) i++;  
            else if (len1 < len2) j++;
            else { i++; j++; }  
        } else {
            i++; j++;
        }
    }

    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    if(begin_word == end_word){
        return {};
    }

    if (word_list.empty()) {
    cerr << "Error: Dictionary is empty!" << endl;
    return {};
    }

    if (word_list.find(end_word) == word_list.end()) {
        cerr << "Error: End word not in dictionary!" << endl;
        return {};
    }

    
    while (!ladder_queue.empty()) {
        int level_size = ladder_queue.size();
        set<string> to_mark;  

        while (level_size--) {
            vector<string> ladder = ladder_queue.front();
            ladder_queue.pop();
            string last_word = ladder.back();
            
            if (last_word == end_word) return ladder;
            
            for (const string& word : word_list) {
                if (is_adjacent(last_word, word) && !visited.count(word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    ladder_queue.push(new_ladder);
                    to_mark.insert(word);
                }
            }
        }

        for (const string& word : to_mark) {
            visited.insert(word);
        }
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); i++) {
        if (i > 0){
            cout << ladder[i] << " ";
        }
    }
    cout << endl;
}

void verify_word_ladder(const vector<string> &ladder){
    cout << ladder.size();
}

