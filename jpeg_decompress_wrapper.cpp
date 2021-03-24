#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "jpeg_decompress_wrapper.h"
#include "jerror.h"
#include "jpegint.h"

Jpeg_decompress::Jpeg_decompress()
{
    char file_template[] = "jpeg_decompressXXXXXX";
    fd =  mkstemp(file_template);
    unlink(file_template);
    if (fd == -1)
        fprintf(stderr, "Error creating file: %s\n", strerror( errno ));
    ftruncate(fd, sizeof(struct jpeg_decompress_struct));
    void *addr = mmap(NULL, sizeof(struct jpeg_decompress_struct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(((int64_t)addr) == -1)
        fprintf(stderr, "Error mapping file: %s\n", strerror( errno ));
    cinfo = (struct jpeg_decompress_struct *) addr;
}

Jpeg_decompress::~Jpeg_decompress()
{
    munmap(cinfo, sizeof(struct jpeg_decompress_struct));
    close(fd);
}

struct jpeg_decompress_struct *move_cinfo(struct jpeg_decompress_struct * cinfo, int fd) {
    // Remap so the library doesnt have the proper pointer, then unmap the original
    void *addr = mmap(NULL, sizeof(struct jpeg_decompress_struct), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    munmap(cinfo, sizeof(struct jpeg_decompress_struct));
    if(((int64_t)addr) == -1)
        fprintf(stderr, "Error re mapping file: %s\n", strerror( errno ));

    assert (cinfo != addr);
    return (struct jpeg_decompress_struct *) addr;
}

void Jpeg_decompress::jpeg_create_decompress_wrapped() {

    struct jpeg_error_mgr *err = cinfo->err;
    void *client_data = cinfo->client_data;
    
    jpeg_create_decompress(cinfo);
    cinfo = move_cinfo(cinfo, fd);

    // Perform checks
    assert(cinfo->global_state == DSTATE_START);
    assert(cinfo->progress == NULL);
    assert(cinfo->src == NULL);

    assert(cinfo->err == err);
    assert(cinfo->client_data == client_data);
    assert(cinfo->is_decompressor == TRUE);

    int i;
    for (i = 0; i < NUM_QUANT_TBLS; i++)
        assert(cinfo->quant_tbl_ptrs[i] == NULL);

    for (i = 0; i < NUM_HUFF_TBLS; i++) {
        assert(cinfo->dc_huff_tbl_ptrs[i] == NULL);
        assert(cinfo->ac_huff_tbl_ptrs[i] == NULL);
    }
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
    
    jpeg_stdio_src(cinfo, infile);
    cinfo = move_cinfo(cinfo, fd);

    // Perform checks

    if (check_src) {
        assert(src == cinfo->src);
    }

    assert(cinfo->src != NULL);
    assert(cinfo->src->bytes_in_buffer == 0);
    assert(cinfo->src->next_input_byte == NULL);

    assert(cinfo->src->init_source != NULL);
    assert(cinfo->src->fill_input_buffer != NULL);
    assert(cinfo->src->skip_input_data != NULL);
    assert(cinfo->src->resync_to_restart != NULL);
    assert(cinfo->src->term_source != NULL);

    assert(((source_mgr*)cinfo->src)->infile == infile);

    // Way to check if all fields except one is changed in a struct
}

int Jpeg_decompress::jpeg_read_header_wrapped(boolean require_image) {
    
    int global_state = cinfo->global_state;
    int retcode = jpeg_read_header(cinfo, require_image);
    cinfo = move_cinfo(cinfo, fd);

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
    boolean output = jpeg_start_decompress(cinfo);
    cinfo = move_cinfo(cinfo, fd);

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
    JDIMENSION row_ctr = jpeg_read_scanlines(cinfo, scanlines, max_lines);
    cinfo = move_cinfo(cinfo, fd);


    assert(row_ctr <= max_lines);
    assert(cinfo->output_scanline == (row_ctr + output_scanline));

    return row_ctr;
}

boolean Jpeg_decompress::jpeg_finish_decompress_wrapped() {
    jpeg_memory_mgr *mem = cinfo->mem;
    boolean output = jpeg_finish_decompress(cinfo);
    cinfo = move_cinfo(cinfo, fd);

    if (mem != NULL)
        assert(cinfo->global_state == DSTATE_START);
    
    return output;
}

void Jpeg_decompress::jpeg_destroy_wrapped() {
    jpeg_destroy_decompress(cinfo);
    cinfo = move_cinfo(cinfo, fd);

    assert(cinfo->mem == NULL);
    assert(cinfo->global_state == 0);
}