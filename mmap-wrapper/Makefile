CC=gcc

all: compress_mmap decompress_mmap

wrapped_malloc.o: wrapped_malloc.c
	gcc -c wrapped_malloc.c

compress_mmap: compress.c wrapped_malloc.o allocator.c
	$(CC) -O2 -o compress_mmap jpeglib_wrapped.c -Wl,--wrap,wmalloc -Wl,--wrap,wfree compress.c wrapped_malloc.o libturbojpeg.a allocator.c

decompress_mmap: decompress.c wrapped_malloc.o allocator.c
	$(CC) -O2  -o decompress_mmap jpeglib_wrapped.c -Wl,--wrap,wmalloc -Wl,--wrap,wfree decompress.c wrapped_malloc.o libturbojpeg.a allocator.c -ggdb

.PHONY: clean

clean:
	rm -rf compress_mmap decompress_mmap