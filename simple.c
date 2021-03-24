#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "jpeg_error_mgr_wrapper.h"
#include "jpeg_decompress_wrapper.h"

int main(int argc, char **argv) {
    unsigned long bmp_size;
	unsigned char *bmp_buffer;
	int row_stride, width, height, pixel_size;

    Jpeg_decompress cinfo;
    Jpeg_error_mgr jerr;

    FILE *input_file = fopen(argv[1], "rb");

    cinfo.get_cinfo()->err = jerr.jpeg_std_error_wrapped();
    cinfo.jpeg_create_decompress_wrapped();

    cinfo.jpeg_stdio_src_wrapped(input_file);
    cinfo.jpeg_read_header_wrapped(TRUE);

    cinfo.jpeg_start_decompress_wrapped();

    width = cinfo.get_cinfo()->output_width;
	height = cinfo.get_cinfo()->output_height;
	pixel_size = cinfo.get_cinfo()->output_components;

    bmp_size = width * height * pixel_size;
	bmp_buffer = (unsigned char*) malloc(bmp_size);

    row_stride = width * pixel_size;

    while (cinfo.get_cinfo()->output_scanline < cinfo.get_cinfo()->output_height) {
		unsigned char *buffer_array[1];
		buffer_array[0] = bmp_buffer + \
						   (cinfo.get_cinfo()->output_scanline) * row_stride;

		cinfo.jpeg_read_scanlines_wrapped(buffer_array, 1);

	}

    fclose(input_file);

    cinfo.jpeg_finish_decompress_wrapped();
    jpeg_destroy_decompress(cinfo.get_cinfo());

    int fd = open("output.ppm", O_CREAT | O_WRONLY, 0666);
	char buf[1024];

	int rc = sprintf(buf, "P6 %d %d 255\n", width, height);
	write(fd, buf, rc); // Write the PPM image header before data
	write(fd, bmp_buffer, bmp_size); // Write out all RGB pixel data

	close(fd);
	free(bmp_buffer);
}