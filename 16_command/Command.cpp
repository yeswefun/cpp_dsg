#include <iostream>

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
private:
    Light *m_light;
};

class LightOffCommand : public Command {
public:
    LightOffCommand(Light *light) : m_light(light) {}

    void execute() {
        m_light->off();
    }
private:
    Light *m_light;
};

//Invoker 可以触发任何命令
class SimpleRemoteControl {
public:
    void setCommand(Command *cmd) {
        m_cmd = cmd;
    }
    void buttonPressed() {
        m_cmd->execute();
    }
private:
    Command *m_cmd;
};


/*
Canvas
    DrawPointCommand
    DrawLineCommand
    DrawRectCommand
    DrawCircleCommand
Paint
*/
int main() {

    SimpleRemoteControl * ctl = new SimpleRemoteControl;
    
    Light *light = new Light;
    LightOnCommand *cmdOn = new LightOnCommand(light);
    LightOffCommand *cmdOff = new LightOffCommand(light);

    ctl->setCommand(cmdOn);
    ctl->buttonPressed();

    ctl->setCommand(cmdOff);
    ctl->buttonPressed();

    return 0;
}
