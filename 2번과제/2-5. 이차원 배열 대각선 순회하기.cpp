#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> board, int k) {

    unsigned int sum = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            sum += i + j <= k ? board[i][j] : 0;
        }
    }
    int answer = sum;
    return answer;
}
