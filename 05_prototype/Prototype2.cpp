#include <iostream>
#include <sstream>

using namespace std;

template<class T>
string covertToString(T value) {
    stringstream ss;
    ss << value;
    return ss.str();
}

class OrderApi {
public:
    virtual int getOrderProductNum() = 0;

    virtual void setOrderProductNum(int num) = 0;

    virtual string getOrderContent() = 0;

    // DRY
    virtual OrderApi* cloneOrder() = 0;

protected:
    OrderApi() {}
};

class HomeOrder : public OrderApi {
public:
    int getOrderProductNum() {
        return m_orderProductNum;
    }

    void setOrderProductNum(int num) {
        m_orderProductNum = num;
    }

    string getOrderContent() {
        return m_customerName + ":" + m_productId + ":" + covertToString(m_orderProductNum);
    }

    void setCustomerName(string name) {
        m_customerName = name;
    }

    string getCustomerName() {
        return m_customerName;
    }

    void setProductId(string id) {
        m_productId = id;
    }

    string getProductId() {
        return m_productId;
    }

    OrderApi* cloneOrder() {
        HomeOrder *p = new HomeOrder;
        p->setOrderProductNum(m_orderProductNum);
        p->setCustomerName(m_customerName);
        p->setProductId(m_productId);
        return p;
    }
private:
    string m_customerName;
    string m_productId;
    int m_orderProductNum;
};


class AboardOrder : public OrderApi {
public:
    int getOrderProductNum() {
        return m_orderProductNum;
    }

    void setOrderProductNum(int num) {
        m_orderProductNum = num;
    }

    string getOrderContent() {
        return m_customerName + ":" + m_productId + ":" + covertToString(m_orderProductNum);
    }

    void setCustomerName(string name) {
        m_customerName = name;
    }

    string getCustomerName() {
        return m_customerName;
    }

    void setProductId(string id) {
        m_productId = id;
    }

    string getProductId() {
        return m_productId;
    }

    OrderApi* cloneOrder() {
        AboardOrder *p = new AboardOrder;
        p->setOrderProductNum(m_orderProductNum);
        p->setCustomerName(m_customerName);
        p->setProductId(m_productId);
        return p;
    }
private:
    string m_customerName;
    string m_productId;
    int m_orderProductNum;
};


class OrderBusiness {
public:
    void saveOrder(OrderApi *order);
};

/*
DRY原则: Don't Repeat Yourself
*/
int main() {
    
    HomeOrder *pHome = new HomeOrder;
    pHome->setProductId("1001");
    pHome->setCustomerName("OrderName");
    pHome->setOrderProductNum(512);
    
    cout << "*** 1" << endl;
    OrderBusiness *p = new OrderBusiness;
    p->saveOrder(pHome);
    
    cout << "*** 2" << endl;
    pHome->setOrderProductNum(128);
    p->saveOrder(pHome);

    cout << "*** 3" << endl;
    pHome->setOrderProductNum(1024);
    p->saveOrder(pHome);

    return 0;
}

void OrderBusiness::saveOrder(OrderApi *order) {
    //超过200，则进行拆分
    while (order->getOrderProductNum() > 200) {       
        OrderApi *newOrder = order->cloneOrder();
        newOrder->setOrderProductNum(200);
        order->setOrderProductNum(order->getOrderProductNum() - 200);
        cout << "splited order: " << newOrder->getOrderContent() << endl;
    }

    cout << " remain order: " << order->getOrderContent() << endl;
}
