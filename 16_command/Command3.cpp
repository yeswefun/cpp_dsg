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

//空命令
class NoCommand : public Command {
public:
    void execute() {
    }
    void undo() {
    }
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

//宏命令: 多个命令
class MacroCommand : public Command {
public:
    
    MacroCommand(vector<Command*> cmdList) : m_cmdList(cmdList) {}

    void execute() {
        for (vector<Command*>::iterator it = m_cmdList.begin(); it != m_cmdList.end(); it++) {
            (*it)->execute();
        }
    }
    void undo() {
        for (vector<Command*>::iterator it = m_cmdList.begin(); it != m_cmdList.end(); it++) {
            (*it)->undo();
        }
    }
private:
    vector<Command*> m_cmdList;
};

class Sound {
public:
    void on() {
        cout << "sound on" << endl;
    }
    void off() {
        cout << "sound off" << endl;
    }
};

class SoundOnCommand : public Command {
public:
    SoundOnCommand(Sound *sound) : m_sound(sound) {}
    void execute() {
        m_sound->on();
    }
    void undo() {
        m_sound->off();
    }
private:
    Sound *m_sound;
};

//能够批量执行命令的Control
class MacroRemoteControl {
public:
    void setCommand(Command *cmd) {
        m_cmd = cmd;
    }
    void onCommandStart() {
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

Command
    do
    undo
    redo

宏命令: 多个命令
*/
int main() {

    //封装调用，ctl 不直接调用 receiver, 而是通过 invoker 来调用，方便记录命令
    SimpleRemoteControl * ctl = new SimpleRemoteControl;
    
    Light *light = new Light;
    LightOnCommand *cmdOn = new LightOnCommand(light);
    LightOffCommand *cmdOff = new LightOffCommand(light);

    ctl->setCommand(cmdOn);
    ctl->onButtonPushed();
    ctl->undoButtonPushed();
   
    ctl->setCommand(cmdOff);
    ctl->onButtonPushed();
    ctl->undoButtonPushed();

    //宏命令 也是 命令
    vector<Command*> cmdList;
    cmdList.push_back(new SoundOnCommand(new Sound));
    cmdList.push_back(cmdOn);

    cout << "*************** 1" << endl;
    MacroCommand *pMacroCommand = new MacroCommand(cmdList);
    ctl->setCommand(pMacroCommand);
    ctl->onButtonPushed();
    ctl->undoButtonPushed();

    cout << "*************** 2" << endl;
    MacroRemoteControl *mctl = new MacroRemoteControl;
    mctl->setCommand(pMacroCommand);
    mctl->onCommandStart();

    return 0;
}
