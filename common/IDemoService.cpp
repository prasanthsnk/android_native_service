#define LOG_NDEBUG 0
#define LOG_TAG "DemoSERVICE"  
  
#include <utils/Log.h>  

#include "IDemoService.h"
#include "IDemoServiceCallback.h"
using namespace android;

class BpDemoService : public BpInterface<IDemoService>
{
public:
    BpDemoService(const sp<IBinder>& impl) : BpInterface<IDemoService>(impl){};
    int OnLoad()
    {
        ALOGD("BpDemoService OnLoad ");
        Parcel data, reply;  
        data.writeInterfaceToken(IDemoService::getInterfaceDescriptor());
        remote()->transact(ONLOAD, data, &reply);
        return reply.readInt32();
    }
    void registerCallback(const sp<IDemoServiceCallback>& cb)
    {
        Parcel data, reply;
        data.writeInterfaceToken(IDemoService::getInterfaceDescriptor());
        data.writeStrongBinder(IInterface::asBinder(cb));
        remote()->transact(REGISTER_CALLBACK, data, &reply);
    }
    void unregisterCallback()
    {
        Parcel data, reply;
        remote()->transact(REGISTER_CALLBACK, data, &reply);
    }
};

IMPLEMENT_META_INTERFACE(DemoService, SERVICE_NAME);


status_t BnDemoService::onTransact(uint32_t code,const Parcel & data,Parcel * reply, uint32_t flags)
{
    switch(code)
    {
        case ONLOAD:
        {
            CHECK_INTERFACE(IDemoService, data, reply);
            int ret = OnLoad();
            ALOGD("BpDemoService OnLoad Switch %d", ret);
            reply->writeInt32(ret);
            return NO_ERROR;
        }
         case REGISTER_CALLBACK: {
            CHECK_INTERFACE(IDemoService, data, reply);
            sp<IDemoServiceCallback> cb = interface_cast<IDemoServiceCallback>(data.readStrongBinder());
            registerCallback(cb);
            return NO_ERROR;
        }
        case UNREGISTER_CALLBACK: {
            CHECK_INTERFACE(IDemoService, data, reply);
            unregisterCallback();
            return NO_ERROR;
        }
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

