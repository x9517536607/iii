#ifndef ENVTHREAD_H
#define ENVTHREAD_H

#include <QThread>
#include "BasicUsageEnvironment.hh"

class envThread : public QThread
{
    Q_OBJECT

    public:
        envThread(QObject *pParent, UsageEnvironment *env);

    protected:
        void run();

    private:
        UsageEnvironment *env;
        bool IsOnline;

    public slots:
        void start(Priority p = InheritPriority);
        void stop();
};

#endif // ENVTHREAD_H
