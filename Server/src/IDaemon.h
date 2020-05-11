#ifndef SERVER_IDAEMON_H
#define SERVER_IDAEMON_H


class IDaemon
{
protected:
    static constexpr int CHILD_MUST_RESTART = 1;
    static constexpr int CHILD_MUST_TERMINATE = 2;
public:
    virtual bool Start() = 0;
    virtual bool Stop() = 0;
    virtual bool Restart() = 0;
};



#endif //SERVER_IDAEMON_H
