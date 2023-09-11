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
    //对账单的部门id
    string m_strDepId;
    //对账单的导出日期
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


// class ExportToTextHelper {
// public:
//     void doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm);
// };

// void ExportToTextHelper::doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm) {
//     string tmp = "";
//     cout << tmp;
// }


// class ExportToXmlHelper {
// public:
//     void doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm);
// };

// void ExportToXmlHelper::doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm) {
//     string tmp = "<?xml version='1.0' encoding='utf-8'>\n";

//     //header
//     tmp.append("<receipt>\n");

//     tmp.append("</receipt>\n");

//     cout << tmp;
// };

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
            m_result += (*it)->getTransId() + ":" + convertToString((*it)->getQuantity()) + "\n";
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
        m_result.append("    <header>\n");
        m_result.append("        <depId>");
        m_result.append(ehm.getDepId());
        m_result.append("</depId>\n");
        m_result.append("        <exportDate>");
        m_result.append(ehm.getExportDate());
        m_result.append("</exportDate>\n");
        m_result.append("    </header>\n");
    }

    void builderBody(vector<ExportDataModel*>& edmCollection) {
        m_result.append("    <body>\n");
        for (vector<ExportDataModel*>::iterator it = edmCollection.begin(); it != edmCollection.end(); it++) {
            m_result.append("        <data>\n");
            m_result.append("            <transId>");
            m_result.append((*it)->getTransId());
            m_result.append("</transId>\n");
            m_result.append("            <quantity>");
            m_result.append(convertToString((*it)->getQuantity()));
            m_result.append("</quantity>\n");
            m_result.append("        </data>\n");
        }
        m_result.append("    </body>\n");
    }

    void builderFooter(ExportFooterModel& efm) {
        m_result.append("    <footer>\n");
        m_result.append("        <user>");
        m_result.append(efm.getExportUser());
        m_result.append("</user>\n");
        m_result.append("    </footer>\n");
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

    ExportHeaderModel* pEhm = new  ExportHeaderModel("NewB", "6月1日");

    ExportDataModel* pEdm = new ExportDataModel("1", 10000.0);
    ExportDataModel* pEdm2 = new ExportDataModel("2", 20000.0);
    ExportDataModel* pEdm3 = new ExportDataModel("3", 30000.0);
    vector<ExportDataModel*> myVec;
    myVec.push_back(pEdm);
    myVec.push_back(pEdm2);
    myVec.push_back(pEdm3);

    ExportFooterModel* pEfm = new ExportFooterModel("Jerry");

    // TextBuilder *pText = new TextBuilder();
    // pText->builderHeader(*pEhm);
    // pText->builderBody(myVec);
    // pText->builderFooter(*pEfm);
    // pText->output();

    // XmlBuilder *pXml = new XmlBuilder();
    // pXml->builderHeader(*pEhm);
    // pXml->builderBody(myVec);
    // pXml->builderFooter(*pEfm);
    // pXml->output();

    TextBuilder *pText = new TextBuilder();
    (new Director(pText))->doExport(*pEhm, myVec, *pEfm);

    XmlBuilder *pXml = new XmlBuilder();
    (new Director(pXml))->doExport(*pEhm, myVec, *pEfm);

    return 0;
}
