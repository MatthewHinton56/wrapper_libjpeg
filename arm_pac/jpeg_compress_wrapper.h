#include "jpeglib.h"
#include <cstdint>
#include "Documentor.h" 
class Jpeg_compress
{
private:
    int id;
    struct jpeg_compress_struct *cinfo;
 
public:
    Jpeg_compress();
    ~Jpeg_compress();
 
    struct jpeg_compress_struct *get_cinfo() { return cinfo; }
    uint64_t get_id() {return id;}
    void jpeg_CreateCompress_wrapped( int version, size_t structsize);
    void jpeg_stdio_dest_wrapped(FILE * outfile);
    void jpeg_set_defaults_wrapped();
    void jpeg_start_compress_wrapped(boolean write_all_tables);
    JDIMENSION jpeg_write_scanlines_wrapped( JSAMPARRAY scanlines, JDIMENSION num_lines);
    void jpeg_finish_compress_wrapped();
    void jpeg_destroy_compress_wrapped();
};
