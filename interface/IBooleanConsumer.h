#ifndef _IBOOLEAN_CONSUMER_H
#define _IBOOLEAN_CONSUMER_H

#include <functional>

class IBooleanConsumer {
    public:
    inline void On() {
        Consume(true);
    }
    inline void Off() {
        Consume(false);
    }
    std::function<void()> OnFunction() {
        return std::function<void()>(std::bind(&IBooleanConsumer::On, this));
    }
    std::function<void()> OffFunction() {
        return std::function<void()>(std::bind(&IBooleanConsumer::Off, this));
    }
    virtual void Consume(bool)=0;
};

#endif