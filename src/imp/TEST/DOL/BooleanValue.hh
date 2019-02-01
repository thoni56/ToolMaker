//============ BooleanValue.hh
//=======================================================================

#ifndef _BooleanValue_hh
#define _BooleanValue_hh

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
// BooleanValue

#ifndef BooleanValue_CLASS_ID
#define BooleanValue_CLASS_ID 13
#endif



class BooleanValue : public PrimitiveValue {
public:
    static BooleanValue* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    Boolean value(void); // get
    void value(Boolean data); // set


protected:
    // Constructors
    BooleanValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    BooleanValue(ClassIdentity classIdentity, DbResultCode& result);

    static BooleanValue* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static BooleanValue* open(DbTitle* title,
	DbResultCode& result,
	BooleanValue* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    BooleanAttribute value_;

    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend PrimitiveValue* PrimitiveValue::open(DbTitle*, DbResultCode&, PrimitiveValue*);
    friend Value* Value::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Value* Value::open(DbTitle*, DbResultCode&, Value*);
}; // BooleanValue

#endif
//-- EoF ------------------------------------------------------------
