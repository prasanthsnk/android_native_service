#define LOG_NDEBUG 0
#define LOG_TAG "DemoSERVICECallback"  
  
#include <utils/Log.h>  
#include "IDemoServiceCallback.h"

using namespace android;

class BpDemoServiceCallback : public BpInterface<IDemoServiceCallback>
{
public:
    BpDemoServiceCallback(const sp<IBinder>& impl) : BpInterface<IDemoServiceCallback>(impl){};
    void onDemoInputConnected()
    {
        ALOGD("BpDemoServiceCallback onDemoInputConnected ");
        Parcel data, reply;  
        data.writeInterfaceToken(IDemoServiceCallback::getInterfaceDescriptor());   
        remote()->transact(ON_Demo_CONNECTED, data, &reply);
    }
    void onDemoInputDisconnected()
    {
        ALOGD("BpDemoServiceCallback onDemoInputDisconnected ");
        Parcel data, reply;  
        data.writeInterfaceToken(IDemoServiceCallback::getInterfaceDescriptor());  
        remote()->transact(ON_Demo_DISCONNECTED, data, &reply);
    }
};

IMPLEMENT_META_INTERFACE(DemoServiceCallback, "com.prasanth.Demoservice.IDemoServiceCallback");

status_t BnDemoServiceCallback::onTransact(uint32_t code,const Parcel & data,Parcel * reply, uint32_t flags)
{
    switch(code)
    {
        case ON_Demo_CONNECTED:
        {
            CHECK_INTERFACE(IDemoServiceCallback, data, reply);
            onDemoInputConnected();
            ALOGD("BpDemoServiceCallback onDemoInputConnected Switch");
            return NO_ERROR;
        }
        case ON_Demo_DISCONNECTED:
        {
            CHECK_INTERFACE(IDemoServiceCallback, data, reply);
            onDemoInputDisconnected();
            ALOGD("BpDemoServiceCallback onDemoInputDisconnected Switch");
            return NO_ERROR;
        }
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}
