#include <stdio.h>
#include <stdlib.h>
#include "pmkList.h"
#include "pwsQueue.h"
#include "pwsGrm.h"

static qEl *qFront = NULL;
static qEl *qRear = NULL;


/*-----------------------------------------------------------------------------
 * init_queue - Initializes queue
 *-----------------------------------------------------------------------------
 */
void init_queue()
{
    while (qFront) {
	qRear = qFront;
	qFront = qFront->next;
	free((char *)qFront);
    }/*while*/
    qFront = NULL;
    qRear = NULL;
}/*init_queue()*/


/*-----------------------------------------------------------------------------
 * empty_queue - tests whether queue is empty or not
 *-----------------------------------------------------------------------------
 */
Boolean empty_queue()
{
    return (qFront == NULL);
}/*empty_queue()*/


/*-----------------------------------------------------------------------------
 * front - returns contents of front element in its arguments and dequeues
 *	   front element
 *-----------------------------------------------------------------------------
 */
void front(nont, analysis)
prod_elnode **nont;
analysis_kind *analysis;
{
    if (empty_queue()) pmkLog(NULL, 215, sevSYS, "");
    else {
	*nont = qFront->nontNode;
	*analysis = qFront->analysisInfo;
	qFront = qFront->next;
    }/*if*/
}/*front()*/


/*-----------------------------------------------------------------------------
 * enqueue - enqueues it's arguments in a queue element at the end of the queue
 *-----------------------------------------------------------------------------
 */
void enqueue(nont, analysis)
prod_elnode *nont;
analysis_kind analysis;
{
    qEl *temp;

    temp = (qEl *)malloc(sizeof(qEl));
    temp->nontNode = nont;
    temp->analysisInfo = analysis;
    temp->next = NULL;
    if (qFront) {
	qRear->next = temp;
	qRear = temp;
    } else {
	qFront = temp;
	qRear = temp;
    }/*if*/
}/*enqueue()*/
