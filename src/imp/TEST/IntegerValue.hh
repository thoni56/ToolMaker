//============ IntegerValue.hh
//=======================================================================

#ifndef _IntegerValue_hh
#define _IntegerValue_hh

#include "DynString.hh"
#include "Boolean.hh"
#include "Integer.hh"
#include "Float.hh"
#include "UniqueName.hh"
#include "Name.hh"
//=======================================================================
// Forward declarations of relations
class ClassAttributes;
//=======================================================================
// Forward declarations of classes
class DbEntity;
class DbObject;
class Class;
class keySpecifikation;
class Attribute;
class AttributeType;
class ArrayAttributeType;
class AttributeProperty;
class Value;
class PrimitiveValue;
class IntegerValue;
class FloatValue;
class BooleanValue;
class StringValue;
class NilValue;
class StructureValue;
class Relation;
class Structure;
class PersistentStructure;
class DynamicStructure;
class Element;
class PersistentElement;
class PredefinedType;
class VolatileElement;
class DynamicString;

// Include superclass:
#include "PrimitiveValue.hh"


//-----------------------------------------------------------------------
// IntegerValue

#ifndef IntegerValue_CLASS_ID
#define IntegerValue_CLASS_ID 11
#endif



class IntegerValue : public PrimitiveValue {
public:
    static IntegerValue* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    Integer value(void); // get
    void value(Integer data); // set


protected:
    // Constructors
    IntegerValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    IntegerValue(ClassIdentity classIdentity, DbResultCode& result);

    static IntegerValue* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static IntegerValue* open(DbTitle* title,
	DbResultCode& result,
	IntegerValue* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    IntegerAttribute value_;

    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, PrimitiveValue*);
    friend Value* Value::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Value* Value::open(DbTitle*, DbResultCode&, Value*);
}; // IntegerValue

#endif
//-- EoF ------------------------------------------------------------
