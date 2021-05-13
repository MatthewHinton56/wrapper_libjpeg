

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include "jpeglib.h"

int test(int argc, char **argv) {
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    /* this is a pointer to one row of image data */
    JSAMPROW row_pointer[1];

    char *inputfile_name = argv[1];
    //printf("%s\n", inputfile_name);


    FILE *inputfile = fopen(inputfile_name, "r");
    fseek(inputfile, 0, SEEK_END);          // Jump to the end of the file
    size_t filelen = ftell(inputfile);             // Get the current byte offset in the file
    rewind(inputfile);                      // Jump back to the beginning of the file

    char *raw_image = (char *)malloc(filelen * sizeof(char)); // Enough memory for the file
    fread(raw_image, filelen, 1, inputfile); // Read in the entire file
    fclose(inputfile);

    FILE *outfile = fopen(argv[6], "wb" );

    if ( !outfile )
    {
        printf("Error opening output jpeg file %s\n!", argv[2] );
        return -1;
    }
    cinfo.err = jpeg_std_error( &jerr );
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    /* Setting the parameters of the output file here */
    cinfo.image_width = atoi(argv[2]);  
    cinfo.image_height = atoi(argv[3]);
    cinfo.input_components = atoi(argv[4]);
    cinfo.in_color_space = (atoi(argv[5]) == 1) ? JCS_RGB : JCS_GRAYSCALE;
    //printf("%d %d %d %d\n", cinfo.image_width, cinfo.image_height, cinfo.input_components, cinfo.in_color_space);
    /* default compression parameters, we shouldn't be worried about these */
    jpeg_set_defaults( &cinfo );
    /* Now do the compression .. */
    jpeg_start_compress( &cinfo, TRUE );
    /* like reading a file, this time write one row at a time */
    while( cinfo.next_scanline < cinfo.image_height )
    {
        row_pointer[0] = &raw_image[ cinfo.next_scanline * cinfo.image_width *  cinfo.input_components];
        jpeg_write_scanlines( &cinfo, row_pointer, 1 );
    }
    /* similar to read file, clean up after we're done compressing */
    jpeg_finish_compress( &cinfo );
    jpeg_destroy_compress( &cinfo );
    fclose( outfile );
}

int main(int argc, char **argv) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(size_t i = 0; i < 10; i++)
        test(argc, argv);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("Base Compress: %s: Execution time = %ld ms\n", argv[1], delta_us / 1000 / 10);
}