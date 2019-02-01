//============ DbObject.hh
//=======================================================================

#ifndef _DbObject_hh
#define _DbObject_hh

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
#include "DbEntity.hh"


//-----------------------------------------------------------------------
// DbObject

#ifndef DbObject_CLASS_ID
#define DbObject_CLASS_ID 2
#endif

class DbObjectIterator {
public:
    void reset();
    DbObject* updateNext(DbResultCode& result, LocalTransaction* trId);
    DbObject* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    DbObject* openNext(DbResultCode& result, DbObject* dol = NULL);
protected:
    friend DbObject;
    DbObjectIterator();
    DbObjectIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    ObjectIndex index; 
};


class DbObject : public DbEntity {
public:
    static DbObject* create(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DbObject* update(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DbObject* remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DbObject* openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DbObject* open(Name key,
	DbResultCode& result,
	DbObject* dol = NULL);

    int getClassNo();

    static DbObjectIterator* getIterator();

    // Attribute interface

protected:
    friend DbObjectIterator;
    // Constructors
    DbObject(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static DbObject* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static DbObject* open(DbTitle* title,
	DbResultCode& result,
	DbObject* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:

    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DbEntity*);
}; // DbObject

#endif
//-- EoF ------------------------------------------------------------
