//============ DynString.hh
//=======================================================================

#ifndef _DynString_hh
#define _DynString_hh


//-----------------------------------------------------------------------
// DynString

class DynString {
public:
    // Persistent elements
    Boolean full;
    Integer_16 length;
    char buffer[200];

    // Constructor
    DynString(Boolean,Integer_16,char *);   
    DynString();   

    // Ranking operators
    Boolean operator==(DynString);
    Boolean operator<(DynString);
}; // DynString

class DynStringAttribute {
public:
    DbResultCode get(DbBaseObject*, AttributeIndex, DynString&);
    DbResultCode get(DbBaseObject*, AttributeIndex, DynString&, int index);
    DbResultCode set(DbBaseObject*, AttributeIndex, DynString);
    DbResultCode set(DbBaseObject*, AttributeIndex, DynString, int index);

}; // DynStringAttribute

#endif
//-- EoF ------------------------------------------------------------
