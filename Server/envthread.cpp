#include "envthread.h"

envThread::envThread(QObject *pParent, UsageEnvironment *env) : QThread(pParent)
{
    this->env = env;
    IsOnline = false;
}

void envThread::run()
{
    env->taskScheduler().doEventLoop();
}

void envThread::start(Priority p)
{
    IsOnline = true;
    QThread::start(p);
}

void envThread::stop()
{
    IsOnline = false;
    env->taskScheduler().doEventLoop(0);
}
