#include <iostream>
#include <cstring>

using namespace std;

class CView {
public:
    virtual void draw() {}
};

class CDecorate : public CView {
public:
    CDecorate(CView *view) : m_view(view) {}

    void draw() {
        m_view->draw();
    }
private:
    CView *m_view;
};

class CScrollBar : public CDecorate {
public:
    CScrollBar(CView *view) : CDecorate(view) {}
protected:
    void drawScrollBars() {
        cout << "draw ScrollBar" << endl;
    }
public:
    void draw() {
        CDecorate::draw();
        drawScrollBars();
    }
};

class CBorder : public CDecorate {
public:
    CBorder(CView *view) : CDecorate(view) {}
protected:
    void drawBorder() {
        cout << "draw Border" << endl;
    }
public:
    void draw() {
        CDecorate::draw();
        drawBorder();
    }
};

//Context -> 主要的被装饰对象
class CTextView : public CView {
public:
    CTextView(const char *s) {
        setWindowText(s);
    }

    void setWindowText(const char *s) {
        strcpy_s(m_text, _countof(m_text), s);
    }

    char* getWindowText() {
        return m_text;
    }

    void draw() {
        CView::draw();
        drawTextView();
    }
protected:
    virtual void drawTextView() {
        cout << "draw TextView, text: " << m_text << endl;
    }
protected:
    char m_text[32];
};


class CWindows {
public:
    CWindows() {
        //ZeroMemory(m_wins, sizeof(CView*) * 8);
        memset(m_wins, 0, sizeof(CView*) * 8);
    }
    void draw() {
        for (int i = 0; i < 8; i++) {
            if (m_wins[i] != nullptr) {
                m_wins[i]->draw();
            }
        }
    }
    void addControl(CView *view) {
        for (int i = 0; i < 8; i++) {
            if (m_wins[i] == nullptr) {
                m_wins[i] = view;
                break;
            }
        }
    }
    void removeControl(CView *view) {
        for (int i = 0; i < 8; i++) {
            if (m_wins[i] == view) {
                m_wins[i] = nullptr;
                break;
            }
        }
    }
protected:
    CView* m_wins[8];
};


int main() {
    
    CWindows wins;
    
    cout << "*********************" << endl;
    CTextView tv("this is a TextView");
    wins.addControl(&tv);
    wins.draw();

    cout << "*********************" << endl;
    //wins.removeControl(&tv);
    CScrollBar *sv = new CScrollBar(&tv);
    wins.addControl(sv);
    wins.draw();

    cout << "*********************" << endl;
    wins.removeControl(&tv);
    wins.removeControl(sv);
    CBorder *border = new CBorder(&tv);
    wins.addControl(border);
    wins.draw();

    return 0;
}
