//============ PredefinedType.hh
//=======================================================================

#ifndef _PredefinedType_hh
#define _PredefinedType_hh

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
// PredefinedType

#ifndef PredefinedType_CLASS_ID
#define PredefinedType_CLASS_ID 23
#endif

class PredefinedTypeIterator {
public:
    void reset();
    PredefinedType* updateNext(DbResultCode& result, LocalTransaction* trId);
    PredefinedType* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    PredefinedType* openNext(DbResultCode& result, PredefinedType* dol = NULL);
protected:
    friend PredefinedType;
    PredefinedTypeIterator();
    PredefinedTypeIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    char searchValue[32];
    ObjectIndex index; 
};

class PredefinedType : public DbAbstractObject {
public:
    static PredefinedType* create(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PredefinedType* update(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PredefinedType* remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PredefinedType* openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PredefinedType* open(Name key,
	DbResultCode& result,
	PredefinedType* dol = NULL);

    int getClassNo();

    static PredefinedTypeIterator* getIterator();

    // Attribute interface
    Name name(void); // get
    static PredefinedTypeIterator* searchname(Name);


protected:
    friend PredefinedTypeIterator;
    // Constructors
    PredefinedType(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static PredefinedType* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static PredefinedType* open(DbTitle* title,
	DbResultCode& result,
	PredefinedType* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    NameAttribute name_;

    friend PersistentElement;
}; // PredefinedType

#endif
//-- EoF ------------------------------------------------------------
