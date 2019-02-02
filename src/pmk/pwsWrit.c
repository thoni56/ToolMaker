#include <stdio.h>
#include "pwsGrm.h"
#include "pwsOrd.h"
#include "pwSymSet.h"
#include "pwGe.h"

/*------------------------print_sym_set----------------------------*/
/*						                   */
/* print_sym_set - writes symbols in a sym_set.                    */
/*						                   */
/*-----------------------------------------------------------------*/

void print_sym_set(s)
SymSet s;
{
    int i, nr;

    nr = 0;
    for(i = 0; i <= vocCnt; i++) {
	if (SetMem(s->ss, i)) {
	    if (nr > 0) fprintf(pwsLog, ", ");
	    fprintf(pwsLog, "%s", vocabulary[i]->name);
	    nr++;
	}/*if*/
    }/*for*/
}/*print_sym_set()*/

/*------------------------write_prod-------------------------------*/
/*						                   */
/* write_prod - writes original production by traversing syntax    */
/*              tree recursively (unformatted). write_orig_prod    */
/*              calls this function.                               */
/*						                   */
/*-----------------------------------------------------------------*/


void write_prod(prodnr,lhs,rhs,top,with_modif)
int prodnr;
prod_elnode * lhs;   /* production's lhs          */
prod_elnode * rhs;   /* production's rhs          */
Boolean top;         /* write lhs (call from top) */
Boolean with_modif;  /* write modifiers           */
{
  prod_elnode *  curr_rhs = rhs;
  altr_lst * curr_altr;
  long i;
  if (!top) {
    fprintf(pwsLog, "%u: ", prodnr);
    if (newsym == NULL)  /* Symbol references are not updated in tree nodes */
                         /* after ordering grammar (See pwsOrd.c). */
      fprintf(pwsLog, "%s = ",
	      vocabulary[lhs->node_info.sym_node.sym_ind]->name);
    else
      fprintf(pwsLog, "%s = ",
	      vocabulary[newsym[lhs->node_info.sym_node.sym_ind]]->name);
  }
  do {
    switch(curr_rhs->node_kind) {

    case null_node_kind:
      fprintf(pwsLog, " Null ");
      break;

    case sym_node_kind:
      if (curr_rhs->node_info.sym_node.newnont)
	switch(curr_rhs->node_info.sym_node.rplc_info) {

	case altrs_rplc:
	  curr_altr = curr_rhs->node_info.sym_node.altrs_seq;
	  fprintf(pwsLog, "(");
	  while (curr_altr != NULL){
	    write_prod(prodnr, lhs,curr_altr->altr,TRUE);
	    curr_altr = curr_altr->nxtalt;
	    if (curr_altr != NULL)
	      fprintf(pwsLog, "|");
	  }
	  fprintf(pwsLog, ")");
	  break;

        case rept_rplc:
	  fprintf(pwsLog, "{");
	  write_prod(prodnr,lhs,curr_rhs->node_info.sym_node.rplc_seq,TRUE,with_modif);
	  fprintf(pwsLog, "}");
	  break;

	case act_rplc:
	  write_prod(prodnr,lhs,curr_rhs->node_info.sym_node.rplc_seq,TRUE,with_modif);
	  break;
	}
      else
	if (newsym == NULL)
	  fprintf(pwsLog, " %s ",vocabulary[curr_rhs->node_info.sym_node.sym_ind]->name);
        else
	  fprintf(pwsLog, " %s ",vocabulary[newsym[curr_rhs->node_info.sym_node.sym_ind]]->name);
      break;

    case mod_node_kind:
      if (with_modif) {
	fprintf(pwsLog, "\n");
	if (curr_rhs->node_info.modify_node->red != NULL){
	  fprintf(pwsLog, "+Reduce (");
	  print_sym_set(curr_rhs->node_info.modify_node->red);
	  fprintf(pwsLog, ")");
	  fprintf(pwsLog, "\n");
	}
	if (curr_rhs->node_info.modify_node->nored != NULL){
	  fprintf(pwsLog, "-Reduce (");
	  print_sym_set(curr_rhs->node_info.modify_node->nored);
	  fprintf(pwsLog, ")");
	  fprintf(pwsLog, "\n");
	}
      }
      break;

    case act_node_kind:
      /* Semantic action numbers are not used any more/ThoNi
	 fprintf(pwsLog, "%%%% %i %%%%",curr_rhs->node_info.act_node.ass_actno);
	 */
      break;
    }
    curr_rhs = curr_rhs->nxtnode;
  }
  while(curr_rhs != NULL);
  if (!top)
    fprintf(pwsLog, "\n");
}
/*------------------------write_derived_prods----------------------*/
/*						                   */
/* wirte_derived_prods - writes productions derived from           */
/*                       orig_prod_nr (unformatted).               */
/*						                   */
/*-----------------------------------------------------------------*/

void write_derived_prods(orig_prod_nr,with_acts,with_attref,with_modif,verified_attref)
int orig_prod_nr;       /* Original production number  */
Boolean with_acts;         /* write actions               */
Boolean with_attref;       /* write vocabulary symbols    */
                           /* in attribute references     */
Boolean with_modif;        /* write modifiers             */
Boolean verified_attref;   /* write vocabulary symbols    */
                           /* in attribute references     */
                           /* after verification          */
{
  int i,j,k,l;
  for(i=0;i<=global_prod_cnt;i++) {
    if (global_prod_tbl[i]->orig_prod == orig_prod_nr) {
      fprintf(pwsLog, "%u: %s",i, vocabulary[global_pvec_tbl[global_prod_tbl[i]->start]]->name);
      fprintf(pwsLog, " =");
      k = global_prod_tbl[i]->start + global_prod_tbl[i]->rssz;
      for(j=global_prod_tbl[i]->start+1; j<=k; j++) 
	fprintf(pwsLog, " %s ",vocabulary[global_pvec_tbl[j]]->name);
      fprintf(pwsLog, ";");
      if (with_acts)
	if (global_prod_tbl[i]->actno != -1) {
	  fprintf(pwsLog, " %%%% %i %%%%",global_prod_tbl[i]->actno);
	  if (with_attref)
	    if (attref_cnt > 0 || global_attref_cnt > 0) {
	      fprintf(pwsLog, " ##");
	      if (verified_attref) {
		/* if attribute references are not verified global_attref_sto is NULL */
		/* (see pwsOrd.c).                                                    */
		if (global_attref_sto != NULL) 
		  for(l=0;l<=global_attref_cnt;l++)
		    if (global_attref_sto[l].ruleno == i)
		      fprintf(pwsLog, " %s",vocabulary[global_attref_sto[l].sym]->name);
	      } else {
		for(l=0;l<=attref_cnt;l++)
		  if (attref_storage[l]->ruleno == i)
		    fprintf(pwsLog, " %s",vocabulary[attref_storage[l]->voc_sym]->name);
	      }
	    }
	}
      if (with_modif)
	if (global_prod_tbl[i]->modify != NULL) {
	  if (global_prod_tbl[i]->modify->red != NULL){
	    fprintf(pwsLog, " %%+");
	    print_sym_set(global_prod_tbl[i]->modify->red);
	  }
	  if (global_prod_tbl[i]->modify->nored != NULL){
	    fprintf(pwsLog, " %%-");
	    print_sym_set(global_prod_tbl[i]->modify->nored);
	  }
	}
      fprintf(pwsLog, "\n");
    }
  }
  fprintf(pwsLog, "\n\n");
}

/*------------------------write_orig_prod--------------------------*/
/*						                   */
/* write_orig_prod - writes original production prod_nr by calling */
/*                   write_prod.                                   */
/*						                   */
/*-----------------------------------------------------------------*/

void write_orig_prod(prod_nr,with_modif)
int prod_nr;      /* original production number */
Boolean with_modif;  /* write modifiers            */
{
  if (prod_nr <=  orig_prod_cnt) 
    write_prod(prod_nr, orig_prod_tbl[prod_nr],orig_prod_tbl[prod_nr]->nxtnode,FALSE,with_modif);
  else
    fprintf(pwsLog, "Production nr is greater than prod cnt. function: 'write_orig_prod'\n");
}

/* test routine -  writes all productions according to */
/*                 original productions order.         */

void write_only_derived()
{
  int i;
  fprintf(pwsLog, "   Productions:\n\n");
  for(i=0;i<=orig_prod_cnt;i++)
    write_derived_prods(i,TRUE,TRUE,TRUE,TRUE,TRUE);
}


