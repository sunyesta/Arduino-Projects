

#ifndef LOOP_MANAGER_HPP
#define LOOP_MANAGER_HPP

class Loopable;

class LoopManager {
   private:
    static const int maxLoopable = 20;
    int loopableCount = 0;
    Loopable *loopables[maxLoopable];

   public:
    LoopManager();
    int connect(Loopable *loopable);
    void loop();
};

extern LoopManager *loopManager;

#endif /* LOOP_MANAGER_HPP */