#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 前向声明
class Circle;
class Rectangle;
class Triangle;

// 抽象访问者
class ShapeVisitor {
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Rectangle& rectangle) = 0;
    virtual void visit(Triangle& triangle) = 0;
};

// 抽象元素
class Shape {
public:
    virtual void accept(ShapeVisitor& visitor) = 0;
};

// 具体元素 - 圆形
class Circle : public Shape {
public:
    Circle(double radius) : m_radius(radius) {}

    double getRadius() const {
        return m_radius;
    }

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double m_radius;
};

// 具体元素 - 矩形
class Rectangle : public Shape {
public:
    Rectangle(double width, double height) : m_width(width), m_height(height) {}

    double getWidth() const {
        return m_width;
    }

    double getHeight() const {
        return m_height;
    }

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }

private:
    double m_width;
    double m_height;
};

class Triangle : public Shape {
public:
    Triangle(double a, double b, double c) : m_a(a), m_b(b), m_c(c) {}

    double getA() {
        return m_a;
    }

    double getB() {
        return m_b;
    }

    double getC() {
        return m_c;
    }

    void accept(ShapeVisitor& visitor) override {
        visitor.visit(*this);
    }
private:
    double m_a;
    double m_b;
    double m_c;
};

// 对象结构
class ShapeCollection {
public:
    void addShape(Shape* shape) {
        m_shapes.push_back(shape);
    }

    void acceptVisitor(ShapeVisitor& visitor) {
        for (Shape* shape : m_shapes) {
            shape->accept(visitor);
        }
    }

private:
    vector<Shape*> m_shapes;
};

// 具体访问者 - 计算面积
class AreaVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        double area = 3.14 * circle.getRadius() * circle.getRadius();
        cout << "Area of Circle: " << area << endl;
    }

    void visit(Rectangle& rectangle) override {
        double area = rectangle.getWidth() * rectangle.getHeight();
        cout << "Area of Rectangle: " << area << endl;
    }

    /*
        已知三角形三边a,b,c，则
        海伦公式:
            p=(a+b+c)/2
            S=sqrt[p(p-a)(p-b)(p-c)]
             =sqrt[(1/16)(a+b+c)(a+b-c)(a+c-b)(b+c-a)]
             =1/4sqrt[(a+b+c)(a+b-c)(a+c-b)(b+c-a)]
    */
    void visit(Triangle& triangle) override {
        double a = triangle.getA();
        double b = triangle.getB();
        double c = triangle.getC();
        double p = (a+b+c)/2;
        // 1 / 4 == 0
        // double area = 1.0 / 4.0 * sqrt((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c));
        double area = sqrt(p*(p-a)*(p-b)*(p-c));
        cout << "Area of Triangle: " << area << endl;
    }
};

// 具体访问者 - 计算周长
class PerimeterVisitor : public ShapeVisitor {
public:
    void visit(Circle& circle) override {
        double perimeter = 2.0 * 3.14 * circle.getRadius();
        cout << "Perimeter of Circle: " << perimeter << endl;
    }

    void visit(Rectangle& rectangle) override {
        double perimeter = 2.0 * (rectangle.getWidth() + rectangle.getHeight());
        cout << "Perimeter of Rectangle: " << perimeter << endl;
    }

    void visit(Triangle& triangle) override {
        double perimeter = triangle.getA() + triangle.getB() + triangle.getC();
        cout << "Perimeter of Triangle: " << perimeter << endl;
    }
};


/*
访问者模式
    允许在运行时根据两个不同的类型来决定要执行的操作。

访问者模式通常用于以下情况：
    当一个数据结构包含多种不同类型的对象，而且希望对这些对象执行一系列不同的操作时。
    当希望为数据结构中的每种对象类型定义不同的操作，但不希望在每个对象类中添加这些操作的代码。
    当需要在不修改现有代码的情况下向已有的对象结构添加新的操作。

访问者模式通常包括以下几个关键角色：
    Visitor(访问者)：访问者是一个抽象类或接口，定义了一组访问不同元素的方法，每个方法对应一个具体元素类型。
    ConcreteVisitor(具体访问者)：具体访问者是实现访问者接口的具体类，它提供了对不同元素的具体操作。

    Element(元素)：元素是一个抽象类或接口，定义了一个接受访问者的方法(accept方法)，并将自身作为参数传递给访问者。
    ConcreteElement(具体元素)：具体元素是实现元素接口的具体类，它实现了accept方法，并通常包含一些状态或数据。

    ObjectStructure(对象结构)：对象结构是一个容纳多个元素的集合，通常提供方法来让访问者访问这些元素。
*/
int main() {
    Circle circle(100.0);
    Rectangle rectangle(4.0, 6.0);
    Triangle triangle(3.0, 4.0, 5.0);

    ShapeCollection sc;
    sc.addShape(&circle);
    sc.addShape(&rectangle);
    sc.addShape(&triangle);

    AreaVisitor areaVisitor;
    PerimeterVisitor perimeterVisitor;

    sc.acceptVisitor(areaVisitor);
    sc.acceptVisitor(perimeterVisitor);

    return 0;
}
