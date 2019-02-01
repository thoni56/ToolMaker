//============ Class.hh
//=======================================================================

#ifndef _Class_hh
#define _Class_hh

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
// Class

#ifndef Class_CLASS_ID
#define Class_CLASS_ID 3
#endif

class ClassIterator {
public:
    void reset();
    Class* updateNext(DbResultCode& result, LocalTransaction* trId);
    Class* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    Class* openNext(DbResultCode& result, Class* dol = NULL);
protected:
    friend Class;
    ClassIterator();
    ClassIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    char searchValue[1];
    ObjectIndex index; 
};


class Class : public DbObject {
public:
    static Class* create(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Class* update(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Class* remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Class* openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Class* open(Name key,
	DbResultCode& result,
	Class* dol = NULL);

    int getClassNo();

    static ClassIterator* getIterator();

    // Attribute interface
    keySpecifikation* updateprimaryKey(DbResultCode& result, LocalTransaction* trId);
    keySpecifikation* removeprimaryKey(DbResultCode& result, LocalTransaction* trId);
    keySpecifikation* openrlockprimaryKey(DbResultCode& result, LocalTransaction* trId);
    keySpecifikation* openprimaryKey(DbResultCode& result, keySpecifikation* dol = NULL);
    void primaryKey(keySpecifikation* data); // set

    Boolean allocate(void); // get
    void allocate(Boolean data); // set
    static ClassIterator* searchallocate(Boolean);

    Class* updatebase(DbResultCode& result, LocalTransaction* trId);
    Class* removebase(DbResultCode& result, LocalTransaction* trId);
    Class* openrlockbase(DbResultCode& result, LocalTransaction* trId);
    Class* openbase(DbResultCode& result, Class* dol = NULL);
    void base(Class* data); // set

    ClassAttributes* createattributes(DbResultCode& result);
    ClassAttributes* openattributes(DbResultCode& result);


protected:
    friend ClassIterator;
    // Constructors
    Class(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static Class* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static Class* open(DbTitle* title,
	DbResultCode& result,
	Class* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* primaryKey_;
    BooleanAttribute allocate_;
    DbTitleRef* base_;
    ClassAttributes* attributes_;

    friend Class;
    friend Relation;
    friend DbObject* DbObject::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend DbObject* DbObject::open(DbTitle*, DbResultCode&, DbObject*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend DbEntity* DbEntity::open(DbTitle*, DbResultCode&, DbEntity*);
}; // Class

#endif
//-- EoF ------------------------------------------------------------
