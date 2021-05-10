#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "jpeg_decompress_wrapper.h"
#include "Documentor.h"
#include "jerror.h"
#include "jpegint.h"

Jpeg_decompress::Jpeg_decompress()
{
    id = Insert_newDoc();
    cinfo = (struct jpeg_decompress_struct *)malloc(sizeof(jpeg_decompress_struct));
    Insert_newBlock_withID(id, (uintptr_t)cinfo, (size_t)sizeof(jpeg_decompress_struct));
    compute_Hash(id, 0);
    printf("cinfo %p\n", cinfo);
}

Jpeg_decompress::~Jpeg_decompress()
{
    Delete_Doc(id);
}

void Jpeg_decompress::jpeg_create_decompress_wrapped() {

    
    assert(cinfo->err->reset_error_mgr != NULL);
    compute_Hash(id, 1);    
    jpeg_create_decompress(cinfo);
    compute_Hash(id, 0);
    // Perform checks
    assert(cinfo->global_state == DSTATE_START);
    assert(cinfo->progress == NULL);
    assert(cinfo->src == NULL);


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
    if (cinfo->src != NULL) {
        check_src = true;
        src = cinfo->src;
    }

    compute_Hash(id, 1); 
    jpeg_stdio_src(cinfo, infile);
    compute_Hash(id, 0);
    

    // Perform checks

    if (check_src) {
        assert(src == cinfo->src);
    }

    assert(cinfo->src != NULL);
    jpeg_source_mgr *client_src = (jpeg_source_mgr *) cinfo->src;
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
    
    int global_state = cinfo->global_state;

    compute_Hash(id, 1);
    int retcode = jpeg_read_header(cinfo, require_image);
    compute_Hash(id, 0);
   

    // Perform checks
    assert(retcode >= JPEG_SUSPENDED && retcode <= JPEG_HEADER_TABLES_ONLY);

    if (require_image)
        assert(retcode != JPEG_HEADER_TABLES_ONLY);

    if (global_state == DSTATE_START)
        assert(cinfo->global_state == DSTATE_READY);

    if (global_state == DSTATE_INHEADER)
        assert(cinfo->global_state == DSTATE_READY);

    if (global_state != DSTATE_START && global_state != DSTATE_INHEADER)
        assert(global_state == cinfo->global_state);

    return retcode;
}

boolean Jpeg_decompress::jpeg_start_decompress_wrapped() {
    
    int global_state = cinfo->global_state;
    boolean buffered_image = cinfo->buffered_image;
    boolean raw_data_out = cinfo->raw_data_out;
    
    compute_Hash(id, 1);
    boolean output = jpeg_start_decompress(cinfo);
    compute_Hash(id, 0);

    if (buffered_image) {
        assert(cinfo->global_state == DSTATE_BUFIMAGE && output);
    }

    if (!buffered_image) {
        if (raw_data_out) {
            assert(cinfo->global_state == DSTATE_RAW_OK  && output);
        } else {
            assert(cinfo->global_state == DSTATE_SCANNING && output);
        }
    }

    return output;
}

JDIMENSION Jpeg_decompress::jpeg_read_scanlines_wrapped(JSAMPARRAY scanlines, JDIMENSION max_lines) {
    JDIMENSION output_scanline = cinfo->output_scanline;

    compute_Hash(id, 1);
    JDIMENSION row_ctr = jpeg_read_scanlines(cinfo, scanlines, max_lines);
    compute_Hash(id, 0);

    assert(row_ctr <= max_lines);
    assert(cinfo->output_scanline == (row_ctr + output_scanline));

    return row_ctr;
}

boolean Jpeg_decompress::jpeg_finish_decompress_wrapped() {
    jpeg_memory_mgr *mem = cinfo->mem;

    compute_Hash(id, 1);
    boolean output = jpeg_finish_decompress(cinfo);
    compute_Hash(id, 0);


    if (mem != NULL)
        assert(cinfo->global_state == DSTATE_START);
    
    return output;
}

void Jpeg_decompress::jpeg_destroy_wrapped() {

    compute_Hash(id, 1);

    jpeg_destroy_decompress(cinfo);
    compute_Hash(id, 0);


    assert(cinfo->mem == NULL);
    assert(cinfo->global_state == 0);
}
