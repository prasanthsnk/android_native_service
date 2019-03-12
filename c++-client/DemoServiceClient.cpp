#include <binder/IServiceManager.h>  
#include "../common/IDemoService.h"  


int main()
{
    sp<IBinder> binder = defaultServiceManager()->getService(String16(SERVICE_NAME));  
    if(binder == NULL)
    {  
        printf("Failed to get service: %s.\n", SERVICE_NAME);  
        return -1;  
    }  

    sp<IDemoService> service = IDemoService::asInterface(binder);  
    if(service == NULL)  
    {  
		printf("Failed to get service Interface: %s.\n", SERVICE_NAME);
        return -2;  
    }

    printf("ONLOAD()=%d\n", service->OnLoad());
}
