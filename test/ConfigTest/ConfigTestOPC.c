#include<stdio.h>
#include "configuration.h"
#include "config_opc.h"

#define USAGE "command [xmlfile]"

int main(int argc, char * argv[]) {

    if(argc != 2) {
        printf(USAGE);
        return -1;
    }
    IG_Config * conf = IG_Config_create(argv[1], IG_CONFIG_OPC);

    if(conf == NULL) {
        printf("wrong format of xml\n");
        return -1;
    }
    IG_ConfigResponse res;

    IG_Status rt = IG_Config_OPC_get_conn_string(conf,&res);
    if(rt != IG_STATUS_GOOD) {
        printf("could not get conn_string\n");
        return -1;
    } else {
        printf("CONNSTRING: '%s'\n",(unsigned char*) res.data);
    }

    rt = IG_Config_OPC_get_subscriptions(conf,&res);
    if(rt != IG_STATUS_GOOD) {
        return -1;
    }
    printf("could get subs\n");
    IG_OPC_Subscription * subs = (IG_OPC_Subscription *) res.data;
    printf("ResponseAmount=%i\n", res.responseAmount);
    for(unsigned int i = 0; i < res.responseAmount; i++) {
        printf("SUBNR:%i subid=%i, intervalms=%ims\n",i,subs[i].subscription_id, subs[i].timeintervalms);
        IG_ConfigResponse it;
        IG_Status status = IG_Config_OPC_get_items(conf,&it,subs[i].subscription_id);
        if(status != IG_STATUS_GOOD) {
            return -1;
            continue;
        }
        IG_OPC_Item * items = (IG_OPC_Item *) it.data;
        for(unsigned int j = 0; j < it.responseAmount; j++) {
            printf("\tsubid=%i, nodeid=%i, igid=%i\n",items[j].to_sub_id, items[j].nodeid, items[j].internal_id);
        }
    }

    
}