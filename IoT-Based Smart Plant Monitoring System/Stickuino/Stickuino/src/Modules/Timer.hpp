

#ifndef TIMER_HPP
#define TIMER_HPP

class Promise {
   public:
    Promise();
    void andThen(void (*callback)()) { callback(); }
};

#endif /* TIMER_HPP */