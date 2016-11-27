#include <DisplayObjectContainer.h>
#include <iostream>
#include "Stage.h"
#include "Shape.h"

using Stage = flash::display::Stage;
using DisplayObjectContainer = flash::display::DisplayObjectContainer;
using DisplayObject = flash::display::DisplayObject;
using Shape = flash::display::Shape;

#define W 800
#define H 600

namespace benchmark {
    
    void _outputLoopTime(double time, int frames);
    
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
    
    HighResolutionTimer _timer;
    
    class BaseBenchmark {
    public:
        virtual void SetUp() = 0;
        
        virtual void TearDown() {}
        
        void run() {
            std::cout << "----------------------------------" << std::endl;
            std::cout << m_name << std::endl;
            _timer.restart();
        }
        
        void finish() {
            _outputLoopTime(_timer.elapsed(), m_frames);
        }
        
        void setFrames(int frames) { m_frames = frames; }
        
        void setName(const std::string& name) { m_name = name; }
        
        const std::string& name() const { return m_name; }
    
    private:
        std::string m_name{""};
        int m_frames{0};
    };
    
    std::vector<BaseBenchmark*> _benchmarks;
    std::vector<int> _frames;
    int _currentBenchmarkIndex{-1};
    
    class FrameCounterStage : public Stage {
    public:
        FrameCounterStage()
                : Stage(W, H) {}
        
        ~FrameCounterStage() {}
        
        void preRender(flash::render::RenderState& state) override {
            if (m_currentFrame++ == m_numFrames) {
                if (_currentBenchmarkIndex >= 0) {
                    _benchmarks[_currentBenchmarkIndex]->finish();
                    _benchmarks[_currentBenchmarkIndex]->TearDown();
                    clear();
                }
                ++_currentBenchmarkIndex;
                if (_currentBenchmarkIndex == _benchmarks.size()) {
                    stop();
                } else {
                    m_currentFrame = 0;
                    m_numFrames = _frames[_currentBenchmarkIndex];
                    _benchmarks[_currentBenchmarkIndex]->SetUp();
                    _benchmarks[_currentBenchmarkIndex]->run();
                }
            }
            DisplayObjectContainer::preRender(state);
        };
    
    private:
        int m_numFrames{0};
        int m_currentFrame{0};
    };
    
    FrameCounterStage* _stage;

    DisplayObject* _addNewObjectTo(DisplayObjectContainer* parent) {
        DisplayObject* object = new Shape();
        parent->addChild(object);
        return object;
    }

    DisplayObjectContainer* _addNewContainerTo(DisplayObjectContainer* parent) {
        DisplayObjectContainer* cont = new DisplayObjectContainer();
        parent->addChild(cont);
        return cont;
    }

    void _outputLoopTime(double time, int frames) {
        std::cout << "    total objects: " << _stage->treeSize() << std::endl;
        std::cout << "    loop time (frames: " << frames << "): " << time << std::endl;
        std::cout << "    frame time: " << time / frames << std::endl;
        std::cout << "    fps: " << 1 / (time / frames) << std::endl;
    }
    
    void _initBenchmarks() {
        _stage = new FrameCounterStage();
    }
    
    void _runBenchmarks() {
        _stage->start();
    }
    
    class DeepTree : public BaseBenchmark {
    public:
        void SetUp() override {
            DisplayObjectContainer* currentCont = _stage;
            for (int i = 0; i < 98; ++i) {
                currentCont = _addNewContainerTo(currentCont);
            }
            _addNewObjectTo(currentCont);
        }
    };
    
    class FlatTree : public BaseBenchmark {
    public:
        void SetUp() override {
            DisplayObjectContainer* cont = _addNewContainerTo(_stage);
            for (int i = 0; i < 200; ++i) {
                _addNewObjectTo(cont);
            }
        }
    };
    
    class NormalTree : public BaseBenchmark {
    public:
        void SetUp() override {
            std::vector<int> arr = {1, 3, 2, 1, 4, 2};
            int arrInd = 0;
    
            std::vector<DisplayObject*> objects;
            objects.reserve(160000);
                    
            DisplayObjectContainer* currentCont{nullptr};
            objects.push_back(_addNewContainerTo(_stage));
            int beginIndex = 0;
            int endIndex = 1;
            for (int i = 0; i < 17; ++i) {
                int numChildren = arr[arrInd];
                for (int j = beginIndex; j < endIndex; ++j) {
                    currentCont = static_cast<DisplayObjectContainer*>(objects[j]);
                    for (int k = 0; k < numChildren; ++k) {
                        objects.push_back(_addNewContainerTo(currentCont));
                    }
                }
                beginIndex = endIndex;
                endIndex = (int) objects.size();
                if (++arrInd == arr.size())
                    arrInd = 0;
            }
            for (int i = beginIndex; i < endIndex; ++i) {
                currentCont = static_cast<DisplayObjectContainer*>(objects[i]);
                _addNewObjectTo(currentCont);
            }
        }
    };
    
    class NormalTreeWithInvisibleChildren : public BaseBenchmark {
    public:
        void SetUp() override {
            std::vector<DisplayObject*> objects;
            objects.reserve(160000);
    
            std::vector<int> arr = {1, 3, 2, 1, 4, 2};
            int arrInd = 0;
    
            int invisIndex = 20;
    
            DisplayObjectContainer* currentCont{nullptr};
            objects.push_back(_addNewContainerTo(_stage));
            int beginIndex = 0;
            int endIndex = 1;
            for (int i = 0; i < 17; ++i) {
                int numChildren = arr[arrInd];
                for (int j = beginIndex; j < endIndex; ++j) {
                    currentCont = static_cast<DisplayObjectContainer*>(objects[j]);
                    if (j && j % invisIndex == 0) {
                        currentCont->setVisible(false);
                        ++m_numInvisible;
                    }
                    for (int k = 0; k < numChildren; ++k) {
                        objects.push_back(_addNewContainerTo(currentCont));
                    }
                }
                beginIndex = endIndex;
                endIndex = (int) objects.size();
                if (++arrInd == arr.size())
                    arrInd = 0;
            }
            for (int i = beginIndex; i < endIndex; ++i) {
                currentCont = static_cast<DisplayObjectContainer*>(objects[i]);
                if (i % invisIndex == 0) {
                    currentCont->setVisible(false);
                    ++m_numInvisible;
                }
                _addNewObjectTo(currentCont);
            }
        }
    
        void TearDown() override {
            std::cout << "    invisible objects: " << m_numInvisible << std::endl;
        }
        
    private:
        int m_numInvisible{0};
    };
}

#define BENCHMARK(benchmarkClass, frames)     \
    _benchmarks.push_back(new benchmarkClass()); \
    _frames.push_back(frames); \
    _benchmarks[_benchmarks.size() - 1]->setName(#benchmarkClass); \
    _benchmarks[_benchmarks.size() - 1]->setFrames(frames)

int main(int argc, char** argv) {
    using namespace benchmark;
    _initBenchmarks();
    BENCHMARK(DeepTree, 100);
    BENCHMARK(FlatTree, 100);
    BENCHMARK(NormalTree, 100);
    BENCHMARK(NormalTreeWithInvisibleChildren, 100);
    _runBenchmarks();
}