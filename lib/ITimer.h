#ifndef DA6A6755_21A6_4743_8988_1F46A84425CA
#define DA6A6755_21A6_4743_8988_1F46A84425CA

class ITimer
{
public:
    virtual bool HasExpired() = 0;
    virtual void Reset() = 0;
};

#endif /* DA6A6755_21A6_4743_8988_1F46A84425CA */
