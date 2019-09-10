#include <iostream>
#include <string>
#include <vector>
#include <glob.h>
#include <fstream>
#include <time.h>
#include <cmath>
#include <queue>
#include <utility>
using namespace std;

#define INF 10000000
const int DN[4] = {1, 0, -1,  0};
const int DM[4] = {0, 1,  0, -1};

typedef pair<int, int> coord;

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

coord get_coordinate(vector<string> map, char search_mark, int N, int M) {
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            if (map[n][m] == search_mark) {
                return coord(n, m);
            }
        }
    }
    cout << search_mark << " is NOT found." << endl;
    return coord(-1, -1);
}

int bfs(vector<string> map, int N, int M, coord start, coord goal) {
    int distance[N][M];
    queue<coord> que;
    for (int n = 0; n < N; n++) {
        for (int m = 0; m < M; m++) {
            distance[n][m] = INF;
        }
    }
    que.push(start);
    distance[start.first][start.second] = 0;

    while (que.size()) {
        coord c = que.front(); que.pop();
        if (c.first == goal.first && c.second == goal.second) break;
        int n_next, m_next;
        for (int i = 0; i < 4; i++) {
            n_next = c.first + DN[i];
            m_next = c.second + DM[i];
            if (n_next >= 0 && n_next < N && m_next >= 0 && m_next < M && map[n_next][m_next] != '#' && distance[n_next][m_next] == INF) {
                que.push(coord(n_next, m_next));
                distance[n_next][m_next] = distance[c.first][c.second] + 1;
            }
        }
    }
    return distance[goal.first][goal.second];
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
    coord start = get_coordinate(map, 'S', N, M);
    coord goal = get_coordinate(map, 'G', N, M);
    int ans = bfs(map, N, M, start, goal);
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
