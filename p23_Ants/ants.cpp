#include <iostream>
#include <string>
#include <vector>
#include <glob.h>
#include <fstream>
#include <time.h>
#include <cmath>
#include <tuple>
#include <limits>
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


tuple<int, int> solve(string f) {
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
    int L = nums[0], n = nums[1];
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        x[i] = nums[i+2];
    }
    int min_val = 0, max_val = 0;
    for (int i = 0; i < n; i++) {
        min_val = max(min_val, min(x[i], L - x[i]));
        max_val = max(max_val, max(x[i], L - x[i]));
    }
    return forward_as_tuple(min_val, max_val);
}

int main(int argc, char* argv[]) {
    string input_dir = argv[1];
    vector<string> files = get_file_path(input_dir);
    string f;
    int min_val, max_val;
    clock_t start, end;
    for (const auto& f: files) {
        start = clock();
        tie(min_val, max_val) = solve(f);
        end = clock();
        cout << "Input file : " << f << endl;
        cout << "Answer : " << "min = " << min_val << " | max = " << max_val << endl;
        cout << "Time : " << (int)((end - start) * pow(10, 3) / CLOCKS_PER_SEC) << " msec" << endl;
        cout << "##########" << endl;
    }
    return 0;
}
