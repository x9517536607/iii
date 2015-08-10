#include "servicesingleton.h"

serviceSingleton *serviceSingleton::m_serviceSingleton = 0;

serviceSingleton::serviceSingleton()
{
    scheduler = BasicTaskScheduler::createNew();
    env = BasicUsageEnvironment::createNew(*scheduler);
    rtspServer = RTSPServer::createNew(*env, 554, NULL);
    serverThread = new envThread(this, env);
    serverThread->start();
}

serviceSingleton::~serviceSingleton()
{
    serverThread->stop();
}

serviceSingleton *serviceSingleton::getInstance()
{
    if(!m_serviceSingleton)
        m_serviceSingleton = new serviceSingleton();
    return m_serviceSingleton;
}

ServerMediaSession * serviceSingleton::createMediaSession(char const* serverURL, char const* name)
{
    return ProxyServerMediaSession::createNew(*env, rtspServer, serverURL , name, NULL, NULL, 0, 0);
}

void serviceSingleton::addMediaSesstion(ServerMediaSession *sms)
{
    rtspServer->addServerMediaSession(sms);
    char* proxyStreamURL = rtspServer->rtspURL(sms);
    *env << "\tPlay this stream using the URL: " << proxyStreamURL << "\n";
    delete[] proxyStreamURL;
}

void serviceSingleton::removeMediaSession(ServerMediaSession *sms)
{
    char* proxyStreamURL = rtspServer->rtspURL(sms);
    *env << "\tRemove this stream using the URL: " << proxyStreamURL << "\n";
    delete[] proxyStreamURL;
    rtspServer->removeServerMediaSession(sms);
}
