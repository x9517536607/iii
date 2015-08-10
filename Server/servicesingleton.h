#ifndef SERVICESINGLETON_H
#define SERVICESINGLETON_H
#include "BasicUsageEnvironment.hh"
#include "liveMedia.hh"
#include "envthread.h"

class serviceSingleton : public QObject
{
public:
    static serviceSingleton *getInstance();
    void addMediaSesstion(ServerMediaSession *sms);
    void removeMediaSession(ServerMediaSession* sms);
    ServerMediaSession *createMediaSession(char const* serverURL, char const* name);
private:
    serviceSingleton();
    ~serviceSingleton();
    static serviceSingleton *m_serviceSingleton;

    UsageEnvironment *env;
    RTSPServer *rtspServer;
    TaskScheduler *scheduler;
    envThread *serverThread;
};

#endif // SERVICESINGLETON_H
