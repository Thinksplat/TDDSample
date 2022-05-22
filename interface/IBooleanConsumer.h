#ifndef _IBOOLEAN_CONSUMER_H
#define _IBOOLEAN_CONSUMER_H

class IBooleanConsumer {
    public:
    inline void On() {
        Consume(true);
    }
    inline void Off() {
        Consume(false);
    }
    virtual void Consume(bool)=0;
};

#endif