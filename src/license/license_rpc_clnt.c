/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <rpc/rpc.h>
#include "license_rpc.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

int *
license_1(argp, clnt)
	char **argp;
	CLIENT *clnt;
{
	static int res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, LICENSE, xdr_wrapstring, argp, xdr_int, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}
