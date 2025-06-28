#include <iostream>
#include <vector>

using namespace std;

class Light {
public:
    void on() {
        cout << "light on" << endl;
    }
    void off() {
        cout << "light off" << endl;
    }
};

//抽象出一个类，专门记录动作行为
class Command {
public:
    virtual void execute() = 0;

    //+++++++++++++++++++++
    virtual void undo() = 0;
protected:
    Command() {}
};

//具体的命令对象
//作用: 用来开灯
//持有一个 Receiver 的实例，让这个 Receiver 去处理
class LightOnCommand : public Command {
public:
    LightOnCommand(Light *light) : m_light(light) {}

    void execute() {
        m_light->on();
    }

    //+++++++++++++++++++++
    void undo() {
        m_light->off();
    }
private:
    Light *m_light;
};

class LightOffCommand : public Command {
public:
    LightOffCommand(Light *light) : m_light(light) {}

    void execute() {
        m_light->off();
    }

    //+++++++++++++++++++++
    void undo() {
        m_light->on();
    }
private:
    Light *m_light;
};

//空命令，设置命令时(第一次操作)，没有撤消命令
class NoCommand : public Command {
public:
    void execute() {}
    void undo() {}
};

//Invoker 可以触发任何命令
class SimpleRemoteControl {
public:
    void setCommand(Command *cmd) {
        cout << "****************** setCommand" << endl;
        m_cmd = cmd;
        m_undo = new NoCommand;
    }
    void onButtonPushed() {
        m_cmd->execute();
        m_undo = m_cmd;
    }
    void offButtonPushed() {
        m_cmd->execute();
        m_undo = m_cmd;
    }
    void undoButtonPushed() {
        m_undo->undo();
    }
private:
    Command *m_cmd;
    Command* m_undo;
};

/*
Undo 撤消操作
*/
int main() {

    SimpleRemoteControl * ctl = new SimpleRemoteControl;
    
    Light *light = new Light;
    LightOnCommand *cmdOn = new LightOnCommand(light);
    LightOffCommand *cmdOff = new LightOffCommand(light);

    ctl->setCommand(cmdOn);
    ctl->onButtonPushed();
    ctl->undoButtonPushed();

    ctl->setCommand(cmdOff);
    ctl->offButtonPushed();
    ctl->undoButtonPushed();

    return 0;
}
