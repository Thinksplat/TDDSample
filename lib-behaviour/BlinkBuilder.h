#ifndef C966AB86_7E5D_483D_BB6D_F9686FE07A05
#define C966AB86_7E5D_483D_BB6D_F9686FE07A05

#include "interface/IBooleanConsumer.h"
#include "interface/IBooleanProvider.h"
#include "lib-behaviour/Blink.h"
#include <memory>

class Blinker : public IWork {
    public:
    Blinker(IBooleanConsumer &on_off, IWork &on_wait, IWork &off_wait, IBooleanProvider &done) : 
        on_off(on_off), on_wait(on_wait), off_wait(off_wait), done(done) {
    }
    void Work() override {
        Behaviour::Blink(on_off, on_wait, off_wait, done);
    }
    private:
    IBooleanConsumer &on_off;
    IWork &on_wait;
    IWork &off_wait;
    IBooleanProvider &done;
};

class BlinkBuilder {
    public:
    BlinkBuilder() {
        
    }
    BlinkBuilder(IBooleanConsumer &on_off) {
        Blink(on_off);
    }

    void Run() {
        Build().Run();
    }

    BlinkBuilder &Blink(IBooleanConsumer &on_off) {
        this->on_off = &on_off;
        return *this;
    }

    Blinker Build() {
        if(!on_off || !on_wait || !off_wait || !done) {
            throw std::runtime_error("BlinkBuilder: Run: not all parameters set");
        }  
        return Blinker(*on_off, *on_wait, *off_wait, *done);
    }

    BlinkBuilder &Until(IBooleanProvider &until) {
        // Reset the done and don't own it
        this->done = &until;
        return *this;
    }

    BlinkBuilder &Wait(IWork &wait) {
        // Reset the on_wait and off_wait
        this->on_wait = &wait;
        this->off_wait = &wait;
        return *this;
    }

    BlinkBuilder &OnWait(IWork &on_wait) {
        // Reset the on_wait and don't own it
        this->on_wait = &on_wait;
        return *this;
    }

    BlinkBuilder &OffWait(IWork &off_wait) {
        // Reset the off_wait and don't own it
        this->off_wait = &off_wait;
        return *this;
    }
    
    private:


    IBooleanConsumer *on_off = nullptr;
    IWork *on_wait = nullptr;
    IWork *off_wait = nullptr;
    IBooleanProvider *done = nullptr;
};

#endif /* C966AB86_7E5D_483D_BB6D_F9686FE07A05 */
