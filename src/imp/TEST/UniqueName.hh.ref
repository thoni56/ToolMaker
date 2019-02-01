//============ UniqueName.hh
//=======================================================================

#ifndef _UniqueName_hh
#define _UniqueName_hh


//-----------------------------------------------------------------------
// UniqueName

class UniqueName {
public:
    // Persistent elements
    char base[32];
    char name[32];

    // Constructor
    UniqueName(char *,char *);   
    UniqueName();   

    // Ranking operators
    Boolean operator==(UniqueName);
    Boolean operator<(UniqueName);
}; // UniqueName

class UniqueNameAttribute {
public:
    DbResultCode get(DbBaseObject*, AttributeIndex, UniqueName&);
    DbResultCode get(DbBaseObject*, AttributeIndex, UniqueName&, int index);
    DbResultCode set(DbBaseObject*, AttributeIndex, UniqueName);
    DbResultCode set(DbBaseObject*, AttributeIndex, UniqueName, int index);

}; // UniqueNameAttribute

#endif
//-- EoF ------------------------------------------------------------
