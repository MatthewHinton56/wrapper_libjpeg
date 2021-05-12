#include "jpeglib.h"
#include "jerror.h"
#include <cstdint>
 
struct jpeg_error_mgr * jpeg_std_error_wrapped(struct jpeg_decompress_struct * my_cinfo, int id);
struct jpeg_error_mgr * jpeg_std_error_compress_wrapped(struct jpeg_compress_struct * my_cinfo, int id);
