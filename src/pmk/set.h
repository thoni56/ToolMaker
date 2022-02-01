#ifndef SetIncluded
#define SetIncluded

/* Type of defined set variables. SET must be used for global
 * variables whereas SETPTR can be used for automatic variables and
 * pointers.
 */
typedef unsigned char SET[];
typedef unsigned char *SETPTR;

/* Use SETDEF(variable,length) to define a set variable
 * which have a 'length' elements.
 */
#define SETLEN(length) ((length+7)>>3)
#define SETDEF(var,length) unsigned char var[SETLEN(length)]

/*

  Some set operations.

  SetUnion: setOut <- setIn1 (Union) setIn2
  SetInter: setOut <- setIn1 (Intersection) setIn2
  SetDiff : setOut <- setIn1 (Not In) setIn2
  SetCompl: setOut <- (Complement) setIn1
  SetClear: set <- 0
  SetEmpty:     return 1 if set is not empty (0), otherwise 0

  SetMem: return elem (In) set
  setIns: set <- set (Intersection) {elem}
  setDel: set <- set (Not in) {elem}
  setClr:       remove all members from lowermember to uppermember (inclusive)

*/

extern void SetUnion( /* SET setIn1, SET setIn2, SET setOut, int length */ );
extern void SetInter( /* SET setIn1, SET setIn2, SET setOut, int length */ );
extern void SetDiff ( /* SET setIn1, SET setIn2, SET setOut, int length */ );
extern void SetCompl( /* SET setIn , SET setOut, int length */ );
extern void SetClear( /* SET set   , int length */ );
extern int  SetEmpty( /* SET set   , int length */ );

extern int  SetMem( /* SET set, int elem */ );
extern void SetIns( /* SET set, int elem */ );
extern void SetDel( /* SET set, int elem */ );
extern void SetClr( /* SET set, int lowermember, int uppermember */ );

#endif
