#include <iostream>
#include <string>
#include <map>

using namespace std;

class DownloadManager;

class DownloadState {
public:
    virtual void download(string user, string item, DownloadManager *dm) = 0;
protected:
    //该类是一个接口
    DownloadState() {};
};

class NormalDownloadState : public DownloadState {
public:
    void download(string user, string item, DownloadManager *dm) {
        cout << "****************** download" << endl;
    }
};

class RepeatDownloadState : public DownloadState {
public:
    void download(string user, string item, DownloadManager *dm) {
        cout << "****************** don't download twice" << endl;
    }
};

class SplitDownloadState : public DownloadState {
public:
    void download(string user, string item, DownloadManager *dm) {
        cout << "****************** forbide download" << endl;
    }
};

class BlackDownloadState : public DownloadState {
public:
    void download(string user, string item, DownloadManager *dm) {
        cout << "****************** black list" << endl;
    }
};

class DownloadManager {
public:
    map<string, string> getDownItem() {
        return m_downItem;
    }
    void down(string user, string item) {
        int downCount = 0;
        if (m_downCount.count(user) > 0) {
            downCount = m_downCount[user];
        } else {
            m_downCount[user] = 0;
        }
        downCount++;
        m_downCount[user] = downCount;

        if (downCount == 1) {
            m_state = new NormalDownloadState;
        } else if (downCount > 1 && downCount < 3) {
            m_state = new RepeatDownloadState;
        } else if (downCount >= 3 && downCount < 5) {
            m_state = new SplitDownloadState;
        } else if (downCount >= 5) {
            m_state = new BlackDownloadState;
        }
        m_state->download(user, item, this);
    }
private:
    DownloadState *m_state;
    map<string, string> m_downItem;
    map<string, int> m_downCount;
};


/*
提取公因式，合并同类项
*/
int main() {

    DownloadManager *pDM = new DownloadManager;
    for (int i = 0; i < 5; i++) {
        pDM->down("dst", "haha");
    }

    return 0;
}
