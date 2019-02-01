//============ Relation.hh
//=======================================================================

#ifndef _Relation_hh
#define _Relation_hh

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
#include "DbObject.hh"


//-----------------------------------------------------------------------
// Relation

#ifndef Relation_CLASS_ID
#define Relation_CLASS_ID 17
#endif

class RelationIterator {
public:
    void reset();
    Relation* updateNext(DbResultCode& result, LocalTransaction* trId);
    Relation* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    Relation* openNext(DbResultCode& result, Relation* dol = NULL);
protected:
    friend Relation;
    RelationIterator();
    RelationIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    ObjectIndex index; 
};


class Relation : public DbObject {
public:
    static Relation* create(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Relation* update(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Relation* remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Relation* openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Relation* open(Name key,
	DbResultCode& result,
	Relation* dol = NULL);

    int getClassNo();

    static RelationIterator* getIterator();

    // Attribute interface
    Class* updatefrom(DbResultCode& result, LocalTransaction* trId);
    Class* removefrom(DbResultCode& result, LocalTransaction* trId);
    Class* openrlockfrom(DbResultCode& result, LocalTransaction* trId);
    Class* openfrom(DbResultCode& result, Class* dol = NULL);
    void from(Class* data); // set

    Class* updateto(DbResultCode& result, LocalTransaction* trId);
    Class* removeto(DbResultCode& result, LocalTransaction* trId);
    Class* openrlockto(DbResultCode& result, LocalTransaction* trId);
    Class* opento(DbResultCode& result, Class* dol = NULL);
    void to(Class* data); // set


protected:
    friend RelationIterator;
    // Constructors
    Relation(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static Relation* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static Relation* open(DbTitle* title,
	DbResultCode& result,
	Relation* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* from_;
    DbTitleRef* to_;

    friend DbObject* DbObject::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend DbObject* DbObject::open(DbTitle*, DbResultCode&, DbObject*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DbEntity*);
}; // Relation

#endif
//-- EoF ------------------------------------------------------------
