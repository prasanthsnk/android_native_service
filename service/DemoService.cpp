#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>  
#include "../common/IDemoService.h"
#include "../common/IDemoServiceCallback.h"  
#include "../common/NotificationClient.h"
#define LOG_NDEBUG 0
#define LOG_TAG "DemoSERVICE"  
  
#include <utils/Log.h>

#include <thread>
#include <iostream>
 
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <fstream>

using namespace android;
class DemoService : public BnDemoService
{ 
    public: 
	 sp<IBinder> binder;
	 int status = -1;

	DemoService(){
		ALOGD("DemoService Constructor");
		pthread_t t1;
		pthread_create(&t1, NULL, DemoService::thread, this);
		//void* result;
		//pthread_join(t1,&result);
	};
	 static void *thread(void *context)
    {
        return ((DemoService *)context)->PrintStatus();
    }
	void *PrintStatus(void) {
		ALOGD("DemoService PrintStatus");
		std::string connected = "connected";
		while(true)
        {
			ALOGD("is_Demo_exists");
			// std::string result1, result2;
			// result1 = readFile("/sys/class/drm/card0-eDP-1/status");
			// result2 = readFile("/sys/class/drm/card0-eDP-2/status");
			// ALOGD("result1%sresult2%s", result1.c_str(), result2.c_str());
			
			if(binder!=NULL){
				ALOGD("BINDER NOT NULL");
							android::sp<IDemoServiceCallback> client = interface_cast<IDemoServiceCallback>(binder);
							if (client.get() != nullptr) {
								ALOGD("CLIENT NOT NULL FIRING CHANGES");
								client->onCallBack();
							}
						}

				// if (connected.compare(result1) == 0 || connected.compare(result2) == 0){
				// 	//connected
				// 	if(status !=1){
				// 		status = 1;
				// 		ALOGD("Demo Connected");
				// 		//fire connected listner
				// 		system("am broadcast -a android.prasanth.intent.action.Demo_STATE_CHANGED --ez state 1 --user 0");
				// 		if(binder!=NULL){
				// 			android::sp<IDemoServiceCallback> client = interface_cast<IDemoServiceCallback>(binder);
				// 			if (client.get() != nullptr) {
				// 				client->onDemoInputConnected();
				// 			}
				// 		}
				// 	}
				// }else{
				// 	//not connected
				// 	if(status !=0){
				// 		status = 0;
				// 		ALOGD("Demo Not Connected");
				// 		//fire not connected listner
				// 		system("am broadcast -a android.prasanth.intent.action.Demo_STATE_CHANGED --ez state 0 --user 0");
				// 		if(binder!=NULL){
				// 			android::sp<IDemoServiceCallback> client = interface_cast<IDemoServiceCallback>(binder);
				// 			if (client.get() != nullptr) {
				// 				client->onDemoInputDisconnected();
				// 			}
				// 		}
				// 	}
				// }
			sleep(1);
		}
	}

	 std::string readFile(std::string path){
		ALOGD("is_Demo_exists");
		std::string line, result;
		std::ifstream myfile (path);
		if (myfile.is_open())
		{
			while ( myfile.good() )
			{
			getline(myfile,line);
			result = result+line;
			ALOGD("LINE %s", line.c_str());
			}
			ALOGD("result%sresult", result.c_str());
			myfile.close();
		}
		return result;
	}

	int OnLoad(){
		return status;//is_Demo_exists();
	}

	// std::map<pid_t, android::sp<NotificationClient>> mNotificationClients;
	void registerCallback(const sp<IDemoServiceCallback>& cb)
	{
		pid_t pid = IPCThreadState::self()->getCallingPid();
		// if (mNotificationClients.count(pid) == 0) {
			sp<NotificationClient> notificationClient = new NotificationClient(pid);
			// mNotificationClients[pid] = notificationClient;

			binder = IInterface::asBinder(cb);
			status_t status = binder->linkToDeath(notificationClient);
			ALOGW_IF(status != NO_ERROR, "registerCallback linkToDeath = %d\n", status);
    	// } 
	}
	void unregisterCallback()
	{
		binder = NULL;
	}
}; 

int main(int argc, char** argv)
{
    ALOGD("DemoService Main Method");
	defaultServiceManager()->addService(String16(SERVICE_NAME), new DemoService());
	ALOGD("DemoService Join");
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;  
} 
