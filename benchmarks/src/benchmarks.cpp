#include <DisplayObjectContainer.h>
#include <iostream>
#include "Stage.h"

using Stage = flash::display::Stage;
using DisplayObjectContainer = flash::display::DisplayObjectContainer;
using DisplayObject = flash::display::DisplayObject;

#define W 800
#define H 600

class HighResolutionTimer {
public:
    HighResolutionTimer()
            : m_startTime(takeTimeStamp()) {}

    void restart() {
        m_startTime = takeTimeStamp();
    }

    double elapsed() const {
        return double(takeTimeStamp() - m_startTime) * 1e-9;
    }

    std::uint64_t elapsedNanoseconds() {
        return takeTimeStamp() - m_startTime;
    }

private:
    static std::uint64_t takeTimeStamp() {
        return std::uint64_t(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    }

    std::uint64_t m_startTime;
};

class FrameCounterStage : public Stage {
public:
    FrameCounterStage()
        : Stage(W, H) {}

    ~FrameCounterStage() {}

    void draw(flash::render::Context& context, flash::render::RenderState& state) override {
        DisplayObjectContainer::draw(context, state);
        if (++m_currentFrame == m_numFrames) {
            stop();
        }
    };

    void setNumFrames(int value) {
        m_numFrames = value;
    }

    int numFrames() const {
        return m_numFrames;
    }

private:
    int m_numFrames{1};
    int m_currentFrame{0};
};

namespace {
    std::vector<DisplayObject*> _objects;
    
    void _deleteObjects() {
        for (DisplayObject* obj : _objects) {
            delete obj;
        }
        _objects.clear();
    }

    DisplayObject* _addNewObjectTo(DisplayObjectContainer* parent) {
        DisplayObject* object = new DisplayObject();
        parent->addChild(object);
        _objects.push_back(object);
        return object;
    }

    DisplayObjectContainer* _addNewContainerTo(DisplayObjectContainer* parent) {
        DisplayObjectContainer* cont = new DisplayObjectContainer();
        parent->addChild(cont);
        _objects.push_back(cont);
        return cont;
    }

    void _outputLoopTime(double time, int frames) {
        std::cout << "    total objects: " << _objects.size() << std::endl;
        std::cout << "    loop time (frames: " << frames << "): " << time << std::endl;
        std::cout << "    frame time: " << time / frames << std::endl;
        std::cout << "    fps: " << 1 / (time / frames) << std::endl;
    }
}

void benchmarkDeepTree() {
    FrameCounterStage stage;
    stage.init();
    stage.setNumFrames(100);
    std::cout << "----------------------------------" << std::endl;
    std::cout << "deep tree" << std::endl;

    _objects.clear();
    _objects.reserve(100);
    
    DisplayObjectContainer* currentCont = &stage;
    for (int i = 0; i < 98; ++i) {
        currentCont = _addNewContainerTo(currentCont);
    }
    _addNewObjectTo(currentCont);

    HighResolutionTimer timer;
    stage.start();
    _outputLoopTime(timer.elapsed(), stage.numFrames());
    _deleteObjects();
}

void benchmarkFlatTree() {
    FrameCounterStage stage;
    stage.init();
    stage.setNumFrames(100);
    std::cout << "----------------------------------" << std::endl;
    std::cout << "flat tree" << std::endl;

    _objects.clear();
    _objects.reserve(300);

    DisplayObjectContainer* cont = _addNewContainerTo(&stage);
    for (int i = 0; i < 200; ++i) {
        _addNewObjectTo(cont);
    }

    HighResolutionTimer timer;
    stage.start();
    _outputLoopTime(timer.elapsed(), stage.numFrames());
    _deleteObjects();
}

void benchmarkNormalTree() {
    FrameCounterStage stage;
    stage.init();
    stage.setNumFrames(30);
    std::cout << "----------------------------------" << std::endl;
    std::cout << "normal tree" << std::endl;

    _objects.clear();
    _objects.reserve(500000);

    std::vector<int> arr = {1, 3, 2, 1, 4, 2};
    int arrInd = 0;

    DisplayObjectContainer* currentCont{nullptr};
    DisplayObjectContainer* cont = _addNewContainerTo(&stage);
    int beginIndex = 0;
    int endIndex = 1;
    for (int i = 0; i < 19; ++i) {
        int numChildren = arr[arrInd];
        for (int j = beginIndex; j < endIndex; ++j) {
            currentCont = static_cast<DisplayObjectContainer*>(_objects[j]);
            for (int k = 0; k < numChildren; ++k) {
                _addNewContainerTo(currentCont);
            }
        }
        beginIndex = endIndex;
        endIndex = (int) _objects.size();
        if (++arrInd == arr.size())
            arrInd = 0;
    }
    for (int i = beginIndex; i < endIndex; ++i) {
        currentCont = static_cast<DisplayObjectContainer*>(_objects[i]);
        _addNewObjectTo(currentCont);
    }

    HighResolutionTimer timer;
    stage.start();
    _outputLoopTime(timer.elapsed(), stage.numFrames());
    _deleteObjects();
}

int main(int argc, char** argv) {
    benchmarkDeepTree();
    benchmarkFlatTree();
    benchmarkNormalTree();
}
