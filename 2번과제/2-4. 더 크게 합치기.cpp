#include <string>
#include <vector>

using namespace std;

int solution(int a, int b) {
    int answer = 0;

    string ab = to_string(a) + to_string(b);
    string ba = to_string(b) + to_string(a);

    int abNum = atoi(ab.c_str());
    int baNum = atoi(ba.c_str());

    answer = abNum >= baNum ? abNum : baNum;

    return answer;
}