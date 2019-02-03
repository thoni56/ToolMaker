/*
 * AUTHOR: Tony Olsson
 * DATE: 1993-06-10/tony@eeyore
 * CREATED: 1990-06-06
 *
 * SoftLab ab (c) 1990
 *

 * License handler. The license server must be running. A call to
 * license() reads the $TMHOME/.license.$HOSTID or $TMHOME/.license
 * license file to determine if a license can be aquired or not.
 */

typedef enum {
  LICENSE_OK,			/* License ok */
  LICENSE_EXPIRED,		/* The license date has expired */
  LICENSE_DENIED,		/* License denied (to many user or wrong host) */
  LICENSE_FORMAT_ERROR,		/* Format error in license file */
  LICENSE_NO_SERVER,		/* No server available */
  LICENSE_NO_FILE,		/* No license file */
  LICENSE_ILLEGAL_PASSWORD,	/* Illeagal password in license file */
  LICENSE_INITIALIZATION_FAILURE /* The license server has not been correctly initialized */
  } License;

extern License license();

