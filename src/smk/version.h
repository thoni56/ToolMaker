#ifndef _version_h_
#define _version_h_ 1

typedef struct {
    char* string;
    int   version;
    int   revision;
    int   correction;
    char* state;
} VERSION;

typedef struct {
    char*   abbreviation;
    char*   name;
    char*   shortHeader;
    char*   longHeader;
    char*   date;
    char*   time;
    VERSION version;
} PRODUCT;

#ifndef _version_c_
extern PRODUCT product;
#endif

#endif
