#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "jpeglib.h"

int test(int argc, char **argv) {
    unsigned long bmp_size;
	unsigned char *bmp_buffer;
	int row_stride, width, height, pixel_size;

    struct jpeg_decompress_struct *cinfo = malloc(sizeof(struct jpeg_decompress_struct));
    struct jpeg_error_mgr *err = malloc(sizeof(struct jpeg_decompress_struct));

    //printf("%s\n", argv[1]);
    FILE *input_file = fopen(argv[1], "rb");

    err = jpeg_std_error(err);
    cinfo->err = err;

    jpeg_CreateDecompress(cinfo, JPEG_LIB_VERSION, (size_t)sizeof(struct jpeg_decompress_struct));

    jpeg_stdio_src(cinfo, input_file);
    
    jpeg_read_header(cinfo, TRUE);

    jpeg_start_decompress(cinfo);

    width = cinfo->output_width;
	height = cinfo->output_height;
	pixel_size = cinfo->output_components;

    bmp_size = width * height * pixel_size;

	bmp_buffer = (unsigned char*) malloc(bmp_size);

    row_stride = width * pixel_size;
    
    while (cinfo->output_scanline < cinfo->output_height) {
		unsigned char *buffer_array[1];
		buffer_array[0] = bmp_buffer + \
						   (cinfo->output_scanline) * row_stride;
        jpeg_read_scanlines(cinfo, buffer_array, 1);
	}

    fclose(input_file);

    jpeg_finish_decompress(cinfo);
    jpeg_destroy((j_common_ptr)cinfo);

    int fd = open(argv[2], O_CREAT | O_WRONLY, 0666);
	char buf[1024];

	int rc = sprintf(buf, "P6 %d %d 255\n", width, height);
	write(fd, buf, rc); // Write the PPM image header before data
	write(fd, bmp_buffer, bmp_size); // Write out all RGB pixel data

	close(fd);
	free(bmp_buffer);
}

int main(int argc, char **argv) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(size_t i = 0; i < 10; i++)
        test(argc, argv);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("Base Decompress: %s: Execution time = %ld ms\n", argv[1], delta_us / 1000 / 10);
}