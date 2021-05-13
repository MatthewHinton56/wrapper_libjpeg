CC=gcc

all: compress_base decompress_base

compress_base: compress.c
	$(CC) -O2 -o compress_base compress.c libjpeg_base.a libturbojpeg_base.a

decompress_base: decompress.c
	$(CC) -O2 -o decompress_base decompress.c libjpeg_base.a libturbojpeg_base.a

.PHONY: clean

clean:
	rm -rf compress_base decompress_base