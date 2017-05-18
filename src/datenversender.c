#include "datenversender.h"


IG_Datenversender * IG_Datenversender_create(IG_Config * config) {
    IG_Datenversender * sender = (IG_Datenversender *) malloc(sizeof(IG_Datenversender));
    sender->config = config;
    sender->queue = IG_Queue_new();
    return sender;
}

void IG_Datenversender_delete(IG_Datenversender * sender) {
    IG_Queue_delete(sender->queue);
    free(sender);
}

bool checkForNewData(IG_Datenversender * sender){
    // if Queue isn't empty there is new Data !
    return IG_Queue_isEmpty(sender->queue);
}

IG_Status sendData(IG_Datenversender * sender, IG_Data * data) {
// right data in to Queue

    IG_Queue_put(&(sender->queue),data);
 // TODO: ?
}

void* doSomeThing(void *arg)
{
            // Loop, when thread creation is succeeded
    while ( 1 )
     {

  struct readThreadParams *params = arg;
  IG_Mqtt *stack = params->stack;
  IG_Datenversender * sender = params->sender;  
  IG_Data * data = params->data;

    if (checkForNewData(&sender)){
    return  IG_STATUS_BAD;
    }
    else {   
    char *payload = getMsgPayload(IG_Queue_take(&(sender->queue)));
    // publish the message
    pubmsg(stack, &payload, sender);
    return IG_STATUS_GOOD;
    }
                    // Do Something
                delay(100);     // 100 ms

}
   
}

IG_Status init_versender(IG_Datenversender * sender) {
/* All this value in config struct "sender" || ADDRESS "tcp://localhost:1883" || CLIENTID "ExampleClientPub" || TOPIC "MQTT Examples"  ||QOS 1 TIMEOUT 10000L*/
int rc;
int err;
pthread_t tid[1];

struct readThreadParams {
     IG_Datenversender * sender;  
     IG_Data * data;
     IG_Mqtt *servant;
};
struct readThreadParams *readParams;
readParams = malloc(sizeof(readThreadParams));
readParams->sender = sender;                                                     
readParams->data = data;                                                
readParams->stack = IG_Mqtt_create();


// Create the Client
MQTTClient_create(&client, getAddress(sender->config), getClientID(sender->config), MQTTCLIENT_PERSISTENCE_NONE, NULL);
conn_opts.keepAliveInterval = 20;
conn_opts.cleansession = 1;

// check for Conn_ACK
 if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        return IG_STATUS_BAD;
    }

 // CallBackMethod Sending out
    err = pthread_create(&(tid[i]), NULL, &doSomeThing, readParams);
        if (err != 0) {
            printf("\ncan't create thread");
            disconnect(&(readParams->stack.client));
            return IG_STATUS_BAD;
        }
        else {
            printf("\n Thread created successfully\n");
       }
}


