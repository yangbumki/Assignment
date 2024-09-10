#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> arr, vector<int> query) {
    for (int i = 0; i < query.size(); i++) {
        //int currentPos = arr.at(query.at(i));
        int currentPos = query.at(i);
        i % 2 == 0 ? arr.erase(arr.begin() + currentPos+1, arr.end()) : arr.erase(arr.begin(), arr.begin() + currentPos);
    }

    vector<int> answer = arr;

    return answer;
}
