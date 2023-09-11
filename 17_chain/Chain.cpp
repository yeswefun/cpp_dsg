#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class FeeRequest {
public:
    int request(double fee) {

        int res;

        cout << "***************************" << endl;

        res = pmHandle(fee);
        if (res > 0) {
            return res;
        }

        res = dmHandle(fee);
        if (res > 0) {
            return res;
        }

        res = ceoHandle(fee);
        if (res > 0) {
            return res;
        }

        return 0;
    }
private:
    int pmHandle(double fee) {
        cout << "pm: " << fee << endl;
        return fee >= 0 && fee < 500;
    }

    int dmHandle(double fee) {
        cout << "dm: " << fee << endl;
        return fee >= 500 && fee < 1000;
    }

    int ceoHandle(double fee) {
        cout << "ceo: " << fee << endl;
        return fee >= 1000;
    }
};


int main() {

    FeeRequest *pRequest = new FeeRequest;
    cout << pRequest->request(-128) << endl;
    cout << pRequest->request(256) << endl;
    cout << pRequest->request(512) << endl;
    cout << pRequest->request(1024) << endl;

    return 0;
}
