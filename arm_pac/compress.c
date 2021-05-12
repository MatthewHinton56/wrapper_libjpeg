#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "jpeg_error_mgr_wrapper.h"
#include "jpeg_compress_wrapper.h"

int test(int argc, char **argv) {

    Jpeg_compress cinfo;
    
    jpeg_std_error_compress_wrapped(cinfo.get_cinfo(),cinfo.get_id());
        printf("hello world\n");
    /* this is a pointer to one row of image data */
    JSAMPROW row_pointer[1];
    Insert_newBlock_withID(cinfo.get_id(), (uintptr_t)row_pointer, (size_t)sizeof(JSAMPROW *), 0);
        printf("hello world\n");
    char *inputfile_name = argv[1];
    FILE *inputfile = fopen(inputfile_name, "r");
    fseek(inputfile, 0, SEEK_END);          // Jump to the end of the file
    size_t filelen = ftell(inputfile);             // Get the current byte offset in the file
    rewind(inputfile);                      // Jump back to the beginning of the file
        printf("hello world\n");
    char *raw_image = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    Insert_newBlock_withID(cinfo.get_id(), (uintptr_t)raw_image, (size_t)(filelen*sizeof(char)), 0);
        printf("hello world\n");
    fread(raw_image, filelen, 1, inputfile); // Read in the entire file
    fclose(inputfile);
          printf("hello world\n");
    FILE *outfile = fopen(argv[6], "wb" );
           printf("hello world\n");
    if ( !outfile )
    {
        printf("Error opening output jpeg file %s\n!", argv[2] );
        return -1;
    }
          printf("hello world\n");
    cinfo.jpeg_CreateCompress_wrapped(JPEG_LIB_VERSION, (size_t)sizeof(struct jpeg_compress_struct));
            printf("hello world\n");
    cinfo.jpeg_stdio_dest_wrapped(outfile);
           printf("hello world\n");
    /* Setting the parameters of the output file here */
    cinfo.get_cinfo()->image_width = atoi(argv[2]);  
    cinfo.get_cinfo()->image_height = atoi(argv[3]);
    cinfo.get_cinfo()->input_components = atoi(argv[4]);
    cinfo.get_cinfo()->in_color_space = (atoi(argv[5]) == 1) ? JCS_EXT_RGB : JCS_GRAYSCALE;
        printf("hello world\n");
    /* default compression parameters, we shouldn't be worried about these */
    cinfo.jpeg_set_defaults_wrapped();
        printf("hello world\n");
    /* Now do the compression .. */
    cinfo.jpeg_start_compress_wrapped(TRUE );
        printf("hello world\n");
    /* like reading a file, this time write one row at a time */
    while( cinfo.get_cinfo()->next_scanline < cinfo.get_cinfo()->image_height )
    {
        row_pointer[0] = (JSAMPROW)(raw_image + cinfo.get_cinfo()->next_scanline * cinfo.get_cinfo()->image_width *  cinfo.get_cinfo()->input_components);
        cinfo.jpeg_write_scanlines_wrapped(row_pointer,  1 );
    }
    /* similar to read file, clean up after we're done compressing */
    cinfo.jpeg_finish_compress_wrapped();
    cinfo.jpeg_destroy_compress_wrapped();
    fclose( outfile );
    
}

int main(int argc, char **argv) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(size_t i = 0; i < 10; i++)
        test(argc, argv);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("pac_sha Compress: %s: Execution time = %ld ms\n", argv[1], delta_us / 1000 / 10);
}
