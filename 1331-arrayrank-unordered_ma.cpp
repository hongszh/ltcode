#include <utility>      // std::pair, std::make_pair
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    // pair的实现，大量数据会超时
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> ans;
        vector<pair<int, int>> arrPair;

        if (arr.size()) {
            return ans;
        }

        for(int i = 0; i < arr.size(); i++) {
            arrPair.push_back(make_pair(arr[i], i));
        }

        // [40,10,20,30]
        // [4,1,2,3]
        // 默认根据first排序
        sort(arrPair.begin(), arrPair.end());

        // 依次判断pair vector中元素是否相等，修改pair.second值
        arrPair[0].second = 1;
        for(int i = 1; i < arrPair.size(); i++) {
            if (arrPair[i].first == arrPair[i-1].first) {
                arrPair[i].second = arrPair[i-1].second;
            } else {
                arrPair[i].second = arrPair[i-1].second+1;
            }
        }

        // 根据原始vector遍历一遍pair vector放入结果值
        for (int i = 0; i < arr.size(); i++) {
            int n = arr[i];
            for(auto p : arrPair) {
                if (n == p.first) {
                    ans.push_back(p.second);
                    break;
                }
            }
        }
        return ans;
    }

    // 利用unordered_map可以直接通过key来检索，比前面的效率提高很多
    vector<int> arrayRankTransform_map(vector<int>& arr) {
        vector<int> ans;
        if (arr.size() == 0) {
            return ans;
        }
        // step 1: 对arr进行排序
        // step 2: 排序后的arr放到map里面
        // step 3: 遍历arr，从map里面检索排序的idx
        vector<int> arrcp = arr;
        sort(arrcp.begin(), arrcp.end());

        int idx = 1;
        unordered_map<int, int> arr_map;
        arr_map[arrcp[0]] = idx;
        for(int i = 1; i < arrcp.size(); i++) {
            if (arrcp[i] != arrcp[i-1]) {
                idx++;
            }
            arr_map[arrcp[i]] = idx;
        }

        for(int i = 0; i < arr.size(); i++) {
            ans.push_back(arr_map[arr[i]]);
        }
        return ans;
    }
};


int main(int argc, char **argv) {
    vector<int> arr = {
        40,10,20,30
    };

    Solution s;
    s.arrayRankTransform(arr);
    s.arrayRankTransform_map(arr);

    return 0;
}
