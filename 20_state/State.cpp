#include <iostream>
#include <string>
#include <map>

using namespace std;

class DownloadManager {
public:
    void download(string user, string item) {
        int cnt;
        if (m_downloadCount.count(user) > 0) { // 存在
            cnt = m_downloadCount[user];
        } else { // 不存在
            m_downloadCount[user] = 0;
        }
        cnt++;
        m_downloadCount[user] = cnt;

        // 判断行为
        if (cnt == 1) {//正常下载
            m_downloadItem[user] = item;
            cout << "****************** download" << endl;
        } else if (cnt == 2) {//重复下载
            cout << "****************** don't download twice" << endl;
        } else if (cnt > 2 && cnt < 5) {//恶意下载
            cout << "****************** forbide download" << endl;
        } else if (cnt >= 5) {//进入黑名单
            cout << "****************** black list" << endl;
        }
    }
private:
    //用户名 : 下载项
    map<string, string> m_downloadItem;

    //用户名 : 下载次数
    map<string, int> m_downloadCount;
};

/*
考虑一个在线下载应用，
要实现控制在 1s 内同一个用户只能单线程下载一个文件
如果一个用户反复下载，而且同时下载的并发数超过3，则判定为恶意下载，要取消用户下载资格，
如果一个用户的下载个数超过5，将进入黑名单，禁止再登录本系统
*/
int main() {

    DownloadManager *pDM = new DownloadManager;
    for (int i = 0; i < 5; i++) {
        pDM->download("dst", "haha");
    }

    return 0;
}
