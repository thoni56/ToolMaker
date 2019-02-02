/*-----------------------------------------------------------------------------
 * timing - Routines for timing
 *-----------------------------------------------------------------------------
 * Created:	89-10-30 by Tom.
 * Modified:	No.
 *-----------------------------------------------------------------------------
 * Entries:								     
 *	tiStart
 *	tiStop
 *	tiPrint
 *	tiC
 *-----------------------------------------------------------------------------
 */

#include <stdio.h>
#include "timing.h"


/*-----------------------------------------------------------------------------
 * tiStart - Start a phase timing.
 *-----------------------------------------------------------------------------
 */
void tiStart(tb)
TiBuf *tb;
{
    times(&(tb->timeBuf));
    tb->uStart = tb->uNow;
    tb->sStart = tb->sNow;
}/*tiStart()*/


/*-----------------------------------------------------------------------------
 * tiStop - Stop a phase timing.
 *-----------------------------------------------------------------------------
 */
void tiStop(tb)
TiBuf *tb;
{
    times(&(tb->timeBuf));
    tb->elapsed = (tb->uNow - tb->uStart) + (tb->sNow - tb->sStart);
}/*tiStop()*/


/*-----------------------------------------------------------------------------
 * tiPrint - Print required time.
 *-----------------------------------------------------------------------------
 */
void tiPrint(tb, mode)
TiBuf *tb;
TiMode mode;
{
    int sTot, hs, s, m;

    hs = ((tb->elapsed % (int)divFactor) * 100) / divFactor;
    sTot = tb->elapsed / divFactor;

    s = sTot % 60;
    m = sTot / 60;

    switch (mode) {

    case TiMS:
	printf("%02d:%02d", m, s);
	break;

    case TiMSC:
	printf("%02d:%02d.%02d", m, s, hs);
	break;

    case TiSC:
    default:
	printf("%3d.%02d", sTot, hs);
	break;

    }/*switch*/
}/*tiPrint()*/


/*-----------------------------------------------------------------------------
 * tiC - Return the elapsed time in centi-seconds
 *-----------------------------------------------------------------------------
 */
int tiC(tb)
TiBuf *tb;
{
    return (tb->elapsed * 100) / divFactor;
}/*tiC()*/
