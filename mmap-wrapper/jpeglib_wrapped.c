#include "jpeglib_wrapped.h"
#include "jpegint.h"
    struct jpeg_error_mgr * jpeg_std_error_wrapped(uint64_t id, struct jpeg_error_mgr * err_client, struct jpeg_error_mgr * err_library) {
        //Saved information here:
        struct jpeg_error_mgr *check = err_library;
        enable_lib(id);

        struct jpeg_error_mgr * ret = jpeg_std_error(err_library);
        disable_lib(id);
        //Sanitize data here:
        assert(err_library == check);
        assert(err_client->trace_level == 0);
        assert(err_client->addon_message_table == NULL);

        return ret;
    }
void jpeg_CreateCompress_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, int version, size_t structsize) {
	//Saved information here:
    struct jpeg_error_mgr *err = cinfo_client->err;
    void *client_data = cinfo_client->client_data;

	enable_lib(id);

	jpeg_CreateCompress(cinfo_library, version, structsize);
	disable_lib(id);
	//Sanitize data here:
    assert(!cinfo_client->is_decompressor);
    assert(cinfo_client->global_state == CSTATE_START);
    assert(cinfo_client->err == err);
    assert(cinfo_client->client_data == client_data);

}
void jpeg_CreateDecompress_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, int version, size_t structsize) {
	//Saved information here:

    struct jpeg_error_mgr *err = cinfo_client->err;
    void *client_data = cinfo_client->client_data;

	enable_lib(id);

	jpeg_CreateDecompress(cinfo_library, version, structsize);
	disable_lib(id);
	//Sanitize data here:
    assert(cinfo_client->is_decompressor);
    assert(cinfo_client->global_state == DSTATE_START);
    assert(cinfo_client->err == err);
    assert(cinfo_client->client_data == client_data);

}
void jpeg_destroy_compress_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_destroy_compress(cinfo_library);
	disable_lib(id);
	//Sanitize data here:
    assert(cinfo_client->mem == NULL);
    assert(cinfo_client->global_state == 0);

}
void jpeg_destroy_decompress_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_destroy_decompress(cinfo_library);
	disable_lib(id);
	//Sanitize data here:
    assert(cinfo_client->mem == NULL);
    assert(cinfo_client->global_state == 0);

}
void jpeg_stdio_dest_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, FILE * outfile_client, FILE * outfile_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_stdio_dest(cinfo_library, outfile_library);
	disable_lib(id);
	//Sanitize data here:
    assert(cinfo_client->dest != NULL);

}
void jpeg_stdio_src_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, FILE * infile_client, FILE * infile_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_stdio_src(cinfo_library, infile_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_mem_dest_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, unsigned char * * outbuffer_client, unsigned char * * outbuffer_library, unsigned long * outsize_client, unsigned long * outsize_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_mem_dest(cinfo_library, outbuffer_library, outsize_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_mem_src_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, const unsigned char * inbuffer_client, const unsigned char * inbuffer_library, unsigned long insize) {
	//Saved information here:

	enable_lib(id);

	jpeg_mem_src(cinfo_library, inbuffer_library, insize);
	disable_lib(id);

    struct jpeg_source_mgr *src = (struct jpeg_source_mgr *)lib_to_client(id, cinfo_client->src);
	//Sanitize data here:
    assert(src->bytes_in_buffer == (size_t)insize);
    assert(src->next_input_byte == (const JOCTET *)inbuffer_library);

}
void jpeg_set_defaults_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_set_defaults(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_set_colorspace_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, J_COLOR_SPACE colorspace) {
	//Saved information here:

	enable_lib(id);

	jpeg_set_colorspace(cinfo_library, colorspace);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_default_colorspace_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_default_colorspace(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_set_quality_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, int quality, boolean force_baseline) {
	//Saved information here:

	enable_lib(id);

	jpeg_set_quality(cinfo_library, quality, force_baseline);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_set_linear_quality_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, int scale_factor, boolean force_baseline) {
	//Saved information here:

	enable_lib(id);

	jpeg_set_linear_quality(cinfo_library, scale_factor, force_baseline);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_add_quant_table_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, int which_tbl, const unsigned int * basic_table_client, const unsigned int * basic_table_library, int scale_factor, boolean force_baseline) {
	//Saved information here:

	enable_lib(id);

	jpeg_add_quant_table(cinfo_library, which_tbl, basic_table_library, scale_factor, force_baseline);
	disable_lib(id);
	//Sanitize data here:

}
int jpeg_quality_scaling_wrapped(uint64_t id, int quality) {
	//Saved information here:

	enable_lib(id);

	int ret = jpeg_quality_scaling(quality);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
void jpeg_simple_progression_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_simple_progression(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_suppress_tables_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, boolean suppress) {
	//Saved information here:

	enable_lib(id);

	jpeg_suppress_tables(cinfo_library, suppress);
	disable_lib(id);
	//Sanitize data here:

}
JQUANT_TBL * jpeg_alloc_quant_table_wrapped(uint64_t id, j_common_ptr cinfo_client, j_common_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	JQUANT_TBL * ret = jpeg_alloc_quant_table(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
JHUFF_TBL * jpeg_alloc_huff_table_wrapped(uint64_t id, j_common_ptr cinfo_client, j_common_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	JHUFF_TBL * ret = jpeg_alloc_huff_table(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
void jpeg_start_compress_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, boolean write_all_tables) {
	//Saved information here:

	enable_lib(id);

	jpeg_start_compress(cinfo_library, write_all_tables);
	disable_lib(id);
	//Sanitize data here:

}
JDIMENSION jpeg_write_scanlines_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, JSAMPARRAY scanlines_client, JSAMPARRAY scanlines_library, JDIMENSION num_lines) {
	//Saved information here:

	enable_lib(id);

	JDIMENSION ret = jpeg_write_scanlines(cinfo_library, scanlines_library, num_lines);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
void jpeg_finish_compress_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_finish_compress(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
JDIMENSION jpeg_write_raw_data_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, JSAMPIMAGE data_client, JSAMPIMAGE data_library, JDIMENSION num_lines) {
	//Saved information here:

	enable_lib(id);

	JDIMENSION ret = jpeg_write_raw_data(cinfo_library, data_library, num_lines);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
void jpeg_write_marker_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, int marker, const JOCTET * dataptr_client, const JOCTET * dataptr_library, unsigned int datalen) {
	//Saved information here:

	enable_lib(id);

	jpeg_write_marker(cinfo_library, marker, dataptr_library, datalen);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_write_m_header_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, int marker, unsigned int datalen) {
	//Saved information here:

	enable_lib(id);

	jpeg_write_m_header(cinfo_library, marker, datalen);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_write_m_byte_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, int val) {
	//Saved information here:

	enable_lib(id);

	jpeg_write_m_byte(cinfo_library, val);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_write_tables_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_write_tables(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_write_icc_profile_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, const JOCTET * icc_data_ptr_client, const JOCTET * icc_data_ptr_library, unsigned int icc_data_len) {
	//Saved information here:

	enable_lib(id);

	jpeg_write_icc_profile(cinfo_library, icc_data_ptr_library, icc_data_len);
	disable_lib(id);
	//Sanitize data here:

}
int jpeg_read_header_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, boolean require_image) {
	//Saved information here:

	enable_lib(id);

	int ret = jpeg_read_header(cinfo_library, require_image);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
boolean jpeg_start_decompress_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	boolean ret = jpeg_start_decompress(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
JDIMENSION jpeg_read_scanlines_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, JSAMPARRAY scanlines_client, JSAMPARRAY scanlines_library, JDIMENSION max_lines) {
	//Saved information here:

	enable_lib(id);

	JDIMENSION ret = jpeg_read_scanlines(cinfo_library, scanlines_library, max_lines);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
JDIMENSION jpeg_skip_scanlines_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, JDIMENSION num_lines) {
	//Saved information here:

	enable_lib(id);

	JDIMENSION ret = jpeg_skip_scanlines(cinfo_library, num_lines);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
void jpeg_crop_scanline_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, JDIMENSION * xoffset_client, JDIMENSION * xoffset_library, JDIMENSION * width_client, JDIMENSION * width_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_crop_scanline(cinfo_library, xoffset_library, width_library);
	disable_lib(id);
	//Sanitize data here:

}
boolean jpeg_finish_decompress_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	boolean ret = jpeg_finish_decompress(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
JDIMENSION jpeg_read_raw_data_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, JSAMPIMAGE data_client, JSAMPIMAGE data_library, JDIMENSION max_lines) {
	//Saved information here:

	enable_lib(id);

	JDIMENSION ret = jpeg_read_raw_data(cinfo_library, data_library, max_lines);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
boolean jpeg_has_multiple_scans_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	boolean ret = jpeg_has_multiple_scans(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
boolean jpeg_start_output_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, int scan_number) {
	//Saved information here:

	enable_lib(id);

	boolean ret = jpeg_start_output(cinfo_library, scan_number);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
boolean jpeg_finish_output_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	boolean ret = jpeg_finish_output(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
boolean jpeg_input_complete_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	boolean ret = jpeg_input_complete(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
void jpeg_new_colormap_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_new_colormap(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
int jpeg_consume_input_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	int ret = jpeg_consume_input(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
void jpeg_calc_output_dimensions_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_calc_output_dimensions(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_save_markers_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, int marker_code, unsigned int length_limit) {
	//Saved information here:

	enable_lib(id);

	jpeg_save_markers(cinfo_library, marker_code, length_limit);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_set_marker_processor_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, int marker_code, jpeg_marker_parser_method routine) {
	//Saved information here:

	enable_lib(id);

	jpeg_set_marker_processor(cinfo_library, marker_code, routine);
	disable_lib(id);
	//Sanitize data here:

}
jvirt_barray_ptr * jpeg_read_coefficients_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jvirt_barray_ptr * ret = jpeg_read_coefficients(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
void jpeg_write_coefficients_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library, jvirt_barray_ptr * coef_arrays_client, jvirt_barray_ptr * coef_arrays_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_write_coefficients(cinfo_library, coef_arrays_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_copy_critical_parameters_wrapped(uint64_t id, j_decompress_ptr srcinfo_client, j_decompress_ptr srcinfo_library, j_compress_ptr dstinfo_client, j_compress_ptr dstinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_copy_critical_parameters(srcinfo_library, dstinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_abort_compress_wrapped(uint64_t id, j_compress_ptr cinfo_client, j_compress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_abort_compress(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_abort_decompress_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_abort_decompress(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_abort_wrapped(uint64_t id, j_common_ptr cinfo_client, j_common_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_abort(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
void jpeg_destroy_wrapped(uint64_t id, j_common_ptr cinfo_client, j_common_ptr cinfo_library) {
	//Saved information here:

	enable_lib(id);

	jpeg_destroy(cinfo_library);
	disable_lib(id);
	//Sanitize data here:

}
boolean jpeg_resync_to_restart_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, int desired) {
	//Saved information here:

	enable_lib(id);

	boolean ret = jpeg_resync_to_restart(cinfo_library, desired);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
boolean jpeg_read_icc_profile_wrapped(uint64_t id, j_decompress_ptr cinfo_client, j_decompress_ptr cinfo_library, JOCTET * * icc_data_ptr_client, JOCTET * * icc_data_ptr_library, unsigned int * icc_data_len_client, unsigned int * icc_data_len_library) {
	//Saved information here:

	enable_lib(id);

	boolean ret = jpeg_read_icc_profile(cinfo_library, icc_data_ptr_library, icc_data_len_library);
	disable_lib(id);
	//Sanitize data here:

	return ret;
}
