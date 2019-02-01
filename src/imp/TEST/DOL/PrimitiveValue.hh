//============ PrimitiveValue.hh
//=======================================================================

#ifndef _PrimitiveValue_hh
#define _PrimitiveValue_hh

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
#include "Value.hh"


//-----------------------------------------------------------------------
// PrimitiveValue

#ifndef PrimitiveValue_CLASS_ID
#define PrimitiveValue_CLASS_ID 10
#endif



class PrimitiveValue : public Value {
public:
    static PrimitiveValue* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface

protected:
    // Constructors
    PrimitiveValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    PrimitiveValue(ClassIdentity classIdentity, DbResultCode& result);

    static PrimitiveValue* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static PrimitiveValue* open(DbTitle* title,
	DbResultCode& result,
	PrimitiveValue* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:

    friend StructureValue;
    friend Value* Value::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Value* Value::open(DbTitle*, DbResultCode&, Value*);
}; // PrimitiveValue

#endif
//-- EoF ------------------------------------------------------------
