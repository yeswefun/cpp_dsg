#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

map<int, vector<string>> sCacheMap;

class BugManager {
public:
    virtual void getBugs() = 0;
};

class RealBugModel : public BugManager {
public:
    void getBugs() {
        ifstream in("./logs.txt");
        if (!in) {
            cerr << "failed to open file" << endl;
        }
        string line;
        int i = 0;
        while (getline(in, line)) {
            sCacheMap[i] = getCache(line);
            i++;
        }
        in.close();
    }
private:
    vector<string> getCache(string row) {
        vector<string> results;
        istringstream ss(row);
        while (!ss.eof()) {
            string col;
            getline(ss, col, '|');
            results.push_back(col);
        }
        return results;
    }
};

class ProxyBugModel : public BugManager {
public:
    ProxyBugModel() : m_reload(true) {}
    void getBugs() {
        if (m_reload) {
            cout << "********************* get from disk" << endl;
            (new RealBugModel())->getBugs();
            m_reload = false;
            showBugs();
        } else {
            cout << "********************* get from cache" << endl;
            showBugs();
        }
    }
private:
    void showBugs() {
        map<int, vector<string>>::iterator it = sCacheMap.begin();
        while (it != sCacheMap.end()) {
            pair<int, vector<string>> p = *it++;
            cout << "no: " << p.first << endl;
            vector<string>::iterator begin = p.second.begin();
            vector<string>::iterator end = p.second.end();
            while (begin != end) {
                cout << "info: " << *begin++ << endl;
            }
        }
    }
private:
    bool m_reload;
};

/*
智能指针
aop
缓存思想

切分日志
    日志
        时间，故障标题，故障描述

    map<int, vector<string>>
        int: 故障序号
        vector<string>: 日志列表
*/
int main() {

    //ProxyBugModel *p = new ProxyBugModel();
    BugManager *p = new ProxyBugModel();
    for (int i = 0; i < 3; i++) {
        cout << "seq: " << i << endl;
        p->getBugs();
    }

    return 0;
}
