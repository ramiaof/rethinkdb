// Copyright 2010-2014 RethinkDB, all rights reserved.
#ifndef RPC_MAILBOX_ADDR_HPP_
#define RPC_MAILBOX_ADDR_HPP_

/* This file is automatically generated by '../scripts/generate_mailbox_addr.py'.
Please modify '../scripts/generate_mailbox_addr.py' instead of modifying this file.*/

#include "rpc/serialize_macros.hpp"
#include "rpc/mailbox/mailbox.hpp"

template <class> class mailbox_t;

template <class T>
class mailbox_addr_t {
public:
    bool operator<(const mailbox_addr_t<T> &other) const {
        return addr < other.addr;
    }
    bool is_nil() const { return addr.is_nil(); }
    peer_id_t get_peer() const { return addr.get_peer(); }

    friend class mailbox_t<T>;

    RDB_MAKE_ME_SERIALIZABLE_1(addr);
    RDB_MAKE_ME_EQUALITY_COMPARABLE_1(mailbox_addr_t<T>, addr);

private:
    friend void send(mailbox_manager_t *, mailbox_addr_t<void()>);
    template <class a0_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t) >::address_t, const a0_t &);
    template <class a0_t, class a1_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t) >::address_t, const a0_t &, const a1_t &);
    template <class a0_t, class a1_t, class a2_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t) >::address_t, const a0_t &, const a1_t &, const a2_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t, class a6_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &, const a6_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t, class a6_t, class a7_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &, const a6_t &, const a7_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t, class a6_t, class a7_t, class a8_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &, const a6_t &, const a7_t &, const a8_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t, class a6_t, class a7_t, class a8_t, class a9_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t, a9_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &, const a6_t &, const a7_t &, const a8_t &, const a9_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t, class a6_t, class a7_t, class a8_t, class a9_t, class a10_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t, a9_t, a10_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &, const a6_t &, const a7_t &, const a8_t &, const a9_t &, const a10_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t, class a6_t, class a7_t, class a8_t, class a9_t, class a10_t, class a11_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t, a9_t, a10_t, a11_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &, const a6_t &, const a7_t &, const a8_t &, const a9_t &, const a10_t &, const a11_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t, class a6_t, class a7_t, class a8_t, class a9_t, class a10_t, class a11_t, class a12_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t, a9_t, a10_t, a11_t, a12_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &, const a6_t &, const a7_t &, const a8_t &, const a9_t &, const a10_t &, const a11_t &, const a12_t &);
    template <class a0_t, class a1_t, class a2_t, class a3_t, class a4_t, class a5_t, class a6_t, class a7_t, class a8_t, class a9_t, class a10_t, class a11_t, class a12_t, class a13_t>
    friend void send(mailbox_manager_t *,
                     typename mailbox_t< void(a0_t, a1_t, a2_t, a3_t, a4_t, a5_t, a6_t, a7_t, a8_t, a9_t, a10_t, a11_t, a12_t, a13_t) >::address_t, const a0_t &, const a1_t &, const a2_t &, const a3_t &, const a4_t &, const a5_t &, const a6_t &, const a7_t &, const a8_t &, const a9_t &, const a10_t &, const a11_t &, const a12_t &, const a13_t &);

    raw_mailbox_t::address_t addr;
};
#endif // RPC_MAILBOX_ADDR_HPP_
