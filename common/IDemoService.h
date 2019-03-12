#ifndef __I_Demo_SERVICE_H__
#define __I_Demo_SERVICE_H__


#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

#include "IDemoServiceCallback.h"

using namespace android;

#define SERVICE_NAME "com.prasanth.Demoservice.IDemoService"

enum {
    ONLOAD = IBinder::FIRST_CALL_TRANSACTION,
    REGISTER_CALLBACK,
    UNREGISTER_CALLBACK
};

class IDemoService : public IInterface
{
public:
    DECLARE_META_INTERFACE(DemoService);

    virtual int OnLoad() = 0;
    virtual void registerCallback(const sp<IDemoServiceCallback>& cb) = 0;
    virtual void unregisterCallback() = 0;
};

class BnDemoService : public BnInterface<IDemoService>
{
public:
    virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0); 
};

#endif /* __I_Demo_SERVICE_H__ */
