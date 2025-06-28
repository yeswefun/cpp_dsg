#include <iostream>
#include <string>
#include <map>

using namespace std;

class DownloadManager;

class DownloadState {
public:
    virtual void download(string user, string item, DownloadManager *dm) = 0;
protected:
    DownloadState() {} //该类是一个接口
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

class SpiteDownloadState : public DownloadState {
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
    map<string, string> getDownloadItem() {
        return m_downloadItem;
    }
    void download(string user, string item) {
        // 获取cnt
        int cnt;
        if (m_downloadCount.count(user) > 0) {
            cnt = m_downloadCount[user];
        } else {
            m_downloadCount[user] = 0;
        }
        cnt++;
        m_downloadCount[user] = cnt;

        // 根据cnt判断行为
        if (cnt == 1) {
            m_state = new NormalDownloadState;
        } else if (cnt == 2) {
            m_state = new RepeatDownloadState;
        } else if (cnt > 2 && cnt < 5) {
            m_state = new SpiteDownloadState;
        } else if (cnt >= 5) {
            m_state = new BlackDownloadState;
        } //else {}
        m_state->download(user, item, this);
    }
private:
    DownloadState *m_state; //当前状态处理对象
    map<string, string> m_downloadItem;
    map<string, int> m_downloadCount;
};


/*
提取公因式，合并同类项

从 if/else 中提取公因式

自动化流水线的状态组合与业务逻辑解耦合
*/
int main() {

    DownloadManager *pDM = new DownloadManager;
    for (int i = 0; i < 5; i++) {
        pDM->download("dst", "haha");
    }

    return 0;
}
