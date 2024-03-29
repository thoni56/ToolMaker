/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <stdio.h>
#include <rpc/rpc.h>
#include "license_rpc.h"

static void licenseprog_1();

int main(argc,argv) int argc;char **argv;
{
    register SVCXPRT *transp;

    (void) pmap_unset(LICENSEPROG, LICENSEVERS);

    transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL) {
        fprintf(stderr, "cannot create udp service.");
        exit(1);
    }
    if (!svc_register(transp, LICENSEPROG, LICENSEVERS, licenseprog_1, IPPROTO_UDP)) {
        fprintf(stderr, "unable to register (LICENSEPROG, LICENSEVERS, udp).");
        exit(1);
    }

    transp = svctcp_create(RPC_ANYSOCK, 0, 0);
    if (transp == NULL) {
        fprintf(stderr, "cannot create tcp service.");
        exit(1);
    }
    if (!svc_register(transp, LICENSEPROG, LICENSEVERS, licenseprog_1, IPPROTO_TCP)) {
        fprintf(stderr, "unable to register (LICENSEPROG, LICENSEVERS, tcp).");
        exit(1);
    }

    licenseInit(argc,argv);licenseDelay();svc_run();
    fprintf(stderr, "svc_run returned");
    exit(1);
    /* NOTREACHED */
}

static void
licenseprog_1(rqstp, transp)
    struct svc_req *rqstp;
    register SVCXPRT *transp;
{
    union {
        char *license_1_arg;
    } argument;
    char *result;
    bool_t (*xdr_argument)(), (*xdr_result)();
    char *(*local)();

    switch (rqstp->rq_proc) {
    case NULLPROC:
        (void) svc_sendreply(transp, xdr_void, (char *)NULL);
        return;

    case LICENSE:
        xdr_argument = xdr_wrapstring;
        xdr_result = xdr_int;
        local = (char *(*)()) license_1;
        break;

    default:
        svcerr_noproc(transp);
        return;
    }
    bzero((char *)&argument, sizeof(argument));
    if (!svc_getargs(transp, xdr_argument, &argument)) {
        svcerr_decode(transp);
        return;
    }
    result = (*local)(&argument, rqstp);
    if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
        svcerr_systemerr(transp);
    }
    if (!svc_freeargs(transp, xdr_argument, &argument)) {
        fprintf(stderr, "unable to free arguments");
        exit(1);
    }
    return;
}
