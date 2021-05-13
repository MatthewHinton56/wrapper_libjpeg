

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "jpeglib_wrapped.h"

int test(int argc, char **argv) {

    uint64_t id = create_allocator();
    disable_lib(id);

    packed_ret_t ret = allocate_client(id, sizeof(struct jpeg_compress_struct));
    struct jpeg_compress_struct *cinfo_lib = (struct jpeg_compress_struct *)ret.lib;
    struct jpeg_compress_struct *cinfo_client = (struct jpeg_compress_struct *)ret.client;

    ret = allocate_client(id, sizeof(struct jpeg_error_mgr));
    struct jpeg_error_mgr *err_client = (struct jpeg_error_mgr *)ret.client;
    struct jpeg_error_mgr *err_lib = (struct jpeg_error_mgr *)ret.lib;
    

    /* this is a pointer to one row of image data */
    JSAMPROW row_pointer[1];

    ret = allocate_client(id, sizeof(JSAMPROW *));
    JSAMPROW *row_pointer_client = (JSAMPROW *)ret.client;
    JSAMPROW *row_pointer_lib = (JSAMPROW *)ret.lib;

    char *inputfile_name = argv[1];
    //printf("%s\n", inputfile_name);


    FILE *inputfile = fopen(inputfile_name, "r");
    fseek(inputfile, 0, SEEK_END);          // Jump to the end of the file
    size_t filelen = ftell(inputfile);             // Get the current byte offset in the file
    rewind(inputfile);                      // Jump back to the beginning of the file

    ret = allocate_client(id, filelen * sizeof(char));
    char *raw_image_client = (char *)ret.client;
    char *raw_image_lib = (char *)ret.lib;

    //char *raw_image = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    fread(raw_image_client, filelen, 1, inputfile); // Read in the entire file
    fclose(inputfile);

    FILE *outfile = fopen(argv[6], "wb" );

    if ( !outfile )
    {
        printf("Error opening output jpeg file %s\n!", argv[2] );
        return -1;
    }
    cinfo_client->err =  jpeg_std_error_wrapped(id, err_client, err_lib);
    jpeg_CreateCompress_wrapped(id, cinfo_client, cinfo_lib, JPEG_LIB_VERSION, (size_t)sizeof(struct jpeg_compress_struct));
    //jpeg_create_compress(&cinfo);
    jpeg_stdio_dest_wrapped(id, cinfo_client, cinfo_lib, outfile, outfile);

    /* Setting the parameters of the output file here */
    cinfo_client->image_width = atoi(argv[2]);  
    cinfo_client->image_height = atoi(argv[3]);
    cinfo_client->input_components = atoi(argv[4]);
    cinfo_client->in_color_space = (atoi(argv[5]) == 1) ? JCS_EXT_RGB : JCS_GRAYSCALE;
    /* default compression parameters, we shouldn't be worried about these */
    jpeg_set_defaults_wrapped(id,  cinfo_client, cinfo_lib );
    /* Now do the compression .. */
    jpeg_start_compress_wrapped(id,  cinfo_client, cinfo_lib , TRUE );
    /* like reading a file, this time write one row at a time */
    while( cinfo_client->next_scanline < cinfo_client->image_height )
    {
        row_pointer_client[0] = raw_image_lib + cinfo_client->next_scanline * cinfo_client->image_width *  cinfo_client->input_components;
        jpeg_write_scanlines_wrapped(id,  cinfo_client, cinfo_lib , row_pointer_client, row_pointer_lib,  1 );
    }
    /* similar to read file, clean up after we're done compressing */
    jpeg_finish_compress_wrapped(id,  cinfo_client, cinfo_lib);
    jpeg_destroy_compress_wrapped(id,  cinfo_client, cinfo_lib);
    fclose( outfile );
    delete_allocator(id);
}

int main(int argc, char **argv) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(size_t i = 0; i < 10; i++)
        test(argc, argv);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("mmap Compress: %s: Execution time = %ld ms\n", argv[1], delta_us / 1000 / 10);
}