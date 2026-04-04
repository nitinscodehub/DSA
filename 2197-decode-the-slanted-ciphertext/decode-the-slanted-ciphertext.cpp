class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        if (rows == 1) return encodedText;

        int n = encodedText.size();
        int cols = n / rows;

        string result = "";

        // Traverse diagonally
        for (int j = 0; j < cols; j++) {
            int i = 0, k = j;
            while (i < rows && k < cols) {
                result += encodedText[i * cols + k];
                i++;
                k++;
            }
        }

        // Remove trailing spaces
        while (!result.empty() && result.back() == ' ') {
            result.pop_back();
        }

        return result;
    }
};