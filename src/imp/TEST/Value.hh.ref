//============ Value.hh
//=======================================================================

#ifndef _Value_hh
#define _Value_hh

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



//-----------------------------------------------------------------------
// Value

#ifndef Value_CLASS_ID
#define Value_CLASS_ID 9
#endif


class Value : public DbAbstractObject {
public:
    static Value* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    Value* updatenext(DbResultCode& result, LocalTransaction* trId);
    Value* removenext(DbResultCode& result, LocalTransaction* trId);
    Value* openrlocknext(DbResultCode& result, LocalTransaction* trId);
    Value* opennext(DbResultCode& result, Value* dol = NULL);
    void next(Value* data); // set


protected:
    // Constructors
    Value(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    Value(ClassIdentity classIdentity, DbResultCode& result);

    static Value* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static Value* open(DbTitle* title,
	DbResultCode& result,
	Value* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* next_;

    friend AttributeProperty;
    friend Value;
}; // Value

#endif
//-- EoF ------------------------------------------------------------
