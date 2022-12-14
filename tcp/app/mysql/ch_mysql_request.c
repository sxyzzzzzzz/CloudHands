
#include "ch_mysql_request.h"

ch_mysql_request_t *ch_mysql_request_parse(ch_pool_t *mp,void *data,size_t dlen){

    ch_mysql_request_t *mreq = (ch_mysql_request_t*)ch_pcalloc(mp,sizeof(*mreq));

    if(dlen>0&&data!=NULL){
    
        mreq->opcode = *(uint8_t*)data;
    
        mreq->dlen = dlen-1;
    
        mreq->data = ch_pcalloc(mp,mreq->dlen);
    
        memcpy(mreq->data,data+1,mreq->dlen);
    }else{

        mreq->dlen = 4;
        mreq->data = ch_pcalloc(mp,mreq->dlen); 
        memcpy(mreq->data,(void*)"NULL",mreq->dlen);
        
    }

    return mreq;
}

