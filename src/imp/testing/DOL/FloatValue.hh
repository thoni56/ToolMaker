//============ FloatValue.hh
//=======================================================================

#ifndef _FloatValue_hh
#define _FloatValue_hh

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
// FloatValue

#ifndef FloatValue_CLASS_ID
#define FloatValue_CLASS_ID 12
#endif



class FloatValue : public PrimitiveValue {
public:
    static FloatValue* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    Float value(void); // get
    void value(Float data); // set


protected:
    // Constructors
    FloatValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    FloatValue(ClassIdentity classIdentity, DbResultCode& result);

    static FloatValue* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static FloatValue* open(DbTitle* title,
	DbResultCode& result,
	FloatValue* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    FloatAttribute value_;

    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, PrimitiveValue*);
    friend Value* Value::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Value* Value::open(DbTitle*, DbResultCode&, Value*);
}; // FloatValue

#endif
//-- EoF ------------------------------------------------------------
