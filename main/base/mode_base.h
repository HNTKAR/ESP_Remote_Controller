#ifndef __MODE_MAIN_H__
#define __MODE_MAIN_H__

class modeMain
{
public:
    ~modeMain() = default;
    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};
#endif // __MODE_MAIN_H__