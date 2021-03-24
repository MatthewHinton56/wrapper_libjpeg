
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "jpeg_error_mgr_wrapper.h"


Jpeg_error_mgr::Jpeg_error_mgr()
{
    char file_template[] = "jpeg_error_mgrXXXXXX";
    fd =  mkstemp(file_template);
    unlink(file_template);
    if (fd == -1)
        fprintf(stderr, "Error creating file: %s\n", strerror( errno ));
    ftruncate(fd, sizeof(struct jpeg_error_mgr));
    void *addr = mmap(NULL, sizeof(struct jpeg_error_mgr), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(((int64_t)addr) == -1)
        fprintf(stderr, "Error mapping file: %s\n", strerror( errno ));
    err = (struct jpeg_error_mgr *) addr;

}

struct jpeg_error_mgr *Jpeg_error_mgr::jpeg_std_error_wrapped() {
    struct jpeg_error_mgr *temp = err;
    err = jpeg_std_error(err);
    assert(err == temp); // Check it returned the correct pointer

    // Remap so the library doesnt have the proper pointer, then unmap the original
    void *addr = mmap(NULL, sizeof(struct jpeg_error_mgr), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    munmap(err, sizeof(struct jpeg_error_mgr));
    if(((int64_t)addr) == -1)
        fprintf(stderr, "Error re mapping file: %s\n", strerror( errno ));

    assert (err != addr);
    err = (struct jpeg_error_mgr *) addr;

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

Jpeg_error_mgr::~Jpeg_error_mgr()
{
    munmap(err, sizeof(struct jpeg_error_mgr));
    close(fd);
}