#ifndef RPLY_FILE_H
#define RPLY_FILE_H
/* ----------------------------------------------------------------------
 * RPly library, read/write PLY files
 * Diego Nehab, IMPA
 * http://www.impa.br/~diego/software/rply
 *
 * This library is distributed under the MIT License. See notice
 * at the end of this file.
 * ---------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

	/* ----------------------------------------------------------------------
	 * Opens a PLY file for reading (fails if file is not a PLY file)
	 *
	 * file_pointer: FILE * to file open for reading
	 * error_cb: error callback function
	 * idata,pdata: contextual information available to users
	 *
	 * Returns 1 if successful, 0 otherwise
	 * ---------------------------------------------------------------------- */
	p_ply ply_open_from_file(FILE *file_pointer, p_ply_error_cb error_cb,
		long idata, void *pdata);

	/* ----------------------------------------------------------------------
	 * Creates new PLY file
	 *
	 * file_pointer: FILE * to a file open for writing
	 * storage_mode: file format mode
	 * error_cb: error callback function
	 * idata,pdata: contextual information available to users
	 *
	 * Returns handle to PLY file if successfull, NULL otherwise
	 * ---------------------------------------------------------------------- */
	p_ply ply_create_to_file(FILE *file_pointer, e_ply_storage_mode storage_mode,
		p_ply_error_cb error_cb, long idata, void *pdata);

#ifdef __cplusplus
}
#endif

#endif /* RPLY_FILE_H */
