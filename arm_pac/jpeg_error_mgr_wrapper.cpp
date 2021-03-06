
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "jpeg_error_mgr_wrapper.h"
#include "Documentor.h"

struct jpeg_error_mgr *jpeg_std_error_wrapped(struct jpeg_decompress_struct * my_cinfo, int id) { 
    compute_Hash(id, 1);
    struct jpeg_error_mgr* jerr = (struct jpeg_error_mgr*)malloc(sizeof(jpeg_error_mgr));
    Insert_newBlock_withID(id, (uintptr_t)jerr, (size_t)sizeof(jpeg_error_mgr), 0);
    
    
    struct jpeg_error_mgr *err = jpeg_std_error(jerr);
    my_cinfo->err = err;    

    compute_Hash(id, 0);
    assert(err == jerr); // Check it returned the correct pointer

    // Perform checks
    assert(err->trace_level == 0);
    assert(err->num_warnings == 0);
    assert(err->msg_code == 0);
    assert(err->last_jpeg_message == (int)JMSG_LASTMSGCODE - 1);
    assert(err->addon_message_table == NULL);
    assert(err->first_addon_message == 0);
    assert(err->last_addon_message == 0);

    assert(err->error_exit != NULL);
    assert(err->emit_message != NULL);
    assert(err->output_message != NULL);
    assert(err->format_message != NULL);
    assert(err->reset_error_mgr != NULL);

    return err;
}
struct jpeg_error_mgr *jpeg_std_error_compress_wrapped(struct jpeg_compress_struct * my_cinfo, int id) { 
    compute_Hash(id, 1);
    struct jpeg_error_mgr* jerr = (struct jpeg_error_mgr*)malloc(sizeof(jpeg_error_mgr));
    Insert_newBlock_withID(id, (uintptr_t)jerr, (size_t)sizeof(jpeg_error_mgr), 0);
    
    
    struct jpeg_error_mgr *err = jpeg_std_error(jerr);
    my_cinfo->err = err;    

    compute_Hash(id, 0);
    assert(err == jerr); // Check it returned the correct pointer

    // Perform checks
    assert(err->trace_level == 0);
    assert(err->num_warnings == 0);
    assert(err->msg_code == 0);
    assert(err->last_jpeg_message == (int)JMSG_LASTMSGCODE - 1);
    assert(err->addon_message_table == NULL);
    assert(err->first_addon_message == 0);
    assert(err->last_addon_message == 0);

    assert(err->error_exit != NULL);
    assert(err->emit_message != NULL);
    assert(err->output_message != NULL);
    assert(err->format_message != NULL);
    assert(err->reset_error_mgr != NULL);

    return err;
}
