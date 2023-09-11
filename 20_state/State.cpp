#include <iostream>
#include <string>
#include <map>

using namespace std;

class DownloadManager {
public:
    void down(string user, string downItem) {
        int downCount = 0;
        if (m_downCount.count(user) > 0) {
            downCount = m_downCount[user];
        } else {
            m_downCount[user] = 0;
        }
        downCount++;
        m_downCount[user] = downCount;

        if (downCount == 1) {
            //正常下载
            m_downItem[user] = downItem;
            cout << "****************** download" << endl;
        } else if (downCount > 1 && downCount < 3) {
            cout << "****************** don't download twice" << endl;
        } else if (downCount >= 3 && downCount < 5) {
            cout << "****************** forbide download" << endl;
        } else if (downCount >= 5) {
            cout << "****************** black list" << endl;
        }
    }
private:
    //用户名 : 下载项
    map<string, string> m_downItem;

    //用户名 : 下载次数
    map<string, int> m_downCount;
};


int main() {

    DownloadManager *pDM = new DownloadManager;
    for (int i = 0; i < 5; i++) {
        pDM->down("dst", "haha");
    }

    return 0;
}
