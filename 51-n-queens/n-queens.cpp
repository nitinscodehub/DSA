class Solution {
public:
    vector<vector<string>> res;

    void solve(int row, int n,
               vector<string>& board,
               unordered_set<int>& col,
               unordered_set<int>& diag,
               unordered_set<int>& antiDiag) {

        if(row == n) {
            res.push_back(board);
            return;
        }

        for(int c = 0; c < n; c++) {

            if(col.count(c) || diag.count(row - c) || antiDiag.count(row + c))
                continue;

            // place queen
            board[row][c] = 'Q';
            col.insert(c);
            diag.insert(row - c);
            antiDiag.insert(row + c);

            solve(row + 1, n, board, col, diag, antiDiag);

            // backtrack
            board[row][c] = '.';
            col.erase(c);
            diag.erase(row - c);
            antiDiag.erase(row + c);
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));

        unordered_set<int> col, diag, antiDiag;

        solve(0, n, board, col, diag, antiDiag);

        return res;
    }
};