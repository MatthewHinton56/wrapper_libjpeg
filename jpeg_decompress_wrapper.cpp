#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "jpeg_decompress_wrapper.h"
#include "allocator.h"
#include "jerror.h"
#include "jpegint.h"

Jpeg_decompress::Jpeg_decompress()
{
    id = create_allocator();
    packed_ret_t ret = allocate_client(id, sizeof(struct jpeg_decompress_struct));
    cinfo_lib = (struct jpeg_decompress_struct *)ret.lib;
    cinfo_client = (struct jpeg_decompress_struct *)ret.client;
    disable_lib(id);
    printf("cinfo %p\n", cinfo_lib);
    printf("cinfo client %p\n", cinfo_client);
}

Jpeg_decompress::~Jpeg_decompress()
{
    delete_allocator(id);
}

void Jpeg_decompress::jpeg_create_decompress_wrapped() {

    void *client_data = cinfo_client->client_data;
    void *err = cinfo_client->err;

    assert(((struct jpeg_error_mgr *)lib_to_client(id, cinfo_client->err))->reset_error_mgr != NULL);
    
    enable_lib(id);
    jpeg_create_decompress(cinfo_lib);
    disable_lib(id);

    assert(((struct jpeg_error_mgr *)lib_to_client(id, cinfo_client->err))->reset_error_mgr != NULL);

    // Perform checks
    assert(cinfo_client->global_state == DSTATE_START);
    assert(cinfo_client->progress == NULL);
    assert(cinfo_client->src == NULL);

    printf("struct %p, %p\n", (void*)cinfo_client->err, err);
    assert(cinfo_client->err == err);
    assert(cinfo_client->client_data == client_data);
    assert(cinfo_client->is_decompressor == TRUE);

}


typedef struct {
  struct jpeg_source_mgr pub;

  FILE *infile;                 
  JOCTET *buffer;              
  boolean start_of_file;        
} source_mgr;

void Jpeg_decompress::jpeg_stdio_src_wrapped(FILE *infile) {
    
    struct jpeg_source_mgr *src;
    bool check_src = false;
    if (cinfo_client->src != NULL) {
        check_src = true;
        src = cinfo_client->src;
    }

    
    enable_lib(id);
    jpeg_stdio_src(cinfo_lib, infile);
    disable_lib(id);

    // Perform checks

    if (check_src) {
        assert(src == cinfo_client->src);
    }

    assert(cinfo_client->src != NULL);
    jpeg_source_mgr *client_src = (jpeg_source_mgr *)lib_to_client(id, cinfo_client->src);
    assert(client_src->bytes_in_buffer == 0);
    assert(client_src->next_input_byte == NULL);

    assert(client_src->init_source != NULL);
    assert(client_src->fill_input_buffer != NULL);
    assert(client_src->skip_input_data != NULL);
    assert(client_src->resync_to_restart != NULL);
    assert(client_src->term_source != NULL);

    assert(((source_mgr*)client_src)->infile == infile);
    // Way to check if all fields except one is changed in a struct
}

int Jpeg_decompress::jpeg_read_header_wrapped(boolean require_image) {
    
    int global_state = cinfo_client->global_state;
    enable_lib(id);
    int retcode = jpeg_read_header(cinfo_lib, require_image);
    disable_lib(id);

    // Perform checks
    assert(retcode >= JPEG_SUSPENDED && retcode <= JPEG_HEADER_TABLES_ONLY);

    if (require_image)
        assert(retcode != JPEG_HEADER_TABLES_ONLY);

    if (global_state == DSTATE_START)
        assert(cinfo_client->global_state == DSTATE_READY);

    if (global_state == DSTATE_INHEADER)
        assert(cinfo_client->global_state == DSTATE_READY);

    if (global_state != DSTATE_START && global_state != DSTATE_INHEADER)
        assert(global_state == cinfo_client->global_state);

    return retcode;
}

boolean Jpeg_decompress::jpeg_start_decompress_wrapped() {
    
    int global_state = cinfo_client->global_state;
    boolean buffered_image = cinfo_client->buffered_image;
    boolean raw_data_out = cinfo_client->raw_data_out;

    enable_lib(id);
    boolean output = jpeg_start_decompress(cinfo_lib);
    disable_lib(id);

    if (buffered_image) {
        assert(cinfo_client->global_state == DSTATE_BUFIMAGE && output);
    }

    if (!buffered_image) {
        if (raw_data_out) {
            assert(cinfo_client->global_state == DSTATE_RAW_OK  && output);
        } else {
            assert(cinfo_client->global_state == DSTATE_SCANNING && output);
        }
    }

    return output;
}

JDIMENSION Jpeg_decompress::jpeg_read_scanlines_wrapped(JSAMPARRAY scanlines, JDIMENSION max_lines) {
    JDIMENSION output_scanline = cinfo_client->output_scanline;
    enable_lib(id);
    JDIMENSION row_ctr = jpeg_read_scanlines(cinfo_lib, scanlines, max_lines);
    disable_lib(id);


    assert(row_ctr <= max_lines);
    assert(cinfo_client->output_scanline == (row_ctr + output_scanline));

    return row_ctr;
}

boolean Jpeg_decompress::jpeg_finish_decompress_wrapped() {
    jpeg_memory_mgr *mem = cinfo_client->mem;
    enable_lib(id);
    boolean output = jpeg_finish_decompress(cinfo_lib);
    disable_lib(id);

    if (mem != NULL)
        assert(cinfo_client->global_state == DSTATE_START);
    
    return output;
}

void Jpeg_decompress::jpeg_destroy_wrapped() {
    enable_lib(id);
    jpeg_destroy_decompress(cinfo_lib);
    disable_lib(id);

    assert(cinfo_client->mem == NULL);
    assert(cinfo_client->global_state == 0);
}