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
        } else {
            cout << "********************* get from cache" << endl;
        }
        showBugs();
    }
private:
    void showBugs() {
        for (int i = 0; i < sCacheMap.size(); i++) {
            cout << "num: " << i << ", msg: ";
            for (vector<string>::iterator it = sCacheMap[i].begin(); it != sCacheMap[i].end(); it++) {
                cout << (*it) << " ";
            }
            cout << endl;
        }
        // map<int, vector<string>>::iterator it = sCacheMap.begin();
        // while (it != sCacheMap.end()) {
        //     pair<int, vector<string>> p = *it++;
        //     cout << "num: " << p.first << endl;
        //     vector<string>::iterator begin = p.second.begin();
        //     vector<string>::iterator end = p.second.end();
        //     while (begin != end) {
        //         cout << "msg: " << *begin++ << endl;
        //     }
        // }
    }
private:
    bool m_reload; // 重新加载
};

int main() {

    //ProxyBugModel *p = new ProxyBugModel();
    BugManager *p = new ProxyBugModel();
    for (int i = 0; i < 3; i++) {
        cout << "seq: " << i << endl;
        p->getBugs();
    }

    return 0;
}
