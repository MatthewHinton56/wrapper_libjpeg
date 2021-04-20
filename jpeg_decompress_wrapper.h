#include "jpeglib.h"
#include <cstdint>
 
class Jpeg_decompress
{
private:
    uint64_t id;
    struct jpeg_decompress_struct *cinfo_client;
    struct jpeg_decompress_struct *cinfo_lib;
 
public:
    Jpeg_decompress();
    ~Jpeg_decompress();
 
    struct jpeg_decompress_struct *get_cinfo() { return cinfo_client; }
    uint64_t get_id() {return id;}
    void jpeg_create_decompress_wrapped();
    void jpeg_stdio_src_wrapped(FILE *infile);
    int jpeg_read_header_wrapped(boolean require_image);
    boolean jpeg_start_decompress_wrapped();
    JDIMENSION jpeg_read_scanlines_wrapped(JSAMPARRAY scanlines, JDIMENSION max_lines);
    boolean jpeg_finish_decompress_wrapped();
    void jpeg_destroy_wrapped();
};