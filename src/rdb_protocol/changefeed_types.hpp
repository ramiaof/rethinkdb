#ifndef RDB_PROTOCOL_CHANGEFEED_TYPES_HPP_
#define RDB_PROTOCOL_CHANGEFEED_TYPES_HPP_

template <class> class mailbox_addr_t;

namespace ql {

namespace changefeed {

struct stamped_msg_t;

typedef mailbox_addr_t<void(stamped_msg_t)> client_addr_t;

typedef mailbox_addr_t<void(client_addr_t)> server_addr_t;


}  // namespace changefeed
}  // namespace ql


#endif  // RDB_PROTOCOL_CHANGEFEED_TYPES_HPP_
