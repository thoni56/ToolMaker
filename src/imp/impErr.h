
/* These datatypes should be defined to be unsigned integers of length 1, 2
 * and 4 bytes respectively.
 */
typedef unsigned char UByte1;
typedef unsigned short UByte2;
typedef unsigned int UByte4;

#include "impList.h"
#include "impCommon.h"

#define MaxTokens 3

extern void impRPoi();	/* Error recovery - restart point  */
extern void impISym();	/* Error recovery - insert symbol  */
extern void impDSym();	/* Error recovery - delete symbol  */
extern void impMess();	/* Error recovery - error message  */

