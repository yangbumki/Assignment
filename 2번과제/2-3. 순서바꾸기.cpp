#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> num_list, int n) {
    vector<int> answer;
    vector<int> preList{};
    vector<int> postList{};
    
    for (int i = 0; i < num_list.size(); i++) {
        if (i <= n-1) {
            preList.push_back(num_list.at(i));
        }else {
            postList.push_back(num_list.at(i));
        }
    }

    for (int i = 0; i < preList.size(); i++) {
        postList.push_back(preList.at(i));
    }

    answer = postList;
    
    return answer;
}