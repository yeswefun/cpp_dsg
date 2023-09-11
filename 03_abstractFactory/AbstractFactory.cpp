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


//创建产品的简单工厂
class FrameFactory {
public:
    static FrameApi* createFrame(int type) {
        if (type == 1) {
            return new PCFrame(1024);
        } else if (type == 2) {
            return new MobileFrame(800);
        }
        return nullptr;
    }
};

class LayoutFactory {
public:
    static LayoutApi* createLayout(int type) {
        if (type == 1) {
            return new HighLayout(1024);
        } else if (type == 2) {
            return new LowLayout(800);
        }
        return nullptr;
    }
};


class GUIEngineer {
public:
    void prepareDraw(int frameType, int layoutType) {
        // if (this->pFrame) {
        //     delete this->pFrame;
        // }
        // if (this->pLayout) {
        //     delete this->pFrame;
        // }
        this->pFrame = FrameFactory::createFrame(frameType);
        this->pLayout = LayoutFactory::createLayout(layoutType);
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
*/
int main() {
    GUIEngineer *pEng = new GUIEngineer;
    pEng->prepareDraw(1, 1);
    // pEng->prepareDraw(1, 2); // not match
    // pEng->prepareDraw(2, 1); // not match
    pEng->prepareDraw(2, 2);
    return 0;
}
