#include <vector>
using namespace std;

class Solution {
public:
    bool rows[9][9] = {false};
    bool cols[9][9] = {false};
    bool boxes[9][9] = {false};

    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        int num = c - '1';
                        int boxIndex = (i / 3) * 3 + (j / 3);

                        if (!rows[i][num] && !cols[j][num] && !boxes[boxIndex][num]) {
                            
                            // place
                            board[i][j] = c;
                            rows[i][num] = cols[j][num] = boxes[boxIndex][num] = true;

                            if (solve(board)) return true;

                            // backtrack
                            board[i][j] = '.';
                            rows[i][num] = cols[j][num] = boxes[boxIndex][num] = false;
                        }
                    }
                    return false; // no valid number
                }
            }
        }
        return true; // solved
    }

    void solveSudoku(vector<vector<char>>& board) {
        // initialize tracking arrays
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') {
                    int num = board[i][j] - '1';
                    int boxIndex = (i / 3) * 3 + (j / 3);
                    rows[i][num] = cols[j][num] = boxes[boxIndex][num] = true;
                }
            }
        }

        solve(board);
    }
};