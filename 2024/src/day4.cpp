/**
 * Advent of Code 2024
 * Day 4: Ceres Search
 * @author Gonzalo G. Fernandez
 * Topics: recursion, shared pointers, graph implementation
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>
#include <ranges>
#include <vector>

using namespace std;

#define NUMBER_OF_NEIGHBORS 8

const char word1_to_find[] = {'X', 'M', 'A', 'S'};
const char word2_to_find[] = {'M', 'A', 'S'};

class LetterNode {
   private:
    char letter;
    vector<shared_ptr<LetterNode>> neighbors;
    weak_ptr<LetterNode> backwardConnection;

   public:
    LetterNode(const char letter) : letter(letter) {
    }

    char getLetter(void) const {
        return letter;
    };

    void setNeighbor(const shared_ptr<LetterNode> &neighbor) {
        neighbors.push_back(neighbor);
    }

    shared_ptr<LetterNode> getNeighbor(int index) const {
        return neighbors[index];
    }
};

bool search_word(shared_ptr<LetterNode> current_node, char expected_letter_idx, int direction, const char *word_to_find,
                 int size_word_to_find, vector<shared_ptr<LetterNode>> &word_found) {
    if (current_node->getLetter() != word_to_find[expected_letter_idx]) {
        return false;
    }
    word_found.push_back(current_node);
    if (expected_letter_idx == size_word_to_find - 1) {
        return true;
    }
    shared_ptr<LetterNode> next_node = current_node->getNeighbor(direction);
    if (next_node == nullptr) {
        return false;
    }
    return search_word(next_node, expected_letter_idx + 1, direction, word_to_find, size_word_to_find, word_found);
}

void generate_word_search_graph(vector<vector<shared_ptr<LetterNode>>> &word_search) {
    for (int row_idx = 0; row_idx < word_search.size(); row_idx++) {
        for (int col_idx = 0; col_idx < word_search[row_idx].size(); col_idx++) {
            // upper row
            word_search[row_idx][col_idx]->setNeighbor(  // upper left (0)
                (row_idx > 0 && col_idx > 0) ? word_search[row_idx - 1][col_idx - 1] : nullptr);
            word_search[row_idx][col_idx]->setNeighbor((row_idx > 0) ? word_search[row_idx - 1][col_idx] : NULL);
            word_search[row_idx][col_idx]->setNeighbor(  // upper right (2)
                (row_idx > 0 && col_idx < word_search[row_idx].size() - 1) ? word_search[row_idx - 1][col_idx + 1]
                                                                           : nullptr);
            // to left
            word_search[row_idx][col_idx]->setNeighbor((col_idx > 0) ? word_search[row_idx][col_idx - 1] : NULL);
            // to right
            word_search[row_idx][col_idx]->setNeighbor(
                (col_idx < word_search[row_idx].size() - 1) ? word_search[row_idx][col_idx + 1] : nullptr);
            // bottom row
            word_search[row_idx][col_idx]->setNeighbor(  // bottom left (5)
                (row_idx < word_search.size() - 1 && col_idx > 0) ? word_search[row_idx + 1][col_idx - 1] : nullptr);
            word_search[row_idx][col_idx]->setNeighbor(
                (row_idx < word_search.size() - 1) ? word_search[row_idx + 1][col_idx] : nullptr);
            word_search[row_idx][col_idx]->setNeighbor(  // bottom right (7)
                (row_idx < word_search.size() - 1 && col_idx < word_search[row_idx].size() - 1)
                    ? word_search[row_idx + 1][col_idx + 1]
                    : nullptr);
        }
    }
}

int perform_word_search_part1(vector<vector<shared_ptr<LetterNode>>> &word_search, const char *word_to_find,
                              int size_word_to_find) {
    int word_count = 0;
    for (int row_idx = 0; row_idx < word_search.size(); row_idx++) {
        for (int col_idx = 0; col_idx < word_search[row_idx].size(); col_idx++) {
            for (int direction = 0; direction < NUMBER_OF_NEIGHBORS; direction++) {
                vector<shared_ptr<LetterNode>> word_found;
                if (search_word(word_search[row_idx][col_idx], 0, direction, word_to_find, size_word_to_find,
                                word_found)) {
                    word_count++;
                }
            }
        }
    }
    return word_count;
}

int perform_word_search_part2(vector<vector<shared_ptr<LetterNode>>> &word_search, const char *word_to_find,
                              int size_word_to_find) {
    vector<vector<shared_ptr<LetterNode>>> words_found;
    int word_count = 0;
    int useful_directions[4] = {0, 2, 5, 7};
    for (int row_idx = 0; row_idx < word_search.size(); row_idx++) {
        for (int col_idx = 0; col_idx < word_search[row_idx].size(); col_idx++) {
            for (int i = 0; i < 4; i++) {
                vector<shared_ptr<LetterNode>> word_found;
                if (search_word(word_search[row_idx][col_idx], 0, useful_directions[i], word_to_find, size_word_to_find,
                                word_found)) {
                    words_found.push_back(word_found);
                }
            }
        }
    }
    for (int i = 0; i < words_found.size(); i++) {
        for (int j = i + 1; j < words_found.size(); j++) {
            if (words_found[i][1] == words_found[j][1]) {
                word_count++;
            }
        }
    }
    return word_count;
}

int day4(string input_file) {
    ifstream input_file_stream;
    string line;
    vector<vector<shared_ptr<LetterNode>>> word_search;
    int word_count;

    input_file_stream.open(input_file);
    if (!input_file_stream.is_open()) {
        cout << "Couldn't open input file" << endl;
        return -1;
    }

    int row_idx = 0;
    while (getline(input_file_stream, line)) {
        word_search.emplace_back();
        for (auto [col_idx, letter] : views::enumerate(line)) {
            word_search[row_idx].push_back(make_shared<LetterNode>(LetterNode(letter)));
        }
        row_idx++;
    }
    input_file_stream.close();

    cout << "Row size: " << word_search.size() << endl;
    cout << "Column size: " << word_search[0].size() << endl;

    cout << "Generating graph..." << endl;
    generate_word_search_graph(word_search);

    cout << "Performing word search (part 1)..." << endl;
    word_count = perform_word_search_part1(word_search, word1_to_find, 4);
    cout << "Number of XMAS found: " << word_count << endl;

    cout << "Performing word search (part 2)..." << endl;
    word_count = perform_word_search_part2(word_search, word2_to_find, 3);
    cout << "Number of X-MAS found: " << word_count << endl;

    return 0;
}
