#ifdef DEBUG

#include <stdio.h>
#include "pwGe.h"
#include "pwDbg.h"
#include "pwsGrm.h"

void dbgPrintProd(prod)
prod_rec *prod;			/* IN production to print */
{
    int i;

    fprintf(pwsLog, "%s = ",
	    vocabulary[global_pvec_tbl[prod->start]]->name);
    for (i = 1; i <= prod->rssz; i++) {
	fprintf(pwsLog, "%s ",
		vocabulary[global_pvec_tbl[prod->start + i]]->name);
    }/*for*/
    fprintf(pwsLog, "\n\n");
}/*dbgPrintProd()*/

#endif
