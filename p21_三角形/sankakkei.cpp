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

int solve(string f) {
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
    int n = nums[0];
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = nums[i+1];
    }
    vector<int> idx(4);
    for (idx[0] = n-1; idx[0] >= 2; idx[0]--) {
        for (idx[1] = idx[0]-1; idx[1] >= 1; idx[1]--) {
            for (idx[2] = idx[1]-1; idx[2] >= 0; idx[2]--) {
                if (a[idx[1]] + a[idx[2]] > a[idx[0]]) return a[idx[0]] + a[idx[1]] + a[idx[2]];
            }
        }
    }
    return 0;
}

int main(int argc, char* argv[]) {
    string input_dir = argv[1];
    vector<string> files = get_file_path(input_dir);
    string f;
    int ans;
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
