//============ StringValue.hh
//=======================================================================

#ifndef _StringValue_hh
#define _StringValue_hh

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
// StringValue

#ifndef StringValue_CLASS_ID
#define StringValue_CLASS_ID 14
#endif



class StringValue : public PrimitiveValue {
public:
    static StringValue* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    DynamicString* updatevalue(DbResultCode& result, LocalTransaction* trId);
    DynamicString* removevalue(DbResultCode& result, LocalTransaction* trId);
    DynamicString* openrlockvalue(DbResultCode& result, LocalTransaction* trId);
    DynamicString* openvalue(DbResultCode& result, DynamicString* dol = NULL);
    void value(DynamicString* data); // set


protected:
    // Constructors
    StringValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    StringValue(ClassIdentity classIdentity, DbResultCode& result);

    static StringValue* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static StringValue* open(DbTitle* title,
	DbResultCode& result,
	StringValue* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* value_;

    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, PrimitiveValue*);
    friend Value* Value::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Value* Value::open(DbTitle*, DbResultCode&, Value*);
}; // StringValue

#endif
//-- EoF ------------------------------------------------------------
