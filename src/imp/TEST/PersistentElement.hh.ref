//============ PersistentElement.hh
//=======================================================================

#ifndef _PersistentElement_hh
#define _PersistentElement_hh

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
#include "Element.hh"


//-----------------------------------------------------------------------
// PersistentElement

#ifndef PersistentElement_CLASS_ID
#define PersistentElement_CLASS_ID 22
#endif

class PersistentElementIterator {
public:
    void reset();
    PersistentElement* updateNext(DbResultCode& result, LocalTransaction* trId);
    PersistentElement* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    PersistentElement* openNext(DbResultCode& result, PersistentElement* dol = NULL);
protected:
    friend PersistentElement;
    PersistentElementIterator();
    PersistentElementIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    char searchValue[4];
    ObjectIndex index; 
};


class PersistentElement : public Element {
public:
    static PersistentElement* create(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PersistentElement* update(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PersistentElement* remove(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PersistentElement* openrlock(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static PersistentElement* open(UniqueName key,
	DbResultCode& result,
	PersistentElement* dol = NULL);

    int getClassNo();

    static PersistentElementIterator* getIterator();

    // Attribute interface
    PredefinedType* updatetype(DbResultCode& result, LocalTransaction* trId);
    PredefinedType* removetype(DbResultCode& result, LocalTransaction* trId);
    PredefinedType* openrlocktype(DbResultCode& result, LocalTransaction* trId);
    PredefinedType* opentype(DbResultCode& result, PredefinedType* dol = NULL);
    void type(PredefinedType* data); // set

    Integer size(void); // get
    void size(Integer data); // set
    static PersistentElementIterator* searchsize(Integer);


protected:
    friend PersistentElementIterator;
    // Constructors
    PersistentElement(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static PersistentElement* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static PersistentElement* open(DbTitle* title,
	DbResultCode& result,
	PersistentElement* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* type_;
    IntegerAttribute size_;

    friend PersistentStructure;
    friend DynamicStructure;
    friend Element* Element::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Element* Element::open(DbTitle*, DbResultCode&, Element*);
}; // PersistentElement

#endif
//-- EoF ------------------------------------------------------------
