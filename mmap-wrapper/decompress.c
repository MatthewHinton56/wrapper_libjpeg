#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "jpeglib_wrapped.h"

int test(int argc, char **argv) {
    unsigned long bmp_size;
	int row_stride, width, height, pixel_size;


    uint64_t id = create_allocator();
    //printf("id: %lld\n", id);
    //disable_lib(id);

    packed_ret_t ret = allocate_client(id, sizeof(struct jpeg_decompress_struct));
    struct jpeg_decompress_struct *cinfo_lib = (struct jpeg_decompress_struct *)ret.lib;
    struct jpeg_decompress_struct *cinfo_client = (struct jpeg_decompress_struct *)ret.client;

    ret = allocate_client(id, sizeof(struct jpeg_error_mgr));
    struct jpeg_error_mgr *err_client = (struct jpeg_error_mgr *)ret.client;
    struct jpeg_error_mgr *err_lib = (struct jpeg_error_mgr *)ret.lib;

    //printf("%p %p\n", cinfo_lib, cinfo_client);
    //cinfo_lib->err = err_lib;

    FILE *input_file = fopen(argv[1], "rb");

    jpeg_std_error_wrapped(id, err_client, err_lib);
    cinfo_client->err = err_lib;

    jpeg_CreateDecompress_wrapped(id, cinfo_client, cinfo_lib, JPEG_LIB_VERSION, (size_t)sizeof(struct jpeg_decompress_struct));

    //cinfo.get_cinfo()->err = jpeg_std_error_wrapped(cinfo.get_id());
    //cinfo.jpeg_create_decompress_wrapped();
    //printf("here\n");
    
    //cinfo.jpeg_stdio_src_wrapped(input_file);
    jpeg_stdio_src_wrapped(id, cinfo_client, cinfo_lib, input_file, input_file);
    

    //printf("here-1\n");
    //cinfo.jpeg_read_header_wrapped(TRUE);
    jpeg_read_header_wrapped(id, cinfo_client, cinfo_lib, TRUE);
    //printf("here-2\n");

    //cinfo.jpeg_start_decompress_wrapped();
    jpeg_start_decompress_wrapped(id, cinfo_client, cinfo_lib);

    width = cinfo_client->output_width;
	height = cinfo_client->output_height;
	pixel_size = cinfo_client->output_components;

    bmp_size = width * height * pixel_size;

    //bmp_buffer = (unsigned char*) malloc(bmp_size);

    ret = allocate_client(id, bmp_size);
    unsigned char *bmp_buffer_client = (unsigned char*)ret.client;
    unsigned char *bmp_buffer_lib = (unsigned char*)ret.lib;

    row_stride = width * pixel_size;
    
    ret = allocate_client(id, sizeof(unsigned char *));
    unsigned char **buffer_array_client = (unsigned char**)ret.client;
    unsigned char **buffer_array_lib = (unsigned char**)ret.lib;

    while (cinfo_client->output_scanline < cinfo_client->output_height) {
		buffer_array_client[0] = bmp_buffer_lib + (cinfo_client->output_scanline) * row_stride;
        jpeg_read_scanlines_wrapped(id, cinfo_client, cinfo_lib, buffer_array_client, buffer_array_lib, 1);
	}

    fclose(input_file);
    
    jpeg_finish_decompress_wrapped(id, cinfo_client, cinfo_lib);
    jpeg_destroy_wrapped(id, cinfo_client, (j_common_ptr)cinfo_lib);

    int fd = open(argv[2], O_CREAT | O_WRONLY, 0666);
	char buf[1024];

	int rc = sprintf(buf, "P6 %d %d 255\n", width, height);
	write(fd, buf, rc); // Write the PPM image header before data
	write(fd, bmp_buffer_client, bmp_size); // Write out all RGB pixel data

	close(fd);
    delete_allocator(id);
}

int main(int argc, char **argv) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for(size_t i = 0; i < 10; i++)
        test(argc, argv);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    uint64_t delta_us = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("mmap Decompress: %s: Execution time = %ld ms\n", argv[1], delta_us / 1000 / 10);
}