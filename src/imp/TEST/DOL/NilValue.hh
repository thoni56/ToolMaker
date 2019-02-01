//============ NilValue.hh
//=======================================================================

#ifndef _NilValue_hh
#define _NilValue_hh

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
// NilValue

#ifndef NilValue_CLASS_ID
#define NilValue_CLASS_ID 15
#endif



class NilValue : public PrimitiveValue {
public:
    static NilValue* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface

protected:
    // Constructors
    NilValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    NilValue(ClassIdentity classIdentity, DbResultCode& result);

    static NilValue* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static NilValue* open(DbTitle* title,
	DbResultCode& result,
	NilValue* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:

    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, PrimitiveValue*);
    friend Value* Value::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Value* Value::open(DbTitle*, DbResultCode&, Value*);
}; // NilValue

#endif
//-- EoF ------------------------------------------------------------
