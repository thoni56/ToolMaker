//============ StructureValue.hh
//=======================================================================

#ifndef _StructureValue_hh
#define _StructureValue_hh

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
// StructureValue

#ifndef StructureValue_CLASS_ID
#define StructureValue_CLASS_ID 16
#endif



class StructureValue : public Value {
public:
    static StructureValue* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    PrimitiveValue* updatevalues(DbResultCode& result, LocalTransaction* trId);
    PrimitiveValue* removevalues(DbResultCode& result, LocalTransaction* trId);
    PrimitiveValue* openrlockvalues(DbResultCode& result, LocalTransaction* trId);
    PrimitiveValue* openvalues(DbResultCode& result, PrimitiveValue* dol = NULL);
    void values(PrimitiveValue* data); // set


protected:
    // Constructors
    StructureValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    StructureValue(ClassIdentity classIdentity, DbResultCode& result);

    static StructureValue* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static StructureValue* open(DbTitle* title,
	DbResultCode& result,
	StructureValue* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* values_;

    friend Value* Value::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Value* Value::open(DbTitle*, DbResultCode&, Value*);
}; // StructureValue

#endif
//-- EoF ------------------------------------------------------------
