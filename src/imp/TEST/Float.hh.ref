//============ Float.hh
//=======================================================================

#ifndef _Float_hh
#define _Float_hh


//-----------------------------------------------------------------------
// Float

class Float {
public:
    // Persistent elements
    Real_64 value;

    // Constructor
    Float(Real_64);   
    Float();   

    // Ranking operators
    Boolean operator==(Float);
    Boolean operator<(Float);
}; // Float

class FloatAttribute {
public:
    DbResultCode get(DbBaseObject*, AttributeIndex, Float&);
    DbResultCode get(DbBaseObject*, AttributeIndex, Float&, int index);
    DbResultCode set(DbBaseObject*, AttributeIndex, Float);
    DbResultCode set(DbBaseObject*, AttributeIndex, Float, int index);

}; // FloatAttribute

#endif
//-- EoF ------------------------------------------------------------
