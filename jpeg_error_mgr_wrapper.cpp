
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "jpeg_error_mgr_wrapper.h"

#include "allocator.h"

struct jpeg_error_mgr *jpeg_std_error_wrapped(uint64_t id) {
    packed_ret_t ret = allocate_client(id, sizeof(struct jpeg_error_mgr));
    struct jpeg_error_mgr *client_err = (struct jpeg_error_mgr *)ret.client;

    struct jpeg_error_mgr *temp = (struct jpeg_error_mgr *)ret.lib;

    enable_lib(id);
    struct jpeg_error_mgr *err = jpeg_std_error(temp);
    disable_lib(id);
    assert(err == temp); // Check it returned the correct pointer

    // Perform checks
    assert(client_err->trace_level == 0);
    assert(client_err->num_warnings == 0);
    assert(client_err->msg_code == 0);
    assert(client_err->last_jpeg_message == (int)JMSG_LASTMSGCODE - 1);
    assert(client_err->addon_message_table == NULL);
    assert(client_err->first_addon_message == 0);
    assert(client_err->last_addon_message == 0);

    assert(client_err->error_exit != NULL);
    assert(client_err->emit_message != NULL);
    assert(client_err->output_message != NULL);
    assert(client_err->format_message != NULL);
    assert(client_err->reset_error_mgr != NULL);

    return err;
}
