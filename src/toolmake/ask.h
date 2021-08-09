/* ask.h                              Date: 1993-04-17/reibert@roo

   Common definitions for ask

   1.00 -
*/
#ifndef _ask_H_
#define _ask_H_ 1

#define ENGLISH 1
#define SWEDISH 46

#define A_NDV 1                         /* no default value */
#define A_NSD 2                         /* not show default */
#define A_RE  4                         /* return on error */
#define A_RF  8                         /* return on fatal error */
#define A_NE 16                         /* no echo on input */

typedef enum {
    askBuffering,
    askStartDefaultString,
    askStopDefaultString,
    askHelpCharSet,
    askEolnCharSet,
    askNumericPrompt,
    askCommandPrompt,
    askBooleanPrompt,
    askHelpWidth,
    askHelpColumns,
    askInitBuffer,
    askFlushBuffer,
/*--*/
    askVersion
} AskCommand;

#define PRIVATE static
#define PUBLIC
#define IN
#define OUT
#define IN_OUT

#ifndef TRUE
typedef int boolean;

#define FALSE 0
#define TRUE 1
#endif

#ifdef PROTOTYPES

int askString(
    IN char *prompt,
    IN_OUT char *value,
    IN int length,
    IN char *help,
    IN int askCommandWord
);

int askBool(
    IN char *prompt,
    IN_OUT boolean *value,
    IN char *help,
    IN char *error,
    IN int askCommandWord
);

int askCom(
    IN char *prompt,
    IN_OUT int *menueNumber,
    IN char *menue[],
    IN char *help,
    IN int askCommandWord
);

int askSet(
    IN AskCommand command,
    IN long value
);
int askGet(
    IN AskCommand command,
    OUT long value
);

#else

int askCom();
int askBool();
int askString();

int askSet();
int askGet();

#endif

#endif
