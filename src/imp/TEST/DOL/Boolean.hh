//============ Boolean.hh
//=======================================================================

#ifndef _Boolean_hh
#define _Boolean_hh


//-----------------------------------------------------------------------
// Boolean

class Boolean {
public:
    // Persistent elements
    Boolean value;

    // Constructor
    Boolean(Boolean);   
    Boolean();   

    // Ranking operators
    Boolean operator==(Boolean);
    Boolean operator<(Boolean);
}; // Boolean

class BooleanAttribute {
public:
    DbResultCode get(DbBaseObject*, AttributeIndex, Boolean&);
    DbResultCode get(DbBaseObject*, AttributeIndex, Boolean&, int index);
    DbResultCode set(DbBaseObject*, AttributeIndex, Boolean);
    DbResultCode set(DbBaseObject*, AttributeIndex, Boolean, int index);

}; // BooleanAttribute

#endif
//-- EoF ------------------------------------------------------------
