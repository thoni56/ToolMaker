//============ Integer.hh
//=======================================================================

#ifndef _Integer_hh
#define _Integer_hh


//-----------------------------------------------------------------------
// Integer

class Integer {
public:
    // Persistent elements
    Integer_32 value;

    // Constructor
    Integer(Integer_32);   
    Integer();   

    // Ranking operators
    Boolean operator==(Integer);
    Boolean operator<(Integer);
}; // Integer

class IntegerAttribute {
public:
    DbResultCode get(DbBaseObject*, AttributeIndex, Integer&);
    DbResultCode get(DbBaseObject*, AttributeIndex, Integer&, int index);
    DbResultCode set(DbBaseObject*, AttributeIndex, Integer);
    DbResultCode set(DbBaseObject*, AttributeIndex, Integer, int index);

}; // IntegerAttribute

#endif
//-- EoF ------------------------------------------------------------
