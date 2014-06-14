// Copyright 2010-2012 RethinkDB, all rights reserved.
#ifndef CLUSTERING_IMMEDIATE_CONSISTENCY_BRANCH_METADATA_HPP_
#define CLUSTERING_IMMEDIATE_CONSISTENCY_BRANCH_METADATA_HPP_

#include <map>
#include <utility>

#include "clustering/generic/registration_metadata.hpp"
#include "clustering/immediate_consistency/branch/history.hpp"
#include "concurrency/fifo_checker.hpp"
#include "concurrency/fifo_enforcer.hpp"
#include "concurrency/promise.hpp"
#include "containers/uuid.hpp"
#include "protocol_api.hpp"
#include "rpc/mailbox/addr.hpp"
#include "rpc/semilattice/joins/macros.hpp"
#include "timestamps.hpp"

class listener_intro_t;

/* Every `listener_t` constructs a `listener_business_card_t` and sends it to
the `broadcaster_t`. */

class listener_business_card_t {

public:
    /* These are the types of mailboxes that the master uses to communicate with
    the mirrors. */

    typedef mailbox_addr_t<void(write_t,
                                transition_timestamp_t,
                                order_token_t,
                                fifo_enforcer_write_token_t,
                                mailbox_addr_t<void()> ack_addr)> write_addr_t;
    typedef write_addr_t::mailbox_type write_mailbox_t;

    typedef mailbox_addr_t<void(write_t,
                                transition_timestamp_t,
                                order_token_t,
                                fifo_enforcer_write_token_t,
                                mailbox_addr_t<void(write_response_t)>,
                                write_durability_t)> writeread_addr_t;
    typedef writeread_addr_t::mailbox_type writeread_mailbox_t;

    typedef mailbox_addr_t<void(read_t,
                                state_timestamp_t,
                                order_token_t,
                                fifo_enforcer_read_token_t,
                                mailbox_addr_t<void(read_response_t)>)> read_addr_t;
    typedef read_addr_t::mailbox_type read_mailbox_t;

    /* The master sends a single message to `intro_mailbox` at the
    very beginning. This tells the mirror what timestamp it's at, the
    master's cpu sharding subspace count, and also tells it where to
    send upgrade/downgrade messages. */

    typedef mailbox_addr_t<void(writeread_addr_t, read_addr_t)> upgrade_addr_t;
    typedef upgrade_addr_t::mailbox_type upgrade_mailbox_t;

    typedef mailbox_addr_t<void(mailbox_addr_t<void()>)> downgrade_addr_t;
    typedef downgrade_addr_t::mailbox_type downgrade_mailbox_t;

    typedef mailbox_addr_t<void(listener_intro_t)> intro_addr_t;
    typedef intro_addr_t::mailbox_type intro_mailbox_t;

    listener_business_card_t() { }
    listener_business_card_t(const intro_addr_t &im,
                             const write_addr_t &wm)
        : intro_mailbox(im), write_mailbox(wm) { }

    intro_addr_t intro_mailbox;
    write_addr_t write_mailbox;

    RDB_MAKE_ME_SERIALIZABLE_2(intro_mailbox, write_mailbox);
};


class listener_intro_t {
public:
    state_timestamp_t broadcaster_begin_timestamp;
    listener_business_card_t::upgrade_addr_t upgrade_mailbox;
    listener_business_card_t::downgrade_addr_t downgrade_mailbox;
    uuid_u listener_id;

    listener_intro_t() { }
    listener_intro_t(state_timestamp_t _broadcaster_begin_timestamp,
                     listener_business_card_t::upgrade_addr_t _upgrade_mailbox,
                     listener_business_card_t::downgrade_addr_t _downgrade_mailbox,
                     uuid_u _listener_id)
        : broadcaster_begin_timestamp(_broadcaster_begin_timestamp),
          upgrade_mailbox(_upgrade_mailbox), downgrade_mailbox(_downgrade_mailbox),
          listener_id(_listener_id) { }

    RDB_MAKE_ME_SERIALIZABLE_4(broadcaster_begin_timestamp,
                               upgrade_mailbox, downgrade_mailbox, listener_id);
};


/* `backfiller_business_card_t` represents a thing that is willing to serve
backfills over the network. It appears in the directory. */

struct backfiller_business_card_t {

    typedef mailbox_addr_t< void(
        backfill_session_id_t,
        region_map_t<version_range_t>,
        branch_history_t,
        mailbox_addr_t< void(
            region_map_t<version_range_t>,
            branch_history_t
            ) >,
        mailbox_addr_t<void(backfill_chunk_t, fifo_enforcer_write_token_t)>,
        mailbox_addr_t<void(fifo_enforcer_write_token_t)>,
        mailbox_addr_t<void(mailbox_addr_t<void(int)>)>
        )> backfill_addr_t;
    typedef backfill_addr_t::mailbox_type backfill_mailbox_t;

    typedef mailbox_addr_t<void(backfill_session_id_t)> cancel_backfill_addr_t;
    typedef cancel_backfill_addr_t::mailbox_type cancel_backfill_mailbox_t;


    /* Mailboxes used for requesting the progress of a backfill */
    typedef mailbox_addr_t<void(backfill_session_id_t,
                                mailbox_addr_t<void(std::pair<int, int>)>)> request_progress_addr_t;
    typedef request_progress_addr_t::mailbox_type request_progress_mailbox_t;

    backfiller_business_card_t() { }
    backfiller_business_card_t(
            const backfill_addr_t &ba,
            const cancel_backfill_addr_t &cba,
            const request_progress_addr_t &pa) :
        backfill_mailbox(ba), cancel_backfill_mailbox(cba), request_progress_mailbox(pa)
        { }

    backfill_addr_t backfill_mailbox;
    cancel_backfill_addr_t cancel_backfill_mailbox;
    request_progress_addr_t request_progress_mailbox;

    RDB_MAKE_ME_SERIALIZABLE_3(backfill_mailbox, cancel_backfill_mailbox,
                               request_progress_mailbox);
};

RDB_MAKE_EQUALITY_COMPARABLE_3(backfiller_business_card_t, backfill_mailbox,
    cancel_backfill_mailbox, request_progress_mailbox);

/* `broadcaster_business_card_t` is the way that listeners find the broadcaster.
It appears in the directory. */

struct broadcaster_business_card_t {

    broadcaster_business_card_t(branch_id_t bid,
            const branch_history_t &bh,
            const registrar_business_card_t<listener_business_card_t> &r) :
        branch_id(bid), branch_id_associated_branch_history(bh), registrar(r) { }

    broadcaster_business_card_t() { }

    branch_id_t branch_id;
    branch_history_t branch_id_associated_branch_history;

    registrar_business_card_t<listener_business_card_t> registrar;

    RDB_MAKE_ME_SERIALIZABLE_3(branch_id, branch_id_associated_branch_history, registrar);
};

RDB_MAKE_EQUALITY_COMPARABLE_3(broadcaster_business_card_t, branch_id,
    branch_id_associated_branch_history, registrar);

struct replier_business_card_t {
    /* This mailbox is used to check that the replier is at least as up to date
     * as the timestamp. The second argument is used as an ack mailbox, once
     * synchronization is complete the replier will send a message to it. */
    typedef mailbox_addr_t<void(state_timestamp_t, mailbox_addr_t<void()>)> synchronize_addr_t;
    typedef synchronize_addr_t::mailbox_type synchronize_mailbox_t;
    synchronize_addr_t synchronize_mailbox;

    backfiller_business_card_t backfiller_bcard;

    replier_business_card_t()
    { }

    replier_business_card_t(const synchronize_addr_t &_synchronize_mailbox,
                            const backfiller_business_card_t &_backfiller_bcard)
        : synchronize_mailbox(_synchronize_mailbox), backfiller_bcard(_backfiller_bcard)
    { }

    RDB_MAKE_ME_SERIALIZABLE_2(synchronize_mailbox, backfiller_bcard);
};

RDB_MAKE_EQUALITY_COMPARABLE_2(replier_business_card_t,
    synchronize_mailbox, backfiller_bcard);

#endif /* CLUSTERING_IMMEDIATE_CONSISTENCY_BRANCH_METADATA_HPP_ */
