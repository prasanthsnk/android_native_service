#ifndef __I_Demo_SERVICE_NOTIFICATION_H__
#define __I_Demo_SERVICE_NOTIFICATION_H__

#include <utils/Log.h>

#include <assert.h>
#include <binder/IPCThreadState.h>
#include <iomanip>
#include <iostream>

using namespace android;
class NotificationClient : public IBinder::DeathRecipient {
    public:
        NotificationClient(pid_t pid);
        virtual ~NotificationClient();
        // IBinder::DeathRecipient
        virtual void binderDied(const android::wp<IBinder>& who);

    protected:
        const pid_t mProcessId;
        
};

#endif //__I_Demo_SERVICE_NOTIFICATION_H__