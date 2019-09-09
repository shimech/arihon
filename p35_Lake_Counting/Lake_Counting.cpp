#include <iostream>
#include <string>
#include <vector>
#include <glob.h>
#include <fstream>
#include <time.h>
#include <cmath>
using namespace std;

int DN[8] = {-1, -1, 0, 1, 1,  1,  0, -1};
int DM[8] = { 0,  1, 1, 1, 0, -1, -1, -1};

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

vector<string> dfs(int n, int m, int N, int M, vector<string> map) {
    map[n][m] = '.';
    int n_next, m_next;
    for (int i = 0; i < 8; i++) {
        n_next = n + DN[i];
        m_next = m + DM[i];
        if (n_next >= 0 && n_next < N && m_next >= 0 && m_next < M && map[n_next][m_next] == 'W') {
            map = dfs(n_next, m_next, N, M, map);
        }
    }
    return map;
}

int solve(string f) {
    ifstream ifs(f);
    string l;
    vector<string> inputs;
    int first = 0, last;
    while (getline(ifs, l)) {
        inputs.push_back(l);
    }
    vector<int> nums;
    last = inputs[0].find_first_of(" ");
    while (first < inputs[0].size()) {
        string subStr(inputs[0], first, last - first);
        nums.push_back(atoi(subStr.c_str()));
        first = last + 1;
        last = inputs[0].find_first_of(" ", first);
        if (last == string::npos) {
            last = inputs[0].size();
        }
    }
    int N = nums[0], M = nums[1];
    vector<string> map(N);
    for (int n = 0; n < N; n++) {
        map[n] = inputs[n+1];
    }
    int ans = 0;
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            if (map[n][m] == 'W') {
                map = dfs(n, m, N, M, map);
                ans++;
            }
        }
    }
    return ans;
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
