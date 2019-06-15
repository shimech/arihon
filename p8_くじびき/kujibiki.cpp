#include <iostream>
#include <string>
#include <vector>
#include <glob.h>
#include <fstream>
#include <time.h>
#include <cmath>
using namespace std;

vector<string> get_file_path(string input_dir) {
    glob_t globbuf;
    vector<string> files;
    glob((input_dir + "*.txt").c_str(), 0, NULL, &globbuf);
    for (int i = 0; i < globbuf.gl_pathc; i++) {
        files.push_back(globbuf.gl_pathv[i]);
    }
    globfree(&globbuf);
    return files;
}


string solve(string f) {
    ifstream ifs(f);
    string l;
    vector<int> nums;
    int first, last, count = 0;
    while (getline(ifs, l)) {
        count = 0;
        first = 0;
        last = l.find_first_of(" ");
        while (first < l.size()) {
            string subStr(l, first, last - first);
            nums.push_back(atoi(subStr.c_str()));
            first = last + 1;
            last = l.find_first_of(" ", first);
            if (last == string::npos) {
                if (count == 0) break;
                else last = l.size();
            }
            count++;
        }
    }
    int n, m;
    vector<int> k;
    n = nums[0]; m = nums[1];
    for (int i = 2; i < nums.size(); i++) {
        k.push_back(nums[i]);
    }
    vector<int> idx(4);
    string ans = "No";
    for (idx[0] = 0; idx[0] < n; idx[0]++) {
        for (idx[1] = 0; idx[1] < n; idx[1]++) {
            for (idx[2] = 0; idx[2] < n; idx[2]++) {
                for (idx[3] = 0; idx[3] < n; idx[3]++) {
                    if (k[idx[0]] + k[idx[1]] + k[idx[2]] + k[idx[3]] == m) {
                        ans = "Yes";
                        return ans;
                    }
                }
            }
        }
    }
    return ans;
}

int main(int argc, char* argv[]) {
    string input_dir = argv[1];
    vector<string> files = get_file_path(input_dir);
    string f, ans;
    clock_t start, end;
    for (const auto& f: files) {
        start = clock();
        ans = solve(f);
        end = clock();
        cout << "Input file : " << f << endl;
        cout << "Answer : " << ans << endl;
        cout << "Time : " << (int)((end - start) * pow(10, 3) / CLOCKS_PER_SEC) << " msec" << endl;
        cout << "##########" << endl;
    }
    return 0;
}
