#ifndef B9F07EA0_9184_4D3B_9CA4_68F79DA07E25
#define B9F07EA0_9184_4D3B_9CA4_68F79DA07E25

#include <Arduino.h>
#include "interface/IIntegerConsumer.h"

class ArduinoSerialConsumer: public IIntegerConsumer {
    public:
        void Consume(IIntegerConsumer::value_type value) override {
            Serial.println(value);
        }
};


#endif /* B9F07EA0_9184_4D3B_9CA4_68F79DA07E25 */
