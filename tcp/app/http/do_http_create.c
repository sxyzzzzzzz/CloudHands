/*
 *
 *      Filename: do_http_other.c
 *
 *        Author: shajf,csp001314@gmail.com
 *   Description: ---
 *        Create: 2018-05-17 17:41:03
 * Last Modified: 2018-09-10 14:35:13
 */


static void * do_http_session_entry_create(ch_mpool_agent_t *mpa,ch_tcp_app_t *app ch_unused,ch_proto_session_store_t *pstore){

	ch_pool_t *mp;

	ch_http_session_entry_t *hsentry = NULL;
    
    if(mpa){

        mp = ch_mpool_agent_alloc(mpa);
    }else{
        mp = ch_pool_create(1024);
    }

	if(mp == NULL){
	
		ch_log(CH_LOG_ERR,"Cannot create memory pool for http session entry!");
		return NULL;
	}

	hsentry = (ch_http_session_entry_t*)ch_pcalloc(mp,sizeof(*hsentry));
	ch_http_sentry_init(hsentry,&pstore->g_buffer,mp);


	return (void*)hsentry;
}

#define CAN_STORE(session) ((session)->parse_phase>=PARSE_PHASE_REQ_HEADER)

static void do_http_session_entry_clean(ch_mpool_agent_t *mpa,ch_tcp_app_t *app,ch_proto_session_store_t *pstore,ch_tcp_session_t *tsession){

    app = app;
	ch_http_session_t *session = NULL;
	ch_http_session_entry_t *hsentry = (ch_http_session_entry_t*)tsession->sentry;

	list_for_each_entry(session,&hsentry->reqs,node){
	
		int is_accept = 1;

		if(session->is_pass){
			is_accept = 0;
		}else if (CAN_STORE(session)) {

            ch_proto_session_store_write(pstore,tsession,(void*)session);
		}

		ch_http_session_body_destroy(session->req_body);
		ch_http_session_body_destroy(session->res_body);

		if(!is_accept){

            ch_log(CH_LOG_INFO,"after pass clean operator:");
			if(session->req_body&&session->req_body->fname){
				unlink(session->req_body->fname);
                ch_log(CH_LOG_INFO,"Delete http request body:%s",session->req_body->fname);
            }

			if(session->res_body&&session->res_body->fname){
				unlink(session->res_body->fname);
                ch_log(CH_LOG_INFO,"Delete http response body:%s",session->res_body->fname);
            }
        }
    }

    //ch_log(CH_LOG_INFO,"Destroy http session----------------------");
    if(mpa){

        ch_mpool_agent_free(mpa,hsentry->mp);
    }else{
        ch_pool_destroy(hsentry->mp);
    }

}

