#include <iostream>

using namespace std;

//Receiver
class Light {
public:
    void on() {
        cout << "light on" << endl;
    }
    void off() {
        cout << "light off" << endl;
    }
};

/*
turn on the light
turn off the light

抽象出一个类，专门记录动作行为，而不管是什么灯(红灯，蓝灯，绿灯)
*/
class Command {
public:
    virtual void execute() = 0;
protected:
    Command() {}
};

//具体的命令对象，只触发动作，用来开灯
//持有一个 Receiver 的实例，让这个 Receiver 去处理
//真正动作的执行 是通过将 真实设备(Light) 组合到 动作(LightOnCommand)
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

//Invoker 可以触发任意命令对象
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
    ...

只要关注 Invoker，并且对 Invoker 进行控制，就可以对一系列"动作"记录下来

对调用进行封装
*/
int main() {

    //Invoker
    SimpleRemoteControl * ctl = new SimpleRemoteControl;
    
    //Receiver
    Light *light = new Light;

    //Command
    LightOnCommand *cmdOn = new LightOnCommand(light);
    LightOffCommand *cmdOff = new LightOffCommand(light);

    ctl->setCommand(cmdOn);
    ctl->buttonPressed(); // Invoker -> Command -> Receiver -> Action

    ctl->setCommand(cmdOff);
    ctl->buttonPressed();

    return 0;
}
