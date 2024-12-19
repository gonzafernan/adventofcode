/**
 * Advent of Code 2024
 * Day 10: Hoof It
 * @author Gonzalo G. Fernandez
 */

#include <fstream>
#include <iostream>
#include <memory>
#include <ranges>
#include <vector>

using namespace std;

class Node {
   private:
    int value_;
    bool is_visited_;
    vector<shared_ptr<Node>> neighbors_;

   public:
    Node(int value) {
        value_ = value;
    }

    void addChild(shared_ptr<Node> &neighbor) {
        neighbors_.push_back(neighbor);
        is_visited_ = false;
    }

    void clean(void) {
        is_visited_ = false;
    }

    bool isTrailhead(void) {
        return value_ == 0;
    }

    int getTrailheadScore(int score) {
        is_visited_ = true;
        if (value_ == 9) {
            return 1;
        }
        for (auto &neighbor : neighbors_) {
            if (neighbor->isVisited()) {
                continue;
            }
            if (neighbor->getValue() == value_ + 1) {
                score += neighbor->getTrailheadScore(0);
            }
        }
        return score;
    }

    int getTrailheadRating(int rating) {
        if (value_ == 9) {
            return 1;
        }
        for (auto &neighbor : neighbors_) {
            if (neighbor->getValue() == value_ + 1) {
                rating += neighbor->getTrailheadRating(0);
            }
        }
        return rating;
    }

    int getValue(void) {
        return value_;
    }

    bool isVisited(void) {
        return is_visited_;
    }
};

void generate_graph(vector<vector<shared_ptr<Node>>> &map) {
    for (int row_idx = 0; row_idx < map.size(); row_idx++) {
        for (int col_idx = 0; col_idx < map[row_idx].size(); col_idx++) {
            if (row_idx > 0) {
                map[row_idx][col_idx]->addChild(map[row_idx - 1][col_idx]);
            }
            if (row_idx < map.size() - 1) {
                map[row_idx][col_idx]->addChild(map[row_idx + 1][col_idx]);
            }
            if (col_idx > 0) {
                map[row_idx][col_idx]->addChild(map[row_idx][col_idx - 1]);
            }
            if (col_idx < map[row_idx].size() - 1) {
                map[row_idx][col_idx]->addChild(map[row_idx][col_idx + 1]);
            }
        }
    }
}

void clean_graph(vector<vector<shared_ptr<Node>>> &map) {
    for (int row_idx = 0; row_idx < map.size(); row_idx++) {
        for (int col_idx = 0; col_idx < map[row_idx].size(); col_idx++) {
            map[row_idx][col_idx]->clean();
        }
    }
}

void search_graph(vector<vector<shared_ptr<Node>>> &map, int &sum_score, int &sum_rating) {
    sum_score = 0;
    sum_rating = 0;
    for (int row_idx = 0; row_idx < map.size(); row_idx++) {
        for (int col_idx = 0; col_idx < map[row_idx].size(); col_idx++) {
            if (map[row_idx][col_idx]->isTrailhead()) {
                sum_score += map[row_idx][col_idx]->getTrailheadScore(0);
                clean_graph(map);
                sum_rating += map[row_idx][col_idx]->getTrailheadRating(0);
                clean_graph(map);
            }
        }
    }
}

int day10(string input_file) {
    ifstream input_file_stream;
    string line;
    vector<vector<shared_ptr<Node>>> map;
    int sum_score, sum_rating;

    input_file_stream.open(input_file);
    if (!input_file_stream.is_open()) {
        cout << "Couldn't open input file" << endl;
        return -1;
    }

    int row_idx = 0;
    while (getline(input_file_stream, line)) {
        map.emplace_back();
        for (auto [col_idx, value] : views::enumerate(line)) {
            map[row_idx].push_back(make_shared<Node>((int)value - '0'));
        }
        row_idx++;
    }
    input_file_stream.close();

    generate_graph(map);
    search_graph(map, sum_score, sum_rating);

    cout << "Part 1: Sum of scores of all trailheads: " << sum_score << endl;
    cout << "Part 2: Sum of ratings of all trailheads: " << sum_rating << endl;

    return 0;
}
