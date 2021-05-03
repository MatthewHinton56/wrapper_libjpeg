/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */



/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */

/* We do not support C11 <threads.h>.  */

/*
 * jpeglib.h
 *
 * This file was part of the Independent JPEG Group's software:
 * Copyright (C) 1991-1998, Thomas G. Lane.
 * Modified 2002-2009 by Guido Vollbeding.
 * libjpeg-turbo Modifications:
 * Copyright (C) 2009-2011, 2013-2014, 2016-2017, 2020, D. R. Commander.
 * Copyright (C) 2015, Google, Inc.
 * For conditions of distribution and use, see the accompanying README.ijg
 * file.
 *
 * This file defines the application interface for the JPEG library.
 * Most applications using the library need only include this file,
 * and perhaps jerror.h if they want to know the exact error codes.
 */


/*
 * First we include the configuration files that record how this
 * installation of the JPEG library is set up.  jconfig.h can be
 * generated automatically for many systems.  jmorecfg.h contains
 * manual configuration options that most people need not worry about.
 */

/* Version ID for the JPEG library.
 * Might be useful for tests like "#if JPEG_LIB_VERSION >= 60".
 */

/* libjpeg-turbo version */

/* libjpeg-turbo version in integer form */

/* Support arithmetic encoding */

/* Support arithmetic decoding */

/* Support in-memory source/destination managers */

/* Use accelerated SIMD routines. */

/*
 * Define BITS_IN_JSAMPLE as either
 *   8   for 8-bit sample values (the usual setting)
 *   12  for 12-bit sample values
 * Only 8 and 12 are legal data precisions for lossy JPEG according to the
 * JPEG standard, and the IJG code does not support anything else!
 * We do not support run-time selection of data precision, sorry.
 */


/* Define to 1 if you have the <locale.h> header file. */

/* Define to 1 if you have the <stddef.h> header file. */

/* Define to 1 if you have the <stdlib.h> header file. */

/* Define if you need to include <sys/types.h> to get size_t. */

/* Define if you have BSD-like bzero and bcopy in <strings.h> rather than
   memset/memcpy in <string.h>. */
/* #undef NEED_BSD_STRINGS */

/* Define to 1 if the system has the type `unsigned char'. */

/* Define to 1 if the system has the type `unsigned short'. */

/* Compiler does not support pointers to undefined structures. */
/* #undef INCOMPLETE_TYPES_BROKEN */

/* Define if your (broken) compiler shifts signed values as if they were
   unsigned. */
/* #undef RIGHT_SHIFT_IS_UNSIGNED */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `unsigned int' if <sys/types.h> does not define. */
/* #undef size_t */
/*
 * jmorecfg.h
 *
 * This file was part of the Independent JPEG Group's software:
 * Copyright (C) 1991-1997, Thomas G. Lane.
 * Modified 1997-2009 by Guido Vollbeding.
 * libjpeg-turbo Modifications:
 * Copyright (C) 2009, 2011, 2014-2015, 2018, 2020, D. R. Commander.
 * For conditions of distribution and use, see the accompanying README.ijg
 * file.
 *
 * This file contains additional configuration options that customize the
 * JPEG software for special applications or support machine-dependent
 * optimizations.  Most users will not need to touch this file.
 */


/*
 * Maximum number of components (color channels) allowed in JPEG image.
 * To meet the letter of Rec. ITU-T T.81 | ISO/IEC 10918-1, set this to 255.
 * However, darn few applications need more than 4 channels (maybe 5 for CMYK +
 * alpha mask).  We recommend 10 as a reasonable compromise; use 4 if you are
 * really short on memory.  (Each allowed component costs a hundred or so
 * bytes of storage, whether actually used in an image or not.)
 */



/*
 * Basic data types.
 * You may need to change these if you have a machine with unusual data
 * type sizes; for example, "char" not 8 bits, "short" not 16 bits,
 * or "long" not 32 bits.  We don't care whether "int" is 16 or 32 bits,
 * but it had better be at least 16.
 */

/* Representation of a single sample (pixel element value).
 * We frequently allocate large arrays of these, so it's important to keep
 * them small.  But if you have memory to burn and access to char or short
 * arrays is very slow on your hardware, you might want to change these.
 */

/* JSAMPLE should be the smallest type that will hold the values 0..255.
 */

typedef unsigned char JSAMPLE;






/* Representation of a DCT frequency coefficient.
 * This should be a signed value of at least 16 bits; "short" is usually OK.
 * Again, we allocate large arrays of these, but you can change to int
 * if you have memory to burn and "short" is really slow.
 */

typedef short JCOEF;


/* Compressed datastreams are represented as arrays of JOCTET.
 * These must be EXACTLY 8 bits wide, at least once they are written to
 * external storage.  Note that when using the stdio data source/destination
 * managers, this is also the data type passed to fread/fwrite.
 */

typedef unsigned char JOCTET;


/* These typedefs are used for various table entries and so forth.
 * They must be at least as wide as specified; but making them too big
 * won't cost a huge amount of memory, so we don't provide special
 * extraction code like we did for JSAMPLE.  (In other words, these
 * typedefs live at a different point on the speed/space tradeoff curve.)
 */

/* UINT8 must hold at least the values 0..255. */

typedef unsigned char UINT8;

/* UINT16 must hold at least the values 0..65535. */

typedef unsigned short UINT16;

/* INT16 must hold at least the values -32768..32767. */

typedef short INT16;

/* INT32 must hold at least signed 32-bit values.
 *
 * NOTE: The INT32 typedef dates back to libjpeg v5 (1994.)  Integers were
 * sometimes 16-bit back then (MS-DOS), which is why INT32 is typedef'd to
 * long.  It also wasn't common (or at least as common) in 1994 for INT32 to be
 * defined by platform headers.  Since then, however, INT32 is defined in
 * several other common places:
 *
 * Xmd.h (X11 header) typedefs INT32 to int on 64-bit platforms and long on
 * 32-bit platforms (i.e always a 32-bit signed type.)
 *
 * basetsd.h (Win32 header) typedefs INT32 to int (always a 32-bit signed type
 * on modern platforms.)
 *
 * qglobal.h (Qt header) typedefs INT32 to int (always a 32-bit signed type on
 * modern platforms.)
 *
 * This is a recipe for conflict, since "long" and "int" aren't always
 * compatible types.  Since the definition of INT32 has technically been part
 * of the libjpeg API for more than 20 years, we can't remove it, but we do not
 * use it internally any longer.  We instead define a separate type (JLONG)
 * for internal use, which ensures that internal behavior will always be the
 * same regardless of any external headers that may be included.
 */

typedef long INT32;

/* Datatype used for image dimensions.  The JPEG standard only supports
 * images up to 64K*64K due to 16-bit fields in SOF markers.  Therefore
 * "unsigned int" is sufficient on all machines.  However, if you need to
 * handle larger images and you don't mind deviating from the spec, you
 * can change this datatype.  (Note that changing this datatype will
 * potentially require modifying the SIMD code.  The x86-64 SIMD extensions,
 * in particular, assume a 32-bit JDIMENSION.)
 */

typedef unsigned int JDIMENSION;



/* These macros are used in all function definitions and extern declarations.
 * You could modify them if you need to change function linkage conventions;
 * in particular, you'll need to do that to make the library a Windows DLL.
 * Another application is to make all functions global for use with debuggers
 * or code profilers that require it.
 */

/* a function called through method pointers: */
/* a function used only in its module: */
/* a function referenced thru EXTERNs: */
/* a reference to a GLOBAL function: */


/* Originally, this macro was used as a way of defining function prototypes
 * for both modern compilers as well as older compilers that did not support
 * prototype parameters.  libjpeg-turbo has never supported these older,
 * non-ANSI compilers, but the macro is still included because there is some
 * software out there that uses it.
 */



/* libjpeg-turbo no longer supports platforms that have far symbols (MS-DOS),
 * but again, some software relies on this macro.
 */



/*
 * On a few systems, type boolean and/or its values FALSE, TRUE may appear
 * in standard header files.  Or you may have conflicts with application-
 * specific header files that you want to include together with these files.
 * Defining HAVE_BOOLEAN before including jpeglib.h should make it work.
 */

typedef int boolean;


/*
 * The remaining options affect code selection within the JPEG library,
 * but they don't need to be visible to most applications using the library.
 * To minimize application namespace pollution, the symbols won't be
 * defined unless JPEG_INTERNALS or JPEG_INTERNAL_OPTIONS has been defined.
 */






/* Various constants determining the sizes of things.
 * All of these are specified by the JPEG standard, so don't change them
 * if you want to be compatible.
 */

/* Unfortunately, some bozo at Adobe saw no reason to be bound by the standard;
 * the PostScript DCT filter can emit files with many more than 10 blocks/MCU.
 * If you happen to run across such a file, you can up D_MAX_BLOCKS_IN_MCU
 * to handle it.  We even let you do this from the jconfig.h file.  However,
 * we strongly discourage changing C_MAX_BLOCKS_IN_MCU; just because Adobe
 * sometimes emits noncompliant files doesn't mean you should too.
 */


/* Data structures for images (arrays of samples and of DCT coefficients).
 */

typedef JSAMPLE *JSAMPROW;      /* ptr to one image row of pixel samples. */
typedef JSAMPROW *JSAMPARRAY;   /* ptr to some rows (a 2-D sample array) */
typedef JSAMPARRAY *JSAMPIMAGE; /* a 3-D sample array: top index is color */

typedef JCOEF JBLOCK[64]; /* one block of coefficients */
typedef JBLOCK *JBLOCKROW;      /* pointer to one row of coefficient blocks */
typedef JBLOCKROW *JBLOCKARRAY;         /* a 2-D array of coefficient blocks */
typedef JBLOCKARRAY *JBLOCKIMAGE;       /* a 3-D array of coefficient blocks */

typedef JCOEF *JCOEFPTR;        /* useful in a couple of places */


/* Types for JPEG compression parameters and working tables. */


/* DCT coefficient quantization tables. */

typedef struct {
  /* This array gives the coefficient quantizers in natural array order
   * (not the zigzag order in which they are stored in a JPEG DQT marker).
   * CAUTION: IJG versions prior to v6a kept this array in zigzag order.
   */
  UINT16 quantval[64];    /* quantization step for each coefficient */
  /* This field is used only during compression.  It's initialized FALSE when
   * the table is created, and set TRUE when it's been output to the file.
   * You could suppress output of a table by setting this to TRUE.
   * (See jpeg_suppress_tables for an example.)
   */
  boolean sent_table;           /* TRUE when table has been output */
} JQUANT_TBL;


/* Huffman coding tables. */

typedef struct {
  /* These two fields directly represent the contents of a JPEG DHT marker */
  UINT8 bits[17];               /* bits[k] = # of symbols with codes of */
                                /* length k bits; bits[0] is unused */
  UINT8 huffval[256];           /* The symbols, in order of incr code length */
  /* This field is used only during compression.  It's initialized FALSE when
   * the table is created, and set TRUE when it's been output to the file.
   * You could suppress output of a table by setting this to TRUE.
   * (See jpeg_suppress_tables for an example.)
   */
  boolean sent_table;           /* TRUE when table has been output */
} JHUFF_TBL;


/* Basic info about one component (color channel). */

typedef struct {
  /* These values are fixed over the whole image. */
  /* For compression, they must be supplied by parameter setup; */
  /* for decompression, they are read from the SOF marker. */
  int component_id;             /* identifier for this component (0..255) */
  int component_index;          /* its index in SOF or cinfo->comp_info[] */
  int h_samp_factor;            /* horizontal sampling factor (1..4) */
  int v_samp_factor;            /* vertical sampling factor (1..4) */
  int quant_tbl_no;             /* quantization table selector (0..3) */
  /* These values may vary between scans. */
  /* For compression, they must be supplied by parameter setup; */
  /* for decompression, they are read from the SOS marker. */
  /* The decompressor output side may not use these variables. */
  int dc_tbl_no;                /* DC entropy table selector (0..3) */
  int ac_tbl_no;                /* AC entropy table selector (0..3) */

  /* Remaining fields should be treated as private by applications. */

  /* These values are computed during compression or decompression startup: */
  /* Component's size in DCT blocks.
   * Any dummy blocks added to complete an MCU are not counted; therefore
   * these values do not depend on whether a scan is interleaved or not.
   */
  JDIMENSION width_in_blocks;
  JDIMENSION height_in_blocks;
  /* Size of a DCT block in samples.  Always DCTSIZE for compression.
   * For decompression this is the size of the output from one DCT block,
   * reflecting any scaling we choose to apply during the IDCT step.
   * Values from 1 to 16 are supported.
   * Note that different components may receive different IDCT scalings.
   */
  int DCT_scaled_size;
  /* The downsampled dimensions are the component's actual, unpadded number
   * of samples at the main buffer (preprocessing/compression interface), thus
   * downsampled_width = ceil(image_width * Hi/Hmax)
   * and similarly for height.  For decompression, IDCT scaling is included, so
   * downsampled_width = ceil(image_width * Hi/Hmax * DCT_[h_]scaled_size/DCTSIZE)
   */
  JDIMENSION downsampled_width;  /* actual width in samples */
  JDIMENSION downsampled_height; /* actual height in samples */
  /* This flag is used only for decompression.  In cases where some of the
   * components will be ignored (eg grayscale output from YCbCr image),
   * we can skip most computations for the unused components.
   */
  boolean component_needed;     /* do we need the value of this component? */

  /* These values are computed before starting a scan of the component. */
  /* The decompressor output side may not use these variables. */
  int MCU_width;                /* number of blocks per MCU, horizontally */
  int MCU_height;               /* number of blocks per MCU, vertically */
  int MCU_blocks;               /* MCU_width * MCU_height */
  int MCU_sample_width;         /* MCU width in samples, MCU_width*DCT_[h_]scaled_size */
  int last_col_width;           /* # of non-dummy blocks across in last MCU */
  int last_row_height;          /* # of non-dummy blocks down in last MCU */

  /* Saved quantization table for component; NULL if none yet saved.
   * See jdinput.c comments about the need for this information.
   * This field is currently used only for decompression.
   */
  JQUANT_TBL *quant_table;

  /* Private per-component storage for DCT or IDCT subsystem. */
  void *dct_table;
} jpeg_component_info;


/* The script for encoding a multiple-scan file is an array of these: */

typedef struct {
  int comps_in_scan;            /* number of components encoded in this scan */
  int component_index[4]; /* their SOF/comp_info[] indexes */
  int Ss, Se;                   /* progressive JPEG spectral selection parms */
  int Ah, Al;                   /* progressive JPEG successive approx. parms */
} jpeg_scan_info;

/* The decompressor can save APPn and COM markers in a list of these: */

typedef struct jpeg_marker_struct *jpeg_saved_marker_ptr;

struct jpeg_marker_struct {
  jpeg_saved_marker_ptr next;   /* next in list, or NULL */
  UINT8 marker;                 /* marker code: JPEG_COM, or JPEG_APP0+n */
  unsigned int original_length; /* # bytes of data in the file */
  unsigned int data_length;     /* # bytes of data saved at data[] */
  JOCTET *data;                 /* the data contained in the marker */
  /* the marker length word is not counted in data_length or original_length */
};

/* Known color spaces. */


typedef enum {
  JCS_UNKNOWN,            /* error/unspecified */
  JCS_GRAYSCALE,          /* monochrome */
  JCS_RGB,                /* red/green/blue as specified by the RGB_RED,
                             RGB_GREEN, RGB_BLUE, and RGB_PIXELSIZE macros */
  JCS_YCbCr,              /* Y/Cb/Cr (also known as YUV) */
  JCS_CMYK,               /* C/M/Y/K */
  JCS_YCCK,               /* Y/Cb/Cr/K */
  JCS_EXT_RGB,            /* red/green/blue */
  JCS_EXT_RGBX,           /* red/green/blue/x */
  JCS_EXT_BGR,            /* blue/green/red */
  JCS_EXT_BGRX,           /* blue/green/red/x */
  JCS_EXT_XBGR,           /* x/blue/green/red */
  JCS_EXT_XRGB,           /* x/red/green/blue */
  /* When out_color_space it set to JCS_EXT_RGBX, JCS_EXT_BGRX, JCS_EXT_XBGR,
     or JCS_EXT_XRGB during decompression, the X byte is undefined, and in
     order to ensure the best performance, libjpeg-turbo can set that byte to
     whatever value it wishes.  Use the following colorspace constants to
     ensure that the X byte is set to 0xFF, so that it can be interpreted as an
     opaque alpha channel. */
  JCS_EXT_RGBA,           /* red/green/blue/alpha */
  JCS_EXT_BGRA,           /* blue/green/red/alpha */
  JCS_EXT_ABGR,           /* alpha/blue/green/red */
  JCS_EXT_ARGB,           /* alpha/red/green/blue */
  JCS_RGB565              /* 5-bit red/6-bit green/5-bit blue */
} J_COLOR_SPACE;

/* DCT/IDCT algorithm options. */

typedef enum {
  JDCT_ISLOW,             /* accurate integer method */
  JDCT_IFAST,             /* less accurate integer method [legacy feature] */
  JDCT_FLOAT              /* floating-point method [legacy feature] */
} J_DCT_METHOD;


/* Dithering options for decompression. */

typedef enum {
  JDITHER_NONE,           /* no dithering */
  JDITHER_ORDERED,        /* simple ordered dither */
  JDITHER_FS              /* Floyd-Steinberg error diffusion dither */
} J_DITHER_MODE;


/* Common fields between JPEG compression and decompression master structs. */


/* Routines that are to be used by both halves of the library are declared
 * to receive a pointer to this structure.  There are no actual instances of
 * jpeg_common_struct, only of jpeg_compress_struct and jpeg_decompress_struct.
 */
struct jpeg_common_struct {
  struct jpeg_error_mgr *err;      struct jpeg_memory_mgr *mem;     struct jpeg_progress_mgr *progress;    void *client_data;               boolean is_decompressor;         int global_state;           /* Fields common to both master struct types */
  /* Additional fields follow in an actual jpeg_compress_struct or
   * jpeg_decompress_struct.  All three structs must agree on these
   * initial fields!  (This would be a lot cleaner in C++.)
   */
};

typedef struct jpeg_common_struct *j_common_ptr;
typedef struct jpeg_compress_struct *j_compress_ptr;
typedef struct jpeg_decompress_struct *j_decompress_ptr;


/* Master record for a compression instance */

struct jpeg_compress_struct {
  struct jpeg_error_mgr *err;      struct jpeg_memory_mgr *mem;     struct jpeg_progress_mgr *progress;    void *client_data;               boolean is_decompressor;         int global_state;           /* Fields shared with jpeg_decompress_struct */

  /* Destination for compressed data */
  struct jpeg_destination_mgr *dest;

  /* Description of source image --- these fields must be filled in by
   * outer application before starting compression.  in_color_space must
   * be correct before you can even call jpeg_set_defaults().
   */

  JDIMENSION image_width;       /* input image width */
  JDIMENSION image_height;      /* input image height */
  int input_components;         /* # of color components in input image */
  J_COLOR_SPACE in_color_space; /* colorspace of input image */

  double input_gamma;           /* image gamma of input image */

  /* Compression parameters --- these fields must be set before calling
   * jpeg_start_compress().  We recommend calling jpeg_set_defaults() to
   * initialize everything to reasonable defaults, then changing anything
   * the application specifically wants to change.  That way you won't get
   * burnt when new parameters are added.  Also note that there are several
   * helper routines to simplify changing parameters.
   */


  int data_precision;           /* bits of precision in image data */

  int num_components;           /* # of color components in JPEG image */
  J_COLOR_SPACE jpeg_color_space; /* colorspace of JPEG image */

  jpeg_component_info *comp_info;
  /* comp_info[i] describes component that appears i'th in SOF */

  JQUANT_TBL *quant_tbl_ptrs[4];
  /* ptrs to coefficient quantization tables, or NULL if not defined,
   * and corresponding scale factors (percentage, initialized 100).
   */

  JHUFF_TBL *dc_huff_tbl_ptrs[4];
  JHUFF_TBL *ac_huff_tbl_ptrs[4];
  /* ptrs to Huffman coding tables, or NULL if not defined */

  UINT8 arith_dc_L[16]; /* L values for DC arith-coding tables */
  UINT8 arith_dc_U[16]; /* U values for DC arith-coding tables */
  UINT8 arith_ac_K[16]; /* Kx values for AC arith-coding tables */

  int num_scans;                /* # of entries in scan_info array */
  const jpeg_scan_info *scan_info; /* script for multi-scan file, or NULL */
  /* The default value of scan_info is NULL, which causes a single-scan
   * sequential JPEG file to be emitted.  To create a multi-scan file,
   * set num_scans and scan_info to point to an array of scan definitions.
   */

  boolean raw_data_in;          /* TRUE=caller supplies downsampled data */
  boolean arith_code;           /* TRUE=arithmetic coding, FALSE=Huffman */
  boolean optimize_coding;      /* TRUE=optimize entropy encoding parms */
  boolean CCIR601_sampling;     /* TRUE=first samples are cosited */
  int smoothing_factor;         /* 1..100, or 0 for no input smoothing */
  J_DCT_METHOD dct_method;      /* DCT algorithm selector */

  /* The restart interval can be specified in absolute MCUs by setting
   * restart_interval, or in MCU rows by setting restart_in_rows
   * (in which case the correct restart_interval will be figured
   * for each scan).
   */
  unsigned int restart_interval; /* MCUs per restart, or 0 for no restart */
  int restart_in_rows;          /* if > 0, MCU rows per restart interval */

  /* Parameters controlling emission of special markers. */

  boolean write_JFIF_header;    /* should a JFIF marker be written? */
  UINT8 JFIF_major_version;     /* What to write for the JFIF version number */
  UINT8 JFIF_minor_version;
  /* These three values are not used by the JPEG code, merely copied */
  /* into the JFIF APP0 marker.  density_unit can be 0 for unknown, */
  /* 1 for dots/inch, or 2 for dots/cm.  Note that the pixel aspect */
  /* ratio is defined by X_density/Y_density even when density_unit=0. */
  UINT8 density_unit;           /* JFIF code for pixel size units */
  UINT16 X_density;             /* Horizontal pixel density */
  UINT16 Y_density;             /* Vertical pixel density */
  boolean write_Adobe_marker;   /* should an Adobe marker be written? */

  /* State variable: index of next scanline to be written to
   * jpeg_write_scanlines().  Application may use this to control its
   * processing loop, e.g., "while (next_scanline < image_height)".
   */

  JDIMENSION next_scanline;     /* 0 .. image_height-1  */

  /* Remaining fields are known throughout compressor, but generally
   * should not be touched by a surrounding application.
   */

  /*
   * These fields are computed during compression startup
   */
  boolean progressive_mode;     /* TRUE if scan script uses progressive mode */
  int max_h_samp_factor;        /* largest h_samp_factor */
  int max_v_samp_factor;        /* largest v_samp_factor */


  JDIMENSION total_iMCU_rows;   /* # of iMCU rows to be input to coef ctlr */
  /* The coefficient controller receives data in units of MCU rows as defined
   * for fully interleaved scans (whether the JPEG file is interleaved or not).
   * There are v_samp_factor * DCTSIZE sample rows of each component in an
   * "iMCU" (interleaved MCU) row.
   */

  /*
   * These fields are valid during any one scan.
   * They describe the components and MCUs actually appearing in the scan.
   */
  int comps_in_scan;            /* # of JPEG components in this scan */
  jpeg_component_info *cur_comp_info[4];
  /* *cur_comp_info[i] describes component that appears i'th in SOS */

  JDIMENSION MCUs_per_row;      /* # of MCUs across the image */
  JDIMENSION MCU_rows_in_scan;  /* # of MCU rows in the image */

  int blocks_in_MCU;            /* # of DCT blocks per MCU */
  int MCU_membership[10];
  /* MCU_membership[i] is index in cur_comp_info of component owning */
  /* i'th block in an MCU */

  int Ss, Se, Ah, Al;           /* progressive JPEG parameters for scan */


  /*
   * Links to compression subobjects (methods and private variables of modules)
   */
  struct jpeg_comp_master *master;
  struct jpeg_c_main_controller *main;
  struct jpeg_c_prep_controller *prep;
  struct jpeg_c_coef_controller *coef;
  struct jpeg_marker_writer *marker;
  struct jpeg_color_converter *cconvert;
  struct jpeg_downsampler *downsample;
  struct jpeg_forward_dct *fdct;
  struct jpeg_entropy_encoder *entropy;
  jpeg_scan_info *script_space; /* workspace for jpeg_simple_progression */
  int script_space_size;
};


/* Master record for a decompression instance */

struct jpeg_decompress_struct {
  struct jpeg_error_mgr *err;      struct jpeg_memory_mgr *mem;     struct jpeg_progress_mgr *progress;    void *client_data;               boolean is_decompressor;         int global_state;           /* Fields shared with jpeg_compress_struct */

  /* Source of compressed data */
  struct jpeg_source_mgr *src;

  /* Basic description of image --- filled in by jpeg_read_header(). */
  /* Application may inspect these values to decide how to process image. */

  JDIMENSION image_width;       /* nominal image width (from SOF marker) */
  JDIMENSION image_height;      /* nominal image height */
  int num_components;           /* # of color components in JPEG image */
  J_COLOR_SPACE jpeg_color_space; /* colorspace of JPEG image */

  /* Decompression processing parameters --- these fields must be set before
   * calling jpeg_start_decompress().  Note that jpeg_read_header() initializes
   * them to default values.
   */

  J_COLOR_SPACE out_color_space; /* colorspace for output */

  unsigned int scale_num, scale_denom; /* fraction by which to scale image */

  double output_gamma;          /* image gamma wanted in output */

  boolean buffered_image;       /* TRUE=multiple output passes */
  boolean raw_data_out;         /* TRUE=downsampled data wanted */

  J_DCT_METHOD dct_method;      /* IDCT algorithm selector */
  boolean do_fancy_upsampling;  /* TRUE=apply fancy upsampling */
  boolean do_block_smoothing;   /* TRUE=apply interblock smoothing */

  boolean quantize_colors;      /* TRUE=colormapped output wanted */
  /* the following are ignored if not quantize_colors: */
  J_DITHER_MODE dither_mode;    /* type of color dithering to use */
  boolean two_pass_quantize;    /* TRUE=use two-pass color quantization */
  int desired_number_of_colors; /* max # colors to use in created colormap */
  /* these are significant only in buffered-image mode: */
  boolean enable_1pass_quant;   /* enable future use of 1-pass quantizer */
  boolean enable_external_quant;/* enable future use of external colormap */
  boolean enable_2pass_quant;   /* enable future use of 2-pass quantizer */

  /* Description of actual output image that will be returned to application.
   * These fields are computed by jpeg_start_decompress().
   * You can also use jpeg_calc_output_dimensions() to determine these values
   * in advance of calling jpeg_start_decompress().
   */

  JDIMENSION output_width;      /* scaled image width */
  JDIMENSION output_height;     /* scaled image height */
  int out_color_components;     /* # of color components in out_color_space */
  int output_components;        /* # of color components returned */
  /* output_components is 1 (a colormap index) when quantizing colors;
   * otherwise it equals out_color_components.
   */
  int rec_outbuf_height;        /* min recommended height of scanline buffer */
  /* If the buffer passed to jpeg_read_scanlines() is less than this many rows
   * high, space and time will be wasted due to unnecessary data copying.
   * Usually rec_outbuf_height will be 1 or 2, at most 4.
   */

  /* When quantizing colors, the output colormap is described by these fields.
   * The application can supply a colormap by setting colormap non-NULL before
   * calling jpeg_start_decompress; otherwise a colormap is created during
   * jpeg_start_decompress or jpeg_start_output.
   * The map has out_color_components rows and actual_number_of_colors columns.
   */
  int actual_number_of_colors;  /* number of entries in use */
  JSAMPARRAY colormap;          /* The color map as a 2-D pixel array */

  /* State variables: these variables indicate the progress of decompression.
   * The application may examine these but must not modify them.
   */

  /* Row index of next scanline to be read from jpeg_read_scanlines().
   * Application may use this to control its processing loop, e.g.,
   * "while (output_scanline < output_height)".
   */
  JDIMENSION output_scanline;   /* 0 .. output_height-1  */

  /* Current input scan number and number of iMCU rows completed in scan.
   * These indicate the progress of the decompressor input side.
   */
  int input_scan_number;        /* Number of SOS markers seen so far */
  JDIMENSION input_iMCU_row;    /* Number of iMCU rows completed */

  /* The "output scan number" is the notional scan being displayed by the
   * output side.  The decompressor will not allow output scan/row number
   * to get ahead of input scan/row, but it can fall arbitrarily far behind.
   */
  int output_scan_number;       /* Nominal scan number being displayed */
  JDIMENSION output_iMCU_row;   /* Number of iMCU rows read */

  /* Current progression status.  coef_bits[c][i] indicates the precision
   * with which component c's DCT coefficient i (in zigzag order) is known.
   * It is -1 when no data has yet been received, otherwise it is the point
   * transform (shift) value for the most recent scan of the coefficient
   * (thus, 0 at completion of the progression).
   * This pointer is NULL when reading a non-progressive file.
   */
  int (*coef_bits)[64];   /* -1 or current Al value for each coef */

  /* Internal JPEG parameters --- the application usually need not look at
   * these fields.  Note that the decompressor output side may not use
   * any parameters that can change between scans.
   */

  /* Quantization and Huffman tables are carried forward across input
   * datastreams when processing abbreviated JPEG datastreams.
   */

  JQUANT_TBL *quant_tbl_ptrs[4];
  /* ptrs to coefficient quantization tables, or NULL if not defined */

  JHUFF_TBL *dc_huff_tbl_ptrs[4];
  JHUFF_TBL *ac_huff_tbl_ptrs[4];
  /* ptrs to Huffman coding tables, or NULL if not defined */

  /* These parameters are never carried across datastreams, since they
   * are given in SOF/SOS markers or defined to be reset by SOI.
   */

  int data_precision;           /* bits of precision in image data */

  jpeg_component_info *comp_info;
  /* comp_info[i] describes component that appears i'th in SOF */

  boolean progressive_mode;     /* TRUE if SOFn specifies progressive mode */
  boolean arith_code;           /* TRUE=arithmetic coding, FALSE=Huffman */

  UINT8 arith_dc_L[16]; /* L values for DC arith-coding tables */
  UINT8 arith_dc_U[16]; /* U values for DC arith-coding tables */
  UINT8 arith_ac_K[16]; /* Kx values for AC arith-coding tables */

  unsigned int restart_interval; /* MCUs per restart interval, or 0 for no restart */

  /* These fields record data obtained from optional markers recognized by
   * the JPEG library.
   */
  boolean saw_JFIF_marker;      /* TRUE iff a JFIF APP0 marker was found */
  /* Data copied from JFIF marker; only valid if saw_JFIF_marker is TRUE: */
  UINT8 JFIF_major_version;     /* JFIF version number */
  UINT8 JFIF_minor_version;
  UINT8 density_unit;           /* JFIF code for pixel size units */
  UINT16 X_density;             /* Horizontal pixel density */
  UINT16 Y_density;             /* Vertical pixel density */
  boolean saw_Adobe_marker;     /* TRUE iff an Adobe APP14 marker was found */
  UINT8 Adobe_transform;        /* Color transform code from Adobe marker */

  boolean CCIR601_sampling;     /* TRUE=first samples are cosited */

  /* Aside from the specific data retained from APPn markers known to the
   * library, the uninterpreted contents of any or all APPn and COM markers
   * can be saved in a list for examination by the application.
   */
  jpeg_saved_marker_ptr marker_list; /* Head of list of saved markers */

  /* Remaining fields are known throughout decompressor, but generally
   * should not be touched by a surrounding application.
   */

  /*
   * These fields are computed during decompression startup
   */
  int max_h_samp_factor;        /* largest h_samp_factor */
  int max_v_samp_factor;        /* largest v_samp_factor */

  int min_DCT_scaled_size;      /* smallest DCT_scaled_size of any component */

  JDIMENSION total_iMCU_rows;   /* # of iMCU rows in image */
  /* The coefficient controller's input and output progress is measured in
   * units of "iMCU" (interleaved MCU) rows.  These are the same as MCU rows
   * in fully interleaved JPEG scans, but are used whether the scan is
   * interleaved or not.  We define an iMCU row as v_samp_factor DCT block
   * rows of each component.  Therefore, the IDCT output contains
   * v_samp_factor*DCT_[v_]scaled_size sample rows of a component per iMCU row.
   */

  JSAMPLE *sample_range_limit;  /* table for fast range-limiting */

  /*
   * These fields are valid during any one scan.
   * They describe the components and MCUs actually appearing in the scan.
   * Note that the decompressor output side must not use these fields.
   */
  int comps_in_scan;            /* # of JPEG components in this scan */
  jpeg_component_info *cur_comp_info[4];
  /* *cur_comp_info[i] describes component that appears i'th in SOS */

  JDIMENSION MCUs_per_row;      /* # of MCUs across the image */
  JDIMENSION MCU_rows_in_scan;  /* # of MCU rows in the image */

  int blocks_in_MCU;            /* # of DCT blocks per MCU */
  int MCU_membership[10];
  /* MCU_membership[i] is index in cur_comp_info of component owning */
  /* i'th block in an MCU */

  int Ss, Se, Ah, Al;           /* progressive JPEG parameters for scan */


  /* This field is shared between entropy decoder and marker parser.
   * It is either zero or the code of a JPEG marker that has been
   * read from the data source, but has not yet been processed.
   */
  int unread_marker;

  /*
   * Links to decompression subobjects (methods, private variables of modules)
   */
  struct jpeg_decomp_master *master;
  struct jpeg_d_main_controller *main;
  struct jpeg_d_coef_controller *coef;
  struct jpeg_d_post_controller *post;
  struct jpeg_input_controller *inputctl;
  struct jpeg_marker_reader *marker;
  struct jpeg_entropy_decoder *entropy;
  struct jpeg_inverse_dct *idct;
  struct jpeg_upsampler *upsample;
  struct jpeg_color_deconverter *cconvert;
  struct jpeg_color_quantizer *cquantize;
};


/* "Object" declarations for JPEG modules that may be supplied or called
 * directly by the surrounding application.
 * As with all objects in the JPEG library, these structs only define the
 * publicly visible methods and state variables of a module.  Additional
 * private fields may exist after the public ones.
 */


/* Error handler object */

struct jpeg_error_mgr {
  /* Error exit handler: does not return to caller */
  void (*error_exit) (j_common_ptr cinfo);
  /* Conditionally emit a trace or warning message */
  void (*emit_message) (j_common_ptr cinfo, int msg_level);
  /* Routine that actually outputs a trace or error message */
  void (*output_message) (j_common_ptr cinfo);
  /* Format a message string for the most recent JPEG error or message */
  void (*format_message) (j_common_ptr cinfo, char *buffer);
  /* Reset error state variables at start of a new image */
  void (*reset_error_mgr) (j_common_ptr cinfo);

  /* The message ID code and any parameters are saved here.
   * A message can have one string parameter or up to 8 int parameters.
   */
  int msg_code;
  union {
    int i[8];
    char s[80];
  } msg_parm;

  /* Standard state variables for error facility */

  int trace_level;              /* max msg_level that will be displayed */

  /* For recoverable corrupt-data errors, we emit a warning message,
   * but keep going unless emit_message chooses to abort.  emit_message
   * should count warnings in num_warnings.  The surrounding application
   * can check for bad data by seeing if num_warnings is nonzero at the
   * end of processing.
   */
  long num_warnings;            /* number of corrupt-data warnings */

  /* These fields point to the table(s) of error message strings.
   * An application can change the table pointer to switch to a different
   * message list (typically, to change the language in which errors are
   * reported).  Some applications may wish to add additional error codes
   * that will be handled by the JPEG library error mechanism; the second
   * table pointer is used for this purpose.
   *
   * First table includes all errors generated by JPEG library itself.
   * Error code 0 is reserved for a "no such error string" message.
   */
  const char * const *jpeg_message_table; /* Library errors */
  int last_jpeg_message;    /* Table contains strings 0..last_jpeg_message */
  /* Second table can be added by application (see cjpeg/djpeg for example).
   * It contains strings numbered first_addon_message..last_addon_message.
   */
  const char * const *addon_message_table; /* Non-library errors */
  int first_addon_message;      /* code for first string in addon table */
  int last_addon_message;       /* code for last string in addon table */
};


/* Progress monitor object */

struct jpeg_progress_mgr {
  void (*progress_monitor) (j_common_ptr cinfo);

  long pass_counter;            /* work units completed in this pass */
  long pass_limit;              /* total number of work units in this pass */
  int completed_passes;         /* passes completed so far */
  int total_passes;             /* total number of passes expected */
};


/* Data destination object for compression */

struct jpeg_destination_mgr {
  JOCTET *next_output_byte;     /* => next byte to write in buffer */
  size_t free_in_buffer;        /* # of byte spaces remaining in buffer */

  void (*init_destination) (j_compress_ptr cinfo);
  boolean (*empty_output_buffer) (j_compress_ptr cinfo);
  void (*term_destination) (j_compress_ptr cinfo);
};


/* Data source object for decompression */

struct jpeg_source_mgr {
  const JOCTET *next_input_byte; /* => next byte to read from buffer */
  size_t bytes_in_buffer;       /* # of bytes remaining in buffer */

  void (*init_source) (j_decompress_ptr cinfo);
  boolean (*fill_input_buffer) (j_decompress_ptr cinfo);
  void (*skip_input_data) (j_decompress_ptr cinfo, long num_bytes);
  boolean (*resync_to_restart) (j_decompress_ptr cinfo, int desired);
  void (*term_source) (j_decompress_ptr cinfo);
};


/* Memory manager object.
 * Allocates "small" objects (a few K total), "large" objects (tens of K),
 * and "really big" objects (virtual arrays with backing store if needed).
 * The memory manager does not allow individual objects to be freed; rather,
 * each created object is assigned to a pool, and whole pools can be freed
 * at once.  This is faster and more convenient than remembering exactly what
 * to free, especially where malloc()/free() are not too speedy.
 * NB: alloc routines never return NULL.  They exit to error_exit if not
 * successful.
 */


typedef struct jvirt_sarray_control *jvirt_sarray_ptr;
typedef struct jvirt_barray_control *jvirt_barray_ptr;


struct jpeg_memory_mgr {
  /* Method pointers */
  void *(*alloc_small) (j_common_ptr cinfo, int pool_id, size_t sizeofobject);
  void *(*alloc_large) (j_common_ptr cinfo, int pool_id,
                        size_t sizeofobject);
  JSAMPARRAY (*alloc_sarray) (j_common_ptr cinfo, int pool_id,
                              JDIMENSION samplesperrow, JDIMENSION numrows);
  JBLOCKARRAY (*alloc_barray) (j_common_ptr cinfo, int pool_id,
                               JDIMENSION blocksperrow, JDIMENSION numrows);
  jvirt_sarray_ptr (*request_virt_sarray) (j_common_ptr cinfo, int pool_id,
                                           boolean pre_zero,
                                           JDIMENSION samplesperrow,
                                           JDIMENSION numrows,
                                           JDIMENSION maxaccess);
  jvirt_barray_ptr (*request_virt_barray) (j_common_ptr cinfo, int pool_id,
                                           boolean pre_zero,
                                           JDIMENSION blocksperrow,
                                           JDIMENSION numrows,
                                           JDIMENSION maxaccess);
  void (*realize_virt_arrays) (j_common_ptr cinfo);
  JSAMPARRAY (*access_virt_sarray) (j_common_ptr cinfo, jvirt_sarray_ptr ptr,
                                    JDIMENSION start_row, JDIMENSION num_rows,
                                    boolean writable);
  JBLOCKARRAY (*access_virt_barray) (j_common_ptr cinfo, jvirt_barray_ptr ptr,
                                     JDIMENSION start_row, JDIMENSION num_rows,
                                     boolean writable);
  void (*free_pool) (j_common_ptr cinfo, int pool_id);
  void (*self_destruct) (j_common_ptr cinfo);

  /* Limit on memory allocation for this JPEG object.  (Note that this is
   * merely advisory, not a guaranteed maximum; it only affects the space
   * used for virtual-array buffers.)  May be changed by outer application
   * after creating the JPEG object.
   */
  long max_memory_to_use;

  /* Maximum allocation request accepted by alloc_large. */
  long max_alloc_chunk;
};


/* Routine signature for application-supplied marker processing methods.
 * Need not pass marker code since it is stored in cinfo->unread_marker.
 */
typedef boolean (*jpeg_marker_parser_method) (j_decompress_ptr cinfo);


/* Originally, this macro was used as a way of defining function prototypes
 * for both modern compilers as well as older compilers that did not support
 * prototype parameters.  libjpeg-turbo has never supported these older,
 * non-ANSI compilers, but the macro is still included because there is some
 * software out there that uses it.
 */



/* Default error-management setup */
extern struct jpeg_error_mgr * jpeg_std_error(struct jpeg_error_mgr *err);

/* Initialization of JPEG compression objects.
 * jpeg_create_compress() and jpeg_create_decompress() are the exported
 * names that applications should call.  These expand to calls on
 * jpeg_CreateCompress and jpeg_CreateDecompress with additional information
 * passed for version mismatch checking.
 * NB: you must set up the error-manager BEFORE calling jpeg_create_xxx.
 */
extern void jpeg_CreateCompress(j_compress_ptr cinfo, int version,
                                 size_t structsize);
extern void jpeg_CreateDecompress(j_decompress_ptr cinfo, int version,
                                   size_t structsize);
/* Destruction of JPEG compression objects */
extern void jpeg_destroy_compress(j_compress_ptr cinfo);
extern void jpeg_destroy_decompress(j_decompress_ptr cinfo);

/* Standard data source and destination managers: stdio streams. */
/* Caller is responsible for opening the file before and closing after. */
extern void jpeg_stdio_dest(j_compress_ptr cinfo, FILE *outfile);
extern void jpeg_stdio_src(j_decompress_ptr cinfo, FILE *infile);

/* Data source and destination managers: memory buffers. */
extern void jpeg_mem_dest(j_compress_ptr cinfo, unsigned char **outbuffer,
                           unsigned long *outsize);
extern void jpeg_mem_src(j_decompress_ptr cinfo,
                          const unsigned char *inbuffer, unsigned long insize);

/* Default parameter setup for compression */
extern void jpeg_set_defaults(j_compress_ptr cinfo);
/* Compression parameter setup aids */
extern void jpeg_set_colorspace(j_compress_ptr cinfo,
                                 J_COLOR_SPACE colorspace);
extern void jpeg_default_colorspace(j_compress_ptr cinfo);
extern void jpeg_set_quality(j_compress_ptr cinfo, int quality,
                              boolean force_baseline);
extern void jpeg_set_linear_quality(j_compress_ptr cinfo, int scale_factor,
                                     boolean force_baseline);
extern void jpeg_add_quant_table(j_compress_ptr cinfo, int which_tbl,
                                  const unsigned int *basic_table,
                                  int scale_factor, boolean force_baseline);
extern int jpeg_quality_scaling(int quality);
extern void jpeg_simple_progression(j_compress_ptr cinfo);
extern void jpeg_suppress_tables(j_compress_ptr cinfo, boolean suppress);
extern JQUANT_TBL * jpeg_alloc_quant_table(j_common_ptr cinfo);
extern JHUFF_TBL * jpeg_alloc_huff_table(j_common_ptr cinfo);

/* Main entry points for compression */
extern void jpeg_start_compress(j_compress_ptr cinfo,
                                 boolean write_all_tables);
extern JDIMENSION jpeg_write_scanlines(j_compress_ptr cinfo,
                                        JSAMPARRAY scanlines,
                                        JDIMENSION num_lines);
extern void jpeg_finish_compress(j_compress_ptr cinfo);


/* Replaces jpeg_write_scanlines when writing raw downsampled data. */
extern JDIMENSION jpeg_write_raw_data(j_compress_ptr cinfo, JSAMPIMAGE data,
                                       JDIMENSION num_lines);

/* Write a special marker.  See libjpeg.txt concerning safe usage. */
extern void jpeg_write_marker(j_compress_ptr cinfo, int marker,
                               const JOCTET *dataptr, unsigned int datalen);
/* Same, but piecemeal. */
extern void jpeg_write_m_header(j_compress_ptr cinfo, int marker,
                                 unsigned int datalen);
extern void jpeg_write_m_byte(j_compress_ptr cinfo, int val);

/* Alternate compression function: just write an abbreviated table file */
extern void jpeg_write_tables(j_compress_ptr cinfo);

/* Write ICC profile.  See libjpeg.txt for usage information. */
extern void jpeg_write_icc_profile(j_compress_ptr cinfo,
                                    const JOCTET *icc_data_ptr,
                                    unsigned int icc_data_len);


/* Decompression startup: read start of JPEG datastream to see what's there */
extern int jpeg_read_header(j_decompress_ptr cinfo, boolean require_image);
/* Return value is one of: */
/* If you pass require_image = TRUE (normal case), you need not check for
 * a TABLES_ONLY return code; an abbreviated file will cause an error exit.
 * JPEG_SUSPENDED is only possible if you use a data source module that can
 * give a suspension return (the stdio source module doesn't).
 */

/* Main entry points for decompression */
extern boolean jpeg_start_decompress(j_decompress_ptr cinfo);
extern JDIMENSION jpeg_read_scanlines(j_decompress_ptr cinfo,
                                       JSAMPARRAY scanlines,
                                       JDIMENSION max_lines);
extern JDIMENSION jpeg_skip_scanlines(j_decompress_ptr cinfo,
                                       JDIMENSION num_lines);
extern void jpeg_crop_scanline(j_decompress_ptr cinfo, JDIMENSION *xoffset,
                                JDIMENSION *width);
extern boolean jpeg_finish_decompress(j_decompress_ptr cinfo);

/* Replaces jpeg_read_scanlines when reading raw downsampled data. */
extern JDIMENSION jpeg_read_raw_data(j_decompress_ptr cinfo, JSAMPIMAGE data,
                                      JDIMENSION max_lines);

/* Additional entry points for buffered-image mode. */
extern boolean jpeg_has_multiple_scans(j_decompress_ptr cinfo);
extern boolean jpeg_start_output(j_decompress_ptr cinfo, int scan_number);
extern boolean jpeg_finish_output(j_decompress_ptr cinfo);
extern boolean jpeg_input_complete(j_decompress_ptr cinfo);
extern void jpeg_new_colormap(j_decompress_ptr cinfo);
extern int jpeg_consume_input(j_decompress_ptr cinfo);
/* Return value is one of: */
/* #define JPEG_SUSPENDED       0    Suspended due to lack of input data */

/* Precalculate output dimensions for current decompression parameters. */
extern void jpeg_calc_output_dimensions(j_decompress_ptr cinfo);

/* Control saving of COM and APPn markers into marker_list. */
extern void jpeg_save_markers(j_decompress_ptr cinfo, int marker_code,
                               unsigned int length_limit);

/* Install a special processing method for COM or APPn markers. */
extern void jpeg_set_marker_processor(j_decompress_ptr cinfo,
                                       int marker_code,
                                       jpeg_marker_parser_method routine);

/* Read or write raw DCT coefficients --- useful for lossless transcoding. */
extern jvirt_barray_ptr * jpeg_read_coefficients(j_decompress_ptr cinfo);
extern void jpeg_write_coefficients(j_compress_ptr cinfo,
                                     jvirt_barray_ptr *coef_arrays);
extern void jpeg_copy_critical_parameters(j_decompress_ptr srcinfo,
                                           j_compress_ptr dstinfo);

/* If you choose to abort compression or decompression before completing
 * jpeg_finish_(de)compress, then you need to clean up to release memory,
 * temporary files, etc.  You can just call jpeg_destroy_(de)compress
 * if you're done with the JPEG object, but if you want to clean it up and
 * reuse it, call this:
 */
extern void jpeg_abort_compress(j_compress_ptr cinfo);
extern void jpeg_abort_decompress(j_decompress_ptr cinfo);

/* Generic versions of jpeg_abort and jpeg_destroy that work on either
 * flavor of JPEG object.  These may be more convenient in some places.
 */
extern void jpeg_abort(j_common_ptr cinfo);
extern void jpeg_destroy(j_common_ptr cinfo);

/* Default restart-marker-resync procedure for use by data source modules */
extern boolean jpeg_resync_to_restart(j_decompress_ptr cinfo, int desired);

/* Read ICC profile.  See libjpeg.txt for usage information. */
extern boolean jpeg_read_icc_profile(j_decompress_ptr cinfo,
                                      JOCTET **icc_data_ptr,
                                      unsigned int *icc_data_len);


/* These marker codes are exported since applications and data source modules
 * are likely to want to use them.
 */



/* If we have a brain-damaged compiler that emits warnings (or worse, errors)
 * for structure definitions that are never filled in, keep it quiet by
 * supplying dummy definitions for the various substructures.
 */



/*
 * The JPEG library modules define JPEG_INTERNALS before including this file.
 * The internal structure declarations are read only when that is true.
 * Applications using the library should not include jpegint.h, but may wish
 * to include jerror.h.
 */



