#ifndef C966AB86_7E5D_483D_BB6D_F9686FE07A05
#define C966AB86_7E5D_483D_BB6D_F9686FE07A05

#include "interface/IBooleanConsumer.h"
#include "interface/IBooleanProvider.h"
#include "lib-behaviour/Blink.h"
#include <memory>

class BlinkBuilder {
    public:
    BlinkBuilder() {
        
    }
    BlinkBuilder(IBooleanConsumer &on_off) {
        OnOff(on_off);
    }

    BlinkBuilder OnOff(IBooleanConsumer &on_off) {
        NoOwn(this->on_off,on_off);
        return *this;
    }

    void Run() {
        if(!on_off.get() || !on_wait.get() || !off_wait.get() || !done.get()) {
            throw std::runtime_error("BlinkBuilder: Run: not all parameters set");
        }   
        Behaviour::Blink(*on_off, *on_wait, *off_wait, *done);
    }

    BlinkBuilder Until(IBooleanProvider &until) {
        // Reset the done and don't own it
        NoOwn(done,until);
        return *this;
    }

    BlinkBuilder Wait(IWork &wait) {
        // Reset the on_wait and off_wait
        NoOwn(this->on_wait,wait);
        NoOwn(this->off_wait,wait);
        return *this;
    }

    BlinkBuilder OnWait(IWork &on_wait) {
        // Reset the on_wait and don't own it
        NoOwn(this->on_wait,on_wait);
        return *this;
    }

    BlinkBuilder OffWait(IWork &off_wait) {
        // Reset the off_wait and don't own it
        NoOwn(this->off_wait,off_wait);
        return *this;
    }
    
    private:
    template <typename T>
    void NoOwn(std::shared_ptr<T> &ptr, T &value) {
        ptr.reset(&value, [](T *) {  });
    }

    std::shared_ptr<IBooleanConsumer> on_off;
    std::shared_ptr<IWork> on_wait;
    std::shared_ptr<IWork> off_wait;
    std::shared_ptr<IBooleanProvider> done;
};

#endif /* C966AB86_7E5D_483D_BB6D_F9686FE07A05 */
