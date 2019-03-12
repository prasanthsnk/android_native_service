#ifndef __I_Demo_SERVICE_CALLBACK_H__
#define __I_Demo_SERVICE_CALLBACK_H__

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

using namespace android;

enum {
    ON_Demo_CONNECTED = IBinder::FIRST_CALL_TRANSACTION,
    ON_Demo_DISCONNECTED
};


class IDemoServiceCallback : public IInterface
{
public:
    DECLARE_META_INTERFACE(DemoServiceCallback);

    virtual void onDemoInputConnected() = 0;
    virtual void onDemoInputDisconnected() = 0;
};


class BnDemoServiceCallback : public BnInterface<IDemoServiceCallback>
{
public:
    virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0); 
};

#endif /* __I_Demo_SERVICE_CALLBACK_H__ */
