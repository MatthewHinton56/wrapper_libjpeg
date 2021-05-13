#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "jpeglib.h"
#include "jerror.h"
#include "Documentor.h"


int main(int argc, char **argv) {
    int id = Insert_newDoc();

    unsigned long bmp_size;
    unsigned char *bmp_buffer;
    int row_stride, width, height, pixel_size;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    printf("Insert_newDoc %d %0x, %0x\n", id, (uintptr_t)&cinfo, (uintptr_t)&jerr);
    Insert_newBlock_withID(id, (uintptr_t)&cinfo, (size_t)sizeof(jpeg_decompress_struct));
    Insert_newBlock_withID(id, (uintptr_t)&jerr, (size_t)sizeof(jpeg_error_mgr));
    uint8_t * temp = (uint8_t *)&cinfo;
     
    
    FILE *input_file = fopen(argv[1], "rb");
    cinfo.err = jpeg_std_error(&jerr);
        
    jpeg_create_decompress(&cinfo);
    
    jpeg_stdio_src(&cinfo, input_file);
    
    (void)jpeg_read_header(&cinfo, TRUE);
    
    (void)jpeg_start_decompress(&cinfo);

    //printf("hello world\n");
    width = cinfo.output_width;
    height = cinfo.output_height;
    pixel_size = cinfo.output_components;

    bmp_size = width * height * pixel_size;
    bmp_buffer = (unsigned char*) malloc(bmp_size);

    row_stride = width * pixel_size;
    
    while (cinfo.output_scanline < cinfo.output_height) {
	unsigned char *buffer_array[1];
	buffer_array[0] = bmp_buffer + (cinfo.output_scanline) * row_stride;
        (void)jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }
    
    fclose(input_file);

    (void)jpeg_finish_decompress(&cinfo);
    
    jpeg_destroy_decompress(&cinfo);

    int fd = open("output.ppm", O_CREAT | O_WRONLY, 0666);
    char buf[1024];

    int rc = sprintf(buf, "P6 %d %d 255\n", width, height);
    write(fd, buf, rc); // Write the PPM image header before data
    write(fd, bmp_buffer, bmp_size); // Write out all RGB pixel data

    close(fd);
    free(bmp_buffer);
}
