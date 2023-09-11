#include <iostream>

using namespace std;

class ExportFileApi {
public:
    virtual bool exportData(string data) = 0;
protected:
    ExportFileApi() {}
};


//------------------------------------ 客户端不可见: start
class ExportTextFile : public ExportFileApi {
public:
    bool exportData(string data) {
        cout << "text: " << data << endl;
        return true;
    }
};

class ExportDB : public ExportFileApi {
public:
    bool exportData(string data) {
        cout << "db: " << data << endl;
        return true;
    }
};
//------------------------------------ 客户端不可见: end


class ExportOperation : public ExportFileApi { // 接口
public:
    bool exportData(string data) {
        cout << "exportData: " << data << endl;
        ExportFileApi* pApi = factoryMethod();
        return pApi->exportData(data);
    }
protected:
    virtual ExportFileApi* factoryMethod() = 0;
};

class ExportTextFileOperation : public ExportOperation {
protected:
    ExportFileApi* factoryMethod() {
        return new ExportTextFile();
    }
};

class ExportDBOperation : public ExportOperation {
protected:
    ExportFileApi* factoryMethod() {
        return new ExportDB();
    }
};

int main() {

    ExportOperation *pOp;
    
    pOp = new ExportTextFileOperation();
    pOp->exportData("数据");

    pOp = new ExportDBOperation();
    pOp->exportData("数据");

    return 0;
}
