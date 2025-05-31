#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

map<int, vector<string>> sLogMap;

vector<string> getBugs(string row) {
    vector<string> results;
    istringstream ss(row);
    while (!ss.eof()) {
        string col;
        getline(ss, col, '|');
        results.push_back(col);
    }
    return results;
}

bool initLogMap() {
    ifstream in("./logs.txt");
    if (!in) {
        cerr << "failed to open file" << endl;
        return -1;
    }

    string line;
    int i = 0;
    while (getline(in, line)) {
        sLogMap[i] = getBugs(line);
        i++;
    }
    in.close();
    return 0;
}

/*
缓存思想
AOP: Aspect-Oriented Programming
智能指针

切分日志
    日志
        时间，故障标题，故障描述

    map<int, vector<string>>
        int: 故障序号
        vector<string>: 日志列表
*/
int main() {

    // 一次性加载，内存可能不够
    initLogMap();

    for (int i = 0; i < 3; i++) {
        cout << "*************************** seq: " << i << endl;
        map<int, vector<string>>::iterator it = sLogMap.begin();
        while (it != sLogMap.end()) {
            pair<int, vector<string>> p = *it++;
            cout << "num: " << p.first << endl;
            vector<string>::iterator begin = p.second.begin();
            vector<string>::iterator end = p.second.end();
            while (begin != end) {
                cout << "msg: " << *begin++ << endl;
            }
        }
    }

    return 0;
}
