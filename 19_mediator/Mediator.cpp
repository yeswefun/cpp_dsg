#include <iostream>

using namespace std;


class Colleague;

class Mediator {
public:
    // 通知 Mediator 处理同事对象的交互
    virtual void changed(Colleague *c) = 0;
protected:
    Mediator() {}
};

class Colleague {
public:
    Colleague() {}
    Colleague(Mediator *m) : m_mediator(m) {}
    Mediator* getMediator() {
        return m_mediator;
    }
private:
    Mediator *m_mediator;
};


class SoundCard : public Colleague {
public:
    SoundCard(Mediator *m) : Colleague(m) {}
    void soundData(string data) {
        cout << "sound: " << data << endl;
    }
};

class VideoCard : public Colleague {
public:
    VideoCard(Mediator *m): Colleague(m) {}
    void videoData(string data) {
        cout << "video: " << data << endl;
    }
};

class CPU : public Colleague {
public:
    CPU(Mediator *m) : Colleague(m) {}
    void executeData(string data[]) {
        m_soundData = data[0];
        m_videoData = data[1];
        this->getMediator()->changed(this);
    }

    string getVideoData() {
        return m_videoData;
    }

    string getSoundData() {
        return m_soundData;
    }
private:
    string m_soundData;
    string m_videoData;
};


class MotherBoard : public Mediator {
public:
    void setCPU(CPU *cpu) {
        m_cpu = cpu;
    }

    void setVideoCard(VideoCard *videoCard) {
        m_videoCard = videoCard;
    }

    void setSoundCard(SoundCard *soundCard) {
        m_soundCard = soundCard;
    }

    void changed(Colleague *c) {
        if (c == m_cpu) {
            this->openCPU((CPU*)c);
        }
    }
private:
    void openCPU(CPU *cpu) {
        string videoData = cpu->getVideoData();
        string soundData = cpu->getSoundData();
        m_soundCard->soundData(soundData);
        m_videoCard->videoData(videoData);
    }
private:
    CPU *m_cpu;
    SoundCard *m_soundCard;
    VideoCard *m_videoCard;
};


/*
中介者
*/
int main() {

    MotherBoard *mediator = new MotherBoard;

    //创建 Colleague 对象
    CPU *pCPU = new CPU(mediator);
    VideoCard *pVC = new VideoCard(mediator);
    SoundCard *pSC = new SoundCard(mediator);

    //让 mediator 知道有这些 Colleague 对象
    mediator->setCPU(pCPU);
    mediator->setSoundCard(pSC);
    mediator->setVideoCard(pVC);

    string arr[] = {"Hello", "World"};
    pCPU->executeData(arr);

    return 0;
}
