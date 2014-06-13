// Copyright 2010-2014 RethinkDB, all rights reserved.
#ifndef CLUSTERING_GENERIC_REGISTRATION_METADATA_HPP_
#define CLUSTERING_GENERIC_REGISTRATION_METADATA_HPP_

#include "containers/uuid.hpp"
#include "rpc/mailbox/addr.hpp"
#include "rpc/semilattice/joins/macros.hpp"

template<class business_card_t>
class registrar_business_card_t {

public:
    typedef uuid_u registration_id_t;


    typedef mailbox_addr_t<void(registration_id_t, peer_id_t, business_card_t)>
        create_mailbox_addr_t;
    typedef typename create_mailbox_addr_t::mailbox_type create_mailbox_t;
    create_mailbox_addr_t create_mailbox;

    typedef mailbox_addr_t<void(registration_id_t)> delete_mailbox_addr_t;
    typedef typename delete_mailbox_addr_t::mailbox_type delete_mailbox_t;
    delete_mailbox_addr_t delete_mailbox;

    registrar_business_card_t() { }

    registrar_business_card_t(const create_mailbox_addr_t &cm,
                              const delete_mailbox_addr_t &dm)
        : create_mailbox(cm), delete_mailbox(dm) { }

    RDB_MAKE_ME_SERIALIZABLE_2(create_mailbox, delete_mailbox);
};

template <class business_card_t>
RDB_MAKE_EQUALITY_COMPARABLE_2(registrar_business_card_t<business_card_t>,
    create_mailbox, delete_mailbox);

#endif /* CLUSTERING_GENERIC_REGISTRATION_METADATA_HPP_ */
