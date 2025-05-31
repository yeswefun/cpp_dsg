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

protected:
    OrderApi() {}
};

// 国内订单
class HomeOrder : public OrderApi {
public:
    int getOrderProductNum() {
        return m_orderProductNum;
    }

    void setOrderProductNum(int num) {
        m_orderProductNum = num;
    }

    string getOrderContent() {
        return m_productId + ":" + m_customerName + ":" + covertToString(m_orderProductNum);
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
private:
    string m_customerName;
    string m_productId;
    int m_orderProductNum;
};


// 国外订单
class AboardOrder : public OrderApi {
public:
    int getOrderProductNum() {
        return m_orderProductNum;
    }

    void setOrderProductNum(int num) {
        m_orderProductNum = num;
    }

    string getOrderContent() {
        return m_productId + ":" + m_customerName + ":" + covertToString(m_orderProductNum);
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
private:
    string m_customerName;
    string m_productId;
    int m_orderProductNum;
};


// 订单业务处理
class OrderBusiness {
public:
    void saveOrder(OrderApi *order);
};


/*
对象的快速复制
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
        
        OrderApi *newOrder = nullptr;
        
        if (dynamic_cast<HomeOrder*>(order) != nullptr) {
            HomeOrder *p1 = static_cast<HomeOrder*>(order);
            HomeOrder *p2 = new HomeOrder;
            p2->setOrderProductNum(200);
            p2->setCustomerName(p1->getCustomerName());
            p2->setProductId(p1->getProductId());
            newOrder = p2;
        }

        if (dynamic_cast<AboardOrder*>(order) != nullptr) {
            AboardOrder *p1 = static_cast<AboardOrder*>(order);
            AboardOrder *p2 = new AboardOrder;
            p2->setOrderProductNum(200);
            p2->setCustomerName(p1->getCustomerName());
            p2->setProductId(p1->getProductId());
            newOrder = p2;
        }

        if (newOrder == nullptr) {
            break;
        }
        order->setOrderProductNum(order->getOrderProductNum() - 200);
        cout << "splited order: " << newOrder->getOrderContent() << endl;
    }

    cout << " remain order: " << order->getOrderContent() << endl;
}
