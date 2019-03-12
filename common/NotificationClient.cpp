#include <utils/Log.h>

#include <assert.h>
#include <binder/IPCThreadState.h>
#include <iomanip>
#include <iostream>
#include "NotificationClient.h"

using namespace android;

NotificationClient::NotificationClient(pid_t pid)
        : mProcessId(pid) {
    ALOGD("NotificationClient(%d) created %p\n", pid, this);
}

NotificationClient::~NotificationClient() {
    ALOGD("~NotificationClient() destroyed %p\n", this);
}

void NotificationClient::binderDied(const android::wp<IBinder>& who) {
    
}