//============ Name.hh
//=======================================================================

#ifndef _Name_hh
#define _Name_hh


//-----------------------------------------------------------------------
// Name

class Name {
public:
    // Persistent elements
    char value[32];

    // Constructor
    Name(char *);   
    Name();   

    // Ranking operators
    Boolean operator==(Name);
    Boolean operator<(Name);
}; // Name

class NameAttribute {
public:
    DbResultCode get(DbBaseObject*, AttributeIndex, Name&);
    DbResultCode get(DbBaseObject*, AttributeIndex, Name&, int index);
    DbResultCode set(DbBaseObject*, AttributeIndex, Name);
    DbResultCode set(DbBaseObject*, AttributeIndex, Name, int index);

}; // NameAttribute

#endif
//-- EoF ------------------------------------------------------------
