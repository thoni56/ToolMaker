/*-----------------------------------------------------------------------------
 * pwPack - Parse table packer
 *		@(#)pwPack.c	1.2 (90/11/07 09:49:18)
 *-----------------------------------------------------------------------------
 * Created:	89-08-22 by Tom
 *			 From VAX/VMS Pascal V1.34, dated 1987-09-18
 * Modified:	90-11-06 by Yngve
 *			actTbl entry combination replaced with
 *			shifting and masking (divFactor refs deleted).
 *-----------------------------------------------------------------------------
 * Entries:								     
 *	pwPack - The entry point of the packer
 *-----------------------------------------------------------------------------
 *									     
 * Static structure							     
 * ----------------							     
 *									     
 *  pwPack		Entry point				     
 *	writeTables	    Output the packed tables		     
 *	    outputEntry		Output one parser entry		     
 *	writePackStats	    Output a summary of the packing process
 *-----------------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------------
 * Imports
 */
#include <stdio.h>
#include "pmk_i.h"
#include "pws.h"
#include "set.h"
#include "pack.h"
#include "pwGe.h"
#include "pwsGrm.h"
#include "pwPack.h"
#include "pwLog.h"

PackItem act, gto;		/* The parser tables */

Boolean actGCS, actLES, actRDS, gtoGCS, gtoLES, gtoRDS;


/*-----------------------------------------------------------------------------
 * pwPack - Parse table packing
 *-----------------------------------------------------------------------------
 * The following packings are carried out in the pack module:
 *
 * ACTION table								     
 * - Row and column merging			(OPTIMIZE(MERGE,TMERGE)) 
 * - Row and column splitting (Bell)		(OPTIMIZE(SPLIT,TSPLIT))
 * - Row Displacement 				(OPTIMIZE(ROW,TROW))
 * - Row and column merging of the error matrix	(OPTIMIZE(ERROR))
 *
 * GOTO table
 * - Row and column merging			(OPTIMIZE(MERGE,NTMERGE))
 * - Row and column splitting (Bell)		(OPTIMIZE(SPLIT,NTSPLIT))
 * - Row Displacement				(OPTIMIZE(ROW,NTROW))    
 *
 * Merging is performed by using a colouring algorithm, and Row Displacement
 * is performed using the First Fit Decreasing heuristic.
 *-----------------------------------------------------------------------------
 */
void pwPack()
{
  int actSet = getSetOpt(ACTIONPACK_OPT);
  int gotoSet = getSetOpt(GOTOPACK_OPT);

    actRDS = (actSet>>2 & 1);
    actGCS = (actSet>>3 & 1);
    actLES = (actSet>>4 & 1);
    gtoRDS = (gotoSet>>2 & 1);
    gtoGCS = (gotoSet>>3 & 1);
    gtoLES = (gotoSet>>4 & 1);

    act.type = 0;
    act.insign = error; /* Error value */
    act.rows = actRowCnt;
    act.cols = actColCnt;
    act.matrix = actTbl;

    gto.type = 0;
    gto.insign = error; /* Error value */
    gto.rows = gtoRowCnt;
    gto.cols = gtoColCnt;
    gto.matrix = gtoTbl;

    if (actGCS || actLES || actRDS) {
	/* Action table
	 */
	if (actGCS) act.type = ePackGCS;
	if (actLES) act.type |= ePackLES;
	if (actRDS) act.type |= ePackRDS;
	if (getSetOpt(ACTIONPACK_OPT)>>5 & 1) 
	  act.type |= ePackERR;

	if (packMatrix(&act)) {
	    /* Packing error
	     */
	}/*if*/
    }/*if*/

    if (gtoGCS || gtoLES || gtoRDS) {
	/* Goto table
	 */
	if (gtoGCS) gto.type = ePackGCS;
	if (gtoLES) gto.type |= ePackLES;
	if (gtoRDS) gto.type |= ePackRDS;

	if (packMatrix(&gto)) {
	    /* Packing error
	     */
	}/*if*/
    }/*if*/

    if (actGCS || gtoGCS || actLES || gtoLES || actRDS || gtoRDS) {
	logPackedTables();
	logPackStats();
    }/*if*/
}/*pwPack()*/
