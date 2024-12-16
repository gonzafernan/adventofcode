/**
 * Advent of Code 2024
 * Day 6: Guard Gallivant
 * @author Gonzalo G. Fernandez
 */

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef enum {
    GUARD_DIRECTION_UP = '^',
    GUARD_DIRECTION_DOWN = 'v',
    GUARD_DIRECTION_RIGHT = '>',
    GUARD_DIRECTION_LEFT = '<',
} guard_direction_t;

class Guard {
   private:
    int position_x_;  // 0 left
    int position_y_;  // 0 top
    int next_position_x_;
    int next_position_y_;
    guard_direction_t direction_;

    void setNextPosition_(void) {
        switch (direction_) {
            case GUARD_DIRECTION_UP:
                next_position_y_ = position_y_ - 1;
                next_position_x_ = position_x_;
                break;
            case GUARD_DIRECTION_DOWN:
                next_position_y_ = position_y_ + 1;
                next_position_x_ = position_x_;
                break;
            case GUARD_DIRECTION_RIGHT:
                next_position_y_ = position_y_;
                next_position_x_ = position_x_ + 1;
                break;
            case GUARD_DIRECTION_LEFT:
                next_position_y_ = position_y_;
                next_position_x_ = position_x_ - 1;
                break;
            default:
                // invalid
                break;
        }
    }

   public:
    Guard(int initial_x, int initial_y, guard_direction_t initial_direction) {
        position_x_ = initial_x;
        position_y_ = initial_y;
        direction_ = initial_direction;
        setNextPosition_();
    }

    void getNextPosition(int &next_position_x, int &next_position_y) {
        next_position_x = next_position_x_;
        next_position_y = next_position_y_;
    }

    void stepForward(void) {
        position_x_ = next_position_x_;
        position_y_ = next_position_y_;
        setNextPosition_();
    }

    void turnRight(void) {
        switch (direction_) {
            case GUARD_DIRECTION_UP:
                direction_ = GUARD_DIRECTION_RIGHT;
                break;
            case GUARD_DIRECTION_DOWN:
                direction_ = GUARD_DIRECTION_LEFT;
                break;
            case GUARD_DIRECTION_RIGHT:
                direction_ = GUARD_DIRECTION_DOWN;
                break;
            case GUARD_DIRECTION_LEFT:
                direction_ = GUARD_DIRECTION_UP;
                break;
            default:
                // invalid
                break;
        }
        setNextPosition_();
    }

    guard_direction_t getDirection(void) {
        return direction_;
    }
};

void display_grid(vector<vector<char>> &grid) {
    for (vector<char> line : grid) {
        for (char value : line) {
            cout << value;
        }
        cout << endl;
    }
}

int guard_direction_to_mask_index(guard_direction_t guard_direction) {
    switch (guard_direction) {
        case GUARD_DIRECTION_UP:
            return 0;
        case GUARD_DIRECTION_DOWN:
            return 1;
        case GUARD_DIRECTION_RIGHT:
            return 2;
        case GUARD_DIRECTION_LEFT:
            return 3;
        default:
            return -1;  // invalid
    }
}

// returns 0 if the guard exits the area
int simulate_guard_path(vector<vector<char>> grid, int guard_initial_x, int guard_initial_y,
                        guard_direction_t guard_initial_direction, int &distinct_positions) {
    Guard guard = Guard(guard_initial_x, guard_initial_y, guard_initial_direction);
    int next_position_x, next_position_y;
    distinct_positions = 1;
    while (1) {
        guard.getNextPosition(next_position_x, next_position_y);
        if (next_position_x < 0 || next_position_y < 0 || next_position_x > grid[0].size() - 1 ||
            next_position_y > grid.size() - 1) {
            // guard is outside map
            break;
        } else if (grid[next_position_y][next_position_x] == '#') {
            guard.turnRight();
        } else {
            if (grid[next_position_y][next_position_x] == 0) {
                distinct_positions++;
            } else if (((grid[next_position_y][next_position_x] >>
                         guard_direction_to_mask_index(guard.getDirection())) &
                        1) == 1) {
                return 1;
            }
            grid[next_position_y][next_position_x] |= (1 << guard_direction_to_mask_index(guard.getDirection()));
            guard.stepForward();
        };
    }
    return 0;
}

int day6_part1(vector<vector<char>> grid, int guard_initial_x, int guard_initial_y,
               guard_direction_t guard_initial_direction) {
    int sum_distinct_positions;
    simulate_guard_path(grid, guard_initial_x, guard_initial_y, guard_initial_direction, sum_distinct_positions);
    return sum_distinct_positions;
}

int day6_part2(vector<vector<char>> grid, int guard_initial_x, int guard_initial_y,
               guard_direction_t guard_initial_direction) {
    int sum_obstraction_for_loop = 0, distinct_positions;
    for (int row_idx = 0; row_idx < grid.size(); row_idx++) {
        for (int col_idx = 0; col_idx < grid[row_idx].size(); col_idx++) {
            if (grid[row_idx][col_idx] == '#' || (row_idx == guard_initial_y && col_idx == guard_initial_x)) {
                continue;  // avoid unnecesary checks
            }
            vector<vector<char>> new_grid = grid;
            new_grid[row_idx][col_idx] = '#';
            if (simulate_guard_path(new_grid, guard_initial_x, guard_initial_y, guard_initial_direction,
                                    distinct_positions)) {
                sum_obstraction_for_loop++;
            }
        }
    }
    return sum_obstraction_for_loop;
}

int day6(string input_file) {
    ifstream input_file_stream;
    string line;
    vector<vector<char>> grid;
    int row_idx, col_idx, guard_initial_x, guard_initial_y;
    guard_direction_t guard_initial_direction;

    input_file_stream.open(input_file);
    if (!input_file_stream.is_open()) {
        cout << "Couldn't open input file" << endl;
        return -1;
    }

    row_idx = 0;
    while (getline(input_file_stream, line)) {
        vector<char> new_row;
        col_idx = 0;
        for (char value : line) {
            if (value == '^' || value == 'v' || value == '>' || value == '<') {
                guard_initial_x = col_idx;
                guard_initial_y = row_idx;
                guard_initial_direction = (guard_direction_t)value;
                value = 0 | (1 << guard_direction_to_mask_index(guard_initial_direction));
            } else if (value == '.') {
                value = 0;
            }
            new_row.push_back(value);
            col_idx++;
        }
        grid.push_back(new_row);
        row_idx++;
    }

    input_file_stream.close();

    cout << "Part 1: Number of distinct positions that the guard will visit before leaving the area: "
         << day6_part1(grid, guard_initial_x, guard_initial_y, guard_initial_direction) << endl;
    cout << "Part 2: Number if dufferent positions for the obstruction to make the guard loop: "
         << day6_part2(grid, guard_initial_x, guard_initial_y, guard_initial_direction) << endl;

    return 0;
}
