//============ PersistentStructure.hh
//=======================================================================

#ifndef _PersistentStructure_hh
#define _PersistentStructure_hh

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
// PersistentStructure

#ifndef PersistentStructure_CLASS_ID
#define PersistentStructure_CLASS_ID 19
#endif

class PersistentStructureIterator {
public:
    void reset();
    PersistentStructure* updateNext(DbResultCode& result, LocalTransaction* trId);
    PersistentStructure* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    PersistentStructure* openNext(DbResultCode& result, PersistentStructure* dol = NULL);
protected:
    friend PersistentStructure;
    PersistentStructureIterator();
    PersistentStructureIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    ObjectIndex index; 
};


class PersistentStructure : public Structure {
public:
    static PersistentStructure* create(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PersistentStructure* update(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PersistentStructure* remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PersistentStructure* openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PersistentStructure* open(Name key,
	DbResultCode& result,
	PersistentStructure* dol = NULL);

    int getClassNo();

    static PersistentStructureIterator* getIterator();

    // Attribute interface
    PersistentElement* updatepersistent(DbResultCode& result, LocalTransaction* trId);
    PersistentElement* removepersistent(DbResultCode& result, LocalTransaction* trId);
    PersistentElement* openrlockpersistent(DbResultCode& result, LocalTransaction* trId);
    PersistentElement* openpersistent(DbResultCode& result, PersistentElement* dol = NULL);
    void persistent(PersistentElement* data); // set


protected:
    friend PersistentStructureIterator;
    // Constructors
    PersistentStructure(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static PersistentStructure* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static PersistentStructure* open(DbTitle* title,
	DbResultCode& result,
	PersistentStructure* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* persistent_;

    friend Structure* Structure::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Structure* Structure::open(DbTitle*, DbResultCode&, Structure*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DbEntity*);
}; // PersistentStructure

#endif
//-- EoF ------------------------------------------------------------
