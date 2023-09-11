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


class ExportToTextHelper {
public:
    void doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm);
};

void ExportToTextHelper::doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm) {
    string tmp = "";
    //header
    tmp += ehm.getDepId() + ", " + ehm.getExportDate() + "\n";
    //data
    for (vector<ExportDataModel*>::iterator it = edmCollection.begin(); it != edmCollection.end(); it++) {
        tmp += (*it)->getTransId() + ":" + convertToString((*it)->getQuantity()) + "\n";
        //tmp += (*it)->getTransId() + ":" + (*it)->getQuantity() + "\n";
    }
    //footer
    tmp += efm.getExportUser() + "\n";
    cout << tmp;
}


class ExportToXmlHelper {
public:
    void doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm);
};

void ExportToXmlHelper::doExport(ExportHeaderModel& ehm, vector<ExportDataModel*>& edmCollection, ExportFooterModel& efm) {
    string tmp = "<?xml version='1.0' encoding='utf-8'>\n";

    //header
    tmp.append("<receipt>\n");
    tmp.append("    <header>\n");
    tmp.append("        <depId>");
    tmp.append(ehm.getDepId());
    tmp.append("</depId>\n");
    tmp.append("        <exportDate>");
    tmp.append(ehm.getExportDate());
    tmp.append("</exportDate>\n");
    tmp.append("    </header>\n");

    //data
    tmp.append("    <body>\n");
    for (vector<ExportDataModel*>::iterator it = edmCollection.begin(); it != edmCollection.end(); it++) {
        tmp.append("        <data>\n");
        tmp.append("            <transId>");
        tmp.append((*it)->getTransId());
        tmp.append("</transId>\n");
        tmp.append("            <quantity>");
        tmp.append(convertToString((*it)->getQuantity()));
        tmp.append("</quantity>\n");
        tmp.append("        </data>\n");
    }
    tmp.append("    </body>\n");

    //footer
    tmp.append("    <footer>\n");
    tmp.append("        <user>");
    tmp.append(efm.getExportUser());
    tmp.append("</user>\n");
    tmp.append("    </footer>\n");
    tmp.append("</receipt>\n");

    cout << tmp;
};


/*
一个对账周期可能会有多笔交易记录
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

    ExportToTextHelper* pEtth = new ExportToTextHelper();
    pEtth->doExport(*pEhm, myVec, *pEfm);

    ExportToXmlHelper* pEtxh = new ExportToXmlHelper();
    pEtxh->doExport(*pEhm, myVec, *pEfm);

    return 0;
}
