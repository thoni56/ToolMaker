//============ VolatileElement.hh
//=======================================================================

#ifndef _VolatileElement_hh
#define _VolatileElement_hh

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
// VolatileElement

#ifndef VolatileElement_CLASS_ID
#define VolatileElement_CLASS_ID 24
#endif

class VolatileElementIterator {
public:
    void reset();
    VolatileElement* updateNext(DbResultCode& result, LocalTransaction* trId);
    VolatileElement* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    VolatileElement* openNext(DbResultCode& result, VolatileElement* dol = NULL);
protected:
    friend VolatileElement;
    VolatileElementIterator();
    VolatileElementIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    char searchValue[32];
    ObjectIndex index; 
};


class VolatileElement : public Element {
public:
    static VolatileElement* create(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static VolatileElement* update(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static VolatileElement* remove(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static VolatileElement* openrlock(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static VolatileElement* open(UniqueName key,
	DbResultCode& result,
	VolatileElement* dol = NULL);

    int getClassNo();

    static VolatileElementIterator* getIterator();

    // Attribute interface
    Name type(void); // get
    void type(Name data); // set
    static VolatileElementIterator* searchtype(Name);


protected:
    friend VolatileElementIterator;
    // Constructors
    VolatileElement(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static VolatileElement* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static VolatileElement* open(DbTitle* title,
	DbResultCode& result,
	VolatileElement* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    NameAttribute type_;

    friend Structure;
    friend Element* Element::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend Element* Element::open(DbTitle*, DbResultCode&, Element*);
}; // VolatileElement

#endif
//-- EoF ------------------------------------------------------------
