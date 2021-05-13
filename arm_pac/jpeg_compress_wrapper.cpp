#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <assert.h>
#include "jpeg_compress_wrapper.h"
#include "jerror.h"
#include "jpegint.h"

Jpeg_compress::Jpeg_compress()
{
    id = Insert_newDoc();
    cinfo = (struct jpeg_compress_struct *)malloc(sizeof(jpeg_compress_struct));
    Insert_newBlock_withID(id, (uintptr_t)cinfo, (size_t)sizeof(jpeg_compress_struct), 1);
    compute_Hash(id, 0);
    printf("cinfo %p\n", cinfo);
}

Jpeg_compress::~Jpeg_compress()
{
    Delete_Doc(id);
}

void Jpeg_compress::jpeg_CreateCompress_wrapped(int version, size_t structsize) {

		
	jpeg_CreateCompress(cinfo, version, structsize);
	
}

void Jpeg_compress::jpeg_stdio_dest_wrapped(FILE * outfile) {
	
	jpeg_stdio_dest(cinfo, outfile);
	
}

void Jpeg_compress::jpeg_set_defaults_wrapped() {

	jpeg_set_defaults(cinfo);
	
}

void Jpeg_compress::jpeg_start_compress_wrapped( boolean write_all_tables) {

	jpeg_start_compress(cinfo, write_all_tables);
	
}

JDIMENSION Jpeg_compress::jpeg_write_scanlines_wrapped(JSAMPARRAY scanlines, JDIMENSION num_lines) {
	
	JDIMENSION ret = jpeg_write_scanlines(cinfo, scanlines, num_lines);
	
	return ret;
}

void Jpeg_compress::jpeg_finish_compress_wrapped() {
	jpeg_finish_compress(cinfo);
	
}

void Jpeg_compress::jpeg_destroy_compress_wrapped() {
	jpeg_destroy_compress(cinfo);
	
}

