#ifndef _pwsQueue
#define _pwsQueue

#include "pws.h"
#include "pwsGrm.h"

typedef struct qEl {
    prod_elnode *nontNode;
    analysis_kind analysisInfo;
    struct qEl *next;
} qEl;

extern void init_queue();
extern Boolean empty_queue();
extern void front();
extern void enqueue();

#endif
