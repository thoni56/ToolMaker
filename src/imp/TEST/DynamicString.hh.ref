//============ DynamicString.hh
//=======================================================================

#ifndef _DynamicString_hh
#define _DynamicString_hh

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
// DynamicString

#ifndef DynamicString_CLASS_ID
#define DynamicString_CLASS_ID 25
#endif


class DynamicString : public DbAbstractObject {
public:
    static DynamicString* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    DynString string(void); // get
    void string(DynString data); // set

    DynamicString* updatenext(DbResultCode& result, LocalTransaction* trId);
    DynamicString* removenext(DbResultCode& result, LocalTransaction* trId);
    DynamicString* openrlocknext(DbResultCode& result, LocalTransaction* trId);
    DynamicString* opennext(DbResultCode& result, DynamicString* dol = NULL);
    void next(DynamicString* data); // set


protected:
    // Constructors
    DynamicString(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    DynamicString(ClassIdentity classIdentity, DbResultCode& result);

    static DynamicString* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static DynamicString* open(DbTitle* title,
	DbResultCode& result,
	DynamicString* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DynStringAttribute string_;
    DbTitleRef* next_;

    friend DbEntity;
    friend StringValue;
    friend DynamicString;
}; // DynamicString

#endif
//-- EoF ------------------------------------------------------------

