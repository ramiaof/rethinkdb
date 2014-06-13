#!/usr/bin/env python
# Copyright 2010-2014 RethinkDB, all rights reserved.
import generate_rpc_templates
import sys

"""This script is used to generate the mailbox template (singular) in
`rethinkdb/src/rpc/mailbox/addr.hpp`. It is meant to be run as follows
(assuming that the current directory is `rethinkdb/src/`):

$ ../scripts/generate_rpc_templates.py > rpc/mailbox/addr.hpp

"""

if __name__ == "__main__":
    print "// Copyright 2010-2014 RethinkDB, all rights reserved."
    print "#ifndef RPC_MAILBOX_ADDR_HPP_"
    print "#define RPC_MAILBOX_ADDR_HPP_"
    print

    print "/* This file is automatically generated by '%s'." % " ".join(sys.argv)
    print "Please modify '%s' instead of modifying this file.*/" % sys.argv[0]
    print

    print "#include \"rpc/serialize_macros.hpp\""
    print "#include \"rpc/mailbox/mailbox.hpp\""
    print

    generate_rpc_templates.generate_mailbox_addr_template()

    print "#endif // RPC_MAILBOX_ADDR_HPP_"
