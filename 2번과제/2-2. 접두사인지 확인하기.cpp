#include <string>
#include <vector>

using namespace std;

int solution(string my_string, string is_prefix) {
    int answer = 0;

    if (my_string.size() >= is_prefix.size()) {
        int totCnt = 0;

        for (int i = 0; i < is_prefix.size(); i++) {
            if (my_string.at(i) == is_prefix.at(i)) {
                totCnt++;
            }
        }

        answer = totCnt == is_prefix.size() ? 1 : 0;
    }

    return answer;
}