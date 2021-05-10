#include "jpeglib.h"
#include "jerror.h"
#include <cstdint>
 

struct jpeg_error_mgr * jpeg_std_error_wrapped(int id);
