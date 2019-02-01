//============ DbEntity.hh
//=======================================================================

#ifndef _DbEntity_hh
#define _DbEntity_hh

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
// DbEntity

#ifndef DbEntity_CLASS_ID
#define DbEntity_CLASS_ID 1
#endif

class DbEntityIterator {
public:
    void reset();
    DbEntity* updateNext(DbResultCode& result, LocalTransaction* trId);
    DbEntity* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    DbEntity* openNext(DbResultCode& result, DbEntity* dol = NULL);
protected:
    friend DbEntity;
    DbEntityIterator();
    DbEntityIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    char searchValue[32];
    ObjectIndex index; 
};

class DbEntity : public DbAbstractObject {
public:
    static DbEntity* create(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DbEntity* update(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DbEntity* remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DbEntity* openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DbEntity* open(Name key,
	DbResultCode& result,
	DbEntity* dol = NULL);

    int getClassNo();

    static DbEntityIterator* getIterator();

    // Attribute interface
    Name name(void); // get
    static DbEntityIterator* searchname(Name);

    DynamicString* updateversion(DbResultCode& result, LocalTransaction* trId);
    DynamicString* removeversion(DbResultCode& result, LocalTransaction* trId);
    DynamicString* openrlockversion(DbResultCode& result, LocalTransaction* trId);
    DynamicString* openversion(DbResultCode& result, DynamicString* dol = NULL);
    void version(DynamicString* data); // set


protected:
    friend DbEntityIterator;
    // Constructors
    DbEntity(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static DbEntity* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static DbEntity* open(DbTitle* title,
	DbResultCode& result,
	DbEntity* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    NameAttribute name_;
    DbTitleRef* version_;

    friend AttributeType;
}; // DbEntity

#endif
//-- EoF ------------------------------------------------------------
