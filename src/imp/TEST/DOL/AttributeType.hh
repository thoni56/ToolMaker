//============ AttributeType.hh
//=======================================================================

#ifndef _AttributeType_hh
#define _AttributeType_hh

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
// AttributeType

#ifndef AttributeType_CLASS_ID
#define AttributeType_CLASS_ID 6
#endif


class AttributeType : public DbAbstractObject {
public:
    static AttributeType* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    DbEntity* updateitem(DbResultCode& result, LocalTransaction* trId);
    DbEntity* removeitem(DbResultCode& result, LocalTransaction* trId);
    DbEntity* openrlockitem(DbResultCode& result, LocalTransaction* trId);
    DbEntity* openitem(DbResultCode& result, DbEntity* dol = NULL);
    void item(DbEntity* data); // set


protected:
    // Constructors
    AttributeType(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    AttributeType(ClassIdentity classIdentity, DbResultCode& result);

    static AttributeType* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static AttributeType* open(DbTitle* title,
	DbResultCode& result,
	AttributeType* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* item_;

    friend Attribute;
}; // AttributeType

#endif
//-- EoF ------------------------------------------------------------
