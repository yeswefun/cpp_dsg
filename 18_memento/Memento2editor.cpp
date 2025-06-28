#include <iostream>
#include <string>

using namespace std;

// 备忘录类
class EditorMemento {
public:
    EditorMemento(const string& t) : text(t) {}

    const string& getText() const {
        return text;
    }

private:
    string text;
};

// 文本编辑器类
class TextEditor {
public:
    void setText(const string& t) {
        text = t;
    }

    const string& getText() const {
        return text;
    }

    // 创建备忘录并保存当前状态
    EditorMemento createMemento() const {
        return EditorMemento(text);
    }

    // 从备忘录中恢复状态
    void restoreFromMemento(const EditorMemento& memento) {
        text = memento.getText();
    }

private:
    string text;
};

int main() {
    TextEditor editor;

    // 用户输入文本
    editor.setText("第一行文本\n第二行文本\n第三行文本");
    cout << "===============当前文本内容:\n" << editor.getText() << endl;

    // 创建备忘录并保存当前状态
    EditorMemento memento = editor.createMemento();

    // 用户继续编辑文本
    editor.setText("新的文本内容");

    cout << "===============修改后的文本内容:\n" << editor.getText() << endl;

    // 恢复到之前的状态
    editor.restoreFromMemento(memento);
    cout << "===============恢复后的文本内容:\n" << editor.getText() << endl;

    return 0;
}
