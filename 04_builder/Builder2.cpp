#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

template<class T>
string convertToString(T value) {
    stringstream ss;
    ss << value;
    return ss.str();
}


class ExportHeaderModel {
public:
    ExportHeaderModel(string depId, string exportDate) : m_strDepId(depId), m_strExportDate(exportDate) {
    }

    string getDepId() {
        return m_strDepId;
    }

    string getExportDate() {
        return m_strExportDate;
    }
private:
    string m_strDepId;
    string m_strExportDate;
};


class ExportDataModel {
public:
    ExportDataModel(string transId, double quantity) : m_transId(transId), m_quantity(quantity) {
    }

    string getTransId() {
        return m_transId;
    }

    double getQuantity() {
        return m_quantity;
    }
private:
    string m_transId;
    double m_quantity;
};


class ExportFooterModel {
public:
    ExportFooterModel(string exportUser) : m_exportUser(exportUser) {
    }

    string getExportUser() {
        return m_exportUser;
    }
private:
    string m_exportUser;
};


// 建造器
class Builder {
public:
    virtual void builderHeader(ExportHeaderModel& ehm) = 0;

    virtual void builderBody(vector<ExportDataModel*>& edmCollection) = 0;

    virtual void builderFooter(ExportFooterModel& efm) = 0;

    virtual void output() = 0;
protected:
    Builder() {}
};

class TextBuilder : public Builder {
public:
    void builderHeader(ExportHeaderModel& ehm) {
        m_result += ehm.getDepId() + ", " + ehm.getExportDate() + "\n";   
    }

    void builderBody(vector<ExportDataModel*>& edmCollection) {
        for (vector<ExportDataModel*>::iterator it = edmCollection.begin(); it != edmCollection.end(); it++) {
            m_result += (*it)->getTransId() + " : " + convertToString((*it)->getQuantity()) + "\n";
        }
    }

    void builderFooter(ExportFooterModel& efm) {
        m_result += efm.getExportUser() + "\n";
    }

    void output() {
        cout << m_result;
    }
private:
    string m_result;
};

class XmlBuilder : public Builder {
public:
    void builderHeader(ExportHeaderModel& ehm) {
        m_result.append("<header>\n");
        m_result.append("    <depId>");
        m_result.append(ehm.getDepId());
        m_result.append("</depId>\n");
        m_result.append("    <exportDate>");
        m_result.append(ehm.getExportDate());
        m_result.append("</exportDate>\n");
        m_result.append("</header>\n");
    }

    void builderBody(vector<ExportDataModel*>& edmCollection) {
        m_result.append("<body>\n");
        for (vector<ExportDataModel*>::iterator it = edmCollection.begin(); it != edmCollection.end(); it++) {
            m_result.append("    <data>\n");
            m_result.append("        <transId>");
            m_result.append((*it)->getTransId());
            m_result.append("</transId>\n");
            m_result.append("        <quantity>");
            m_result.append(convertToString((*it)->getQuantity()));
            m_result.append("</quantity>\n");
            m_result.append("    </data>\n");
        }
        m_result.append("</body>\n");
    }

    void builderFooter(ExportFooterModel& efm) {
        m_result.append("<footer>\n");
        m_result.append("    <user>");
        m_result.append(efm.getExportUser());
        m_result.append("</user>\n");
        m_result.append("</footer>\n");
    }

    void output() {
        cout << m_result;
    }
private:
    string m_result;
};


class Director {
public:
    Director(Builder *builder) : pBuilder(builder) {}

    /*
        建造者模式不一定是链式调用的，链式调用更加简洁
        建造过程一样
    */
    void doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm) {
        pBuilder->builderHeader(ehm);
        pBuilder->builderBody(edmCollection);
        pBuilder->builderFooter(efm);
        pBuilder->output();
    }
private:
    Builder *pBuilder;
};


/*
一个对账周期可能会有多笔交易记录

将不变的暴露给 客户端，将可变的隐藏到内部
*/
int main() {

    ExportHeaderModel* pEhm = new  ExportHeaderModel("部门", "6月1日");

    ExportDataModel* pEdm1 = new ExportDataModel("111", 10000.0);
    ExportDataModel* pEdm2 = new ExportDataModel("222", 20000.0);
    ExportDataModel* pEdm3 = new ExportDataModel("333", 30000.0);
    vector<ExportDataModel*> myVec;
    myVec.push_back(pEdm1);
    myVec.push_back(pEdm2);
    myVec.push_back(pEdm3);

    ExportFooterModel* pEfm = new ExportFooterModel("张三");

    cout << "************************************* text" << endl;
    TextBuilder *pText = new TextBuilder();
    pText->builderHeader(*pEhm);
    pText->builderBody(myVec);
    pText->builderFooter(*pEfm);
    pText->output();

    cout << "************************************* xml" << endl;
    XmlBuilder *pXml = new XmlBuilder();
    pXml->builderHeader(*pEhm);
    pXml->builderBody(myVec);
    pXml->builderFooter(*pEfm);
    pXml->output();

    cout << "************************************* text" << endl;
    TextBuilder *pt = new TextBuilder();
    (new Director(pt))->doExport(*pEhm, myVec, *pEfm);

    cout << "************************************* xml" << endl;
    XmlBuilder *px = new XmlBuilder();
    (new Director(px))->doExport(*pEhm, myVec, *pEfm);

    return 0;
}
