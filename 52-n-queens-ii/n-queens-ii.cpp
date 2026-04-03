class Solution {
public:
    int count = 0;

    void solve(int row, int n,
               unordered_set<int>& col,
               unordered_set<int>& diag,
               unordered_set<int>& antiDiag) {

        if(row == n) {
            count++;
            return;
        }

        for(int c = 0; c < n; c++) {

            if(col.count(c) || diag.count(row - c) || antiDiag.count(row + c))
                continue;

            // place queen
            col.insert(c);
            diag.insert(row - c);
            antiDiag.insert(row + c);

            solve(row + 1, n, col, diag, antiDiag);

            // backtrack
            col.erase(c);
            diag.erase(row - c);
            antiDiag.erase(row + c);
        }
    }

    int totalNQueens(int n) {
        unordered_set<int> col, diag, antiDiag;
        solve(0, n, col, diag, antiDiag);
        return count;
    }
};