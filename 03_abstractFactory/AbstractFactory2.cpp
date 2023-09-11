#include <iostream>

using namespace std;


class FrameApi {
public:
    virtual void draw() = 0;
protected:
    FrameApi() {
    }
};


class PCFrame : public FrameApi {
public:
    PCFrame(int pins) : m_pins(pins) {
    }
    void draw() {
        cout << "PC#draw" << endl;
    }
private:
    int m_pins;
};


class MobileFrame : public FrameApi {
public:
    MobileFrame(int pins) : m_pins(pins) {
    }
    void draw() {
        cout << "Mobile#draw" << endl;
    }
private:
    int m_pins;
};


class LayoutApi {
public:
    virtual void installFrame() = 0;
protected:
    LayoutApi() {
    }
};

class HighLayout : public LayoutApi {
public:
    HighLayout(int frameAdapterPins) : m_frameAdapterPins(frameAdapterPins) {
    }
    void installFrame() {
        cout << "HighLayout -> pins: " << m_frameAdapterPins << endl;
    }
private:
    int m_frameAdapterPins;
};


class LowLayout : public LayoutApi {
public:
    LowLayout(int frameAdapterPins) : m_frameAdapterPins(frameAdapterPins) {
    }
    void installFrame() {
        cout << "LowLayout -> pins: " << m_frameAdapterPins << endl;
    }
private:
    int m_frameAdapterPins;
};



//抽象工厂用来定义产品簇
class AbstractFactory {
public:
    virtual FrameApi* createFrameApi() = 0;
    virtual LayoutApi* createLayoutApi() = 0;
protected:
    AbstractFactory() {
    }
};

class Schema1 : public AbstractFactory {
public:
    FrameApi* createFrameApi() {
        return new PCFrame(1024);
    }
    LayoutApi* createLayoutApi() {
        return new HighLayout(1024);
    }
};

class Schema2 : public AbstractFactory {
public:
    FrameApi* createFrameApi() {
        return new MobileFrame(800);
    }
    LayoutApi* createLayoutApi() {
        return new LowLayout(800);
    }
};

class AdvancedGuiEngineer {
public:
    void prepareMaterials(AbstractFactory *schema) {
        this->pFrame = schema->createFrameApi();
        this->pLayout = schema->createLayoutApi();
        pFrame->draw();
        pLayout->installFrame();
    }
private:
    FrameApi* pFrame;
    LayoutApi* pLayout;
};

/*
HighLayout -> PCFrame
LowLayout -> MobileFrame

抽象工厂 相当于 套餐
    有固定搭配
*/
int main() {
    AdvancedGuiEngineer* pEng =  new AdvancedGuiEngineer();
    pEng->prepareMaterials(new Schema1());
    pEng->prepareMaterials(new Schema2());
    return 0;
}
