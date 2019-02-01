//============ DynamicStructure.hh
//=======================================================================

#ifndef _DynamicStructure_hh
#define _DynamicStructure_hh

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
#include "Structure.hh"


//-----------------------------------------------------------------------
// DynamicStructure

#ifndef DynamicStructure_CLASS_ID
#define DynamicStructure_CLASS_ID 20
#endif

class DynamicStructureIterator {
public:
    void reset();
    DynamicStructure* updateNext(DbResultCode& result, LocalTransaction* trId);
    DynamicStructure* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    DynamicStructure* openNext(DbResultCode& result, DynamicStructure* dol = NULL);
protected:
    friend DynamicStructure;
    DynamicStructureIterator();
    DynamicStructureIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    ObjectIndex index; 
};


class DynamicStructure : public Structure {
public:
    static DynamicStructure* create(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DynamicStructure* update(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DynamicStructure* remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DynamicStructure* openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static DynamicStructure* open(Name key,
	DbResultCode& result,
	DynamicStructure* dol = NULL);

    int getClassNo();

    static DynamicStructureIterator* getIterator();

    // Attribute interface
    PersistentElement* updatedynamic(DbResultCode& result, LocalTransaction* trId);
    PersistentElement* removedynamic(DbResultCode& result, LocalTransaction* trId);
    PersistentElement* openrlockdynamic(DbResultCode& result, LocalTransaction* trId);
    PersistentElement* opendynamic(DbResultCode& result, PersistentElement* dol = NULL);
    void dynamic(PersistentElement* data); // set


protected:
    friend DynamicStructureIterator;
    // Constructors
    DynamicStructure(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static DynamicStructure* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static DynamicStructure* open(DbTitle* title,
	DbResultCode& result,
	DynamicStructure* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* dynamic_;

    friend Structure* Structure::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Structure* Structure::open(DbTitle*, DbResultCode&, Structure*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DbEntity*);
}; // DynamicStructure

#endif
//-- EoF ------------------------------------------------------------
