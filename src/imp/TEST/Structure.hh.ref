//============ Structure.hh
//=======================================================================

#ifndef _Structure_hh
#define _Structure_hh

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
// Structure

#ifndef Structure_CLASS_ID
#define Structure_CLASS_ID 18
#endif

class StructureIterator {
public:
    void reset();
    Structure* updateNext(DbResultCode& result, LocalTransaction* trId);
    Structure* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    Structure* openNext(DbResultCode& result, Structure* dol = NULL);
protected:
    friend Structure;
    StructureIterator();
    StructureIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    ObjectIndex index; 
};


class Structure : public DbEntity {
public:
    static Structure* create(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Structure* update(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Structure* remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Structure* openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Structure* open(Name key,
	DbResultCode& result,
	Structure* dol = NULL);

    int getClassNo();

    static StructureIterator* getIterator();

    // Attribute interface
    VolatileElement* updatevolatile(DbResultCode& result, LocalTransaction* trId);
    VolatileElement* removevolatile(DbResultCode& result, LocalTransaction* trId);
    VolatileElement* openrlockvolatile(DbResultCode& result, LocalTransaction* trId);
    VolatileElement* openvolatile(DbResultCode& result, VolatileElement* dol = NULL);
    void volatile(VolatileElement* data); // set


protected:
    friend StructureIterator;
    // Constructors
    Structure(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static Structure* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static Structure* open(DbTitle* title,
	DbResultCode& result,
	Structure* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* volatile_;

    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DbEntity*);
}; // Structure

#endif
//-- EoF ------------------------------------------------------------
