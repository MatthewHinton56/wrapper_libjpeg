#include "jpeglib.h"
#include "jerror.h"

 
class Jpeg_error_mgr
{
private:
    int fd;
    struct jpeg_error_mgr *err;
 
public:
    Jpeg_error_mgr();
    ~Jpeg_error_mgr();
 
    struct jpeg_error_mgr *get_jpeg_error_mgr() { return err; }
    struct jpeg_error_mgr * jpeg_std_error_wrapped();
};