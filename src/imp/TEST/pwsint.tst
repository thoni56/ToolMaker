/* -------------------------- PWSINT --------------------------------------- */
/*									     */
/* File: PWSINT.SKL		- Interface file 		1987-05-05   */
/*									     */
/*	Host   :  Dec-Pascal/VMS					     */
/*	Target :  Dec-C/VMS						     */
/* ------------------------------------------------------------------------- */

%%BEGIN(idata)

	/* Parser definitions */

#define PWSTKMX	   32		/* Stack length      */
#define	PWLAMX	   5		/* Look-ahead length */
#define	PWSCOST    5		/* SHifting cost     */


%%BEGIN(notincl)
Denna text skall ej inkluderas i parsern!
%%END(foonotincl)
	/* Scanner interface */
	/* ----------------- */

#include "swscan.h"

typedef SWSYMDF PWSYMDF;

extern PWSYMDF token;

	/* Semantic attribute interface */
	/* ---------------------------- */

#include <stdio.h>
#include "macro.h"

typedef struct {		/* Semantic attribute definitions  */
	SWSRCP srcp;		/* Source position propagated from terminals.*/
	SWSTR sval;		/* String propagated from terminals. */
	boolean flag;		/* Multi purpose flag. */
	char *ref;		/* Multi purpose pointer. */
	 } PWSEMDF;


%%END(fooidata)
%%BEGIN(icode)

#define pwscan(token) swscan(token)

extern pwrpoi();		/* Error recovery - restart point  */
extern pwisym();		/* Error recovery - insert symbol  */
extern pwdsym();		/* Error recovery - delete symbol  */
extern pwmess();		/* Error recovery - error message  */
%%END(icode)
