/*
 *
 *      Filename: ch_sa_udp_session_pool.h
 *
 *        Author: shajf,csp001314@gmail.com
 *   Description: ---
 *        Create: 2018-04-13 10:42:54
 * Last Modified: 2018-04-13 10:42:54
 */

#ifndef CH_SA_UDP_SESSION_POOL_H
#define CH_SA_UDP_SESSION_POOL_H

typedef struct ch_sa_udp_session_pool_t ch_sa_udp_session_pool_t;

#include "ch_sa_work.h"
#include "ch_mpool.h"
#include "ch_ptable.h"
#include "ch_sa_udp_session.h"
#include "ch_packet_udp.h"

struct ch_sa_udp_session_pool_t {

	ch_pool_t *mp;
	
	ch_sa_work_t *sa_work;

	ch_ptable_t *udp_session_tbl;

};

extern ch_sa_udp_session_pool_t *ch_sa_udp_session_pool_create(ch_sa_work_t *sa_work,
	void (*entry_timeout_cb)(ch_ptable_entry_t *entry,uint64_t tv,void *priv_data),
	void *priv_data,const char *ptable_name);

static inline ch_sa_udp_session_t *
ch_sa_udp_session_pool_entry_create(ch_sa_udp_session_pool_t *udp_pool,ch_packet_udp_t *udp_pkt,uint64_t session_id){


	ch_sa_udp_session_t *udp_session = (ch_sa_udp_session_t*)ch_ptable_entry_create(udp_pool->udp_session_tbl,(void*)udp_pkt);
	if(udp_session)
	{

		ch_sa_udp_session_init(udp_session,udp_pkt,session_id);

	}

	return udp_session;

}

#define ch_sa_udp_session_pool_destroy(udp_pool) ch_pool_destroy(udp_pool->mp)


#define ch_sa_udp_session_pool_entry_find(udp_pool,udp_pkt) (ch_sa_udp_session_t*)ch_ptable_entry_find(udp_pool->udp_session_tbl,(void*)udp_pkt)


#define ch_sa_udp_session_pool_entry_free(udp_pool,udp_session) ch_ptable_entry_free(udp_pool->udp_session_tbl,(ch_ptable_entry_t*)udp_session)

#endif /*CH_SA_UDP_SESSION_POOL_H*/
