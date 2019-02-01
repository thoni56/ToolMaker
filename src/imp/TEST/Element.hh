//============ Element.hh
//=======================================================================

#ifndef _Element_hh
#define _Element_hh

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
// Element

#ifndef Element_CLASS_ID
#define Element_CLASS_ID 21
#endif

class ElementIterator {
public:
    void reset();
    Element* updateNext(DbResultCode& result, LocalTransaction* trId);
    Element* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    Element* openNext(DbResultCode& result, Element* dol = NULL);
protected:
    friend Element;
    ElementIterator();
    ElementIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    char searchValue[64];
    ObjectIndex index; 
};

class Element : public DbAbstractObject {
public:
    static Element* create(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Element* update(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Element* remove(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Element* openrlock(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Element* open(UniqueName key,
	DbResultCode& result,
	Element* dol = NULL);

    int getClassNo();

    static ElementIterator* getIterator();

    // Attribute interface
    UniqueName name(void); // get
    static ElementIterator* searchname(UniqueName);

    Element* updatenext(DbResultCode& result, LocalTransaction* trId);
    Element* removenext(DbResultCode& result, LocalTransaction* trId);
    Element* openrlocknext(DbResultCode& result, LocalTransaction* trId);
    Element* opennext(DbResultCode& result, Element* dol = NULL);
    void next(Element* data); // set


protected:
    friend ElementIterator;
    // Constructors
    Element(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static Element* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static Element* open(DbTitle* title,
	DbResultCode& result,
	Element* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    UniqueNameAttribute name_;
    DbTitleRef* next_;

    friend Element;
}; // Element

#endif
//-- EoF ------------------------------------------------------------
