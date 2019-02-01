//============ Attribute.hh
//=======================================================================

#ifndef _Attribute_hh
#define _Attribute_hh

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
// Attribute

#ifndef Attribute_CLASS_ID
#define Attribute_CLASS_ID 5
#endif

class AttributeIterator {
public:
    void reset();
    Attribute* updateNext(DbResultCode& result, LocalTransaction* trId);
    Attribute* openrlockNext(DbResultCode& result, LocalTransaction* trId);
    Attribute* openNext(DbResultCode& result, Attribute* dol = NULL);
protected:
    friend Attribute;
    AttributeIterator();
    AttributeIterator(AttributeIndex attr, void* value, int length);
    AttributeIndex attrNumber;
    char searchValue[64];
    ObjectIndex index; 
};

class Attribute : public DbAbstractObject {
public:
    static Attribute* create(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Attribute* update(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Attribute* remove(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Attribute* openrlock(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId);

    static Attribute* open(UniqueName key,
	DbResultCode& result,
	Attribute* dol = NULL);

    int getClassNo();

    static AttributeIterator* getIterator();

    // Attribute interface
    UniqueName name(void); // get
    static AttributeIterator* searchname(UniqueName);

    AttributeType* updatetype(DbResultCode& result, LocalTransaction* trId);
    AttributeType* removetype(DbResultCode& result, LocalTransaction* trId);
    AttributeType* openrlocktype(DbResultCode& result, LocalTransaction* trId);
    AttributeType* opentype(DbResultCode& result, AttributeType* dol = NULL);
    void type(AttributeType* data); // set

    AttributeProperty* updateproperties(DbResultCode& result, LocalTransaction* trId);
    AttributeProperty* removeproperties(DbResultCode& result, LocalTransaction* trId);
    AttributeProperty* openrlockproperties(DbResultCode& result, LocalTransaction* trId);
    AttributeProperty* openproperties(DbResultCode& result, AttributeProperty* dol = NULL);
    void properties(AttributeProperty* data); // set

    Integer attributeIdentity(void); // get
    void attributeIdentity(Integer data); // set
    static AttributeIterator* searchattributeIdentity(Integer);


protected:
    friend AttributeIterator;
    // Constructors
    Attribute(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    static Attribute* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static Attribute* open(DbTitle* title,
	DbResultCode& result,
	Attribute* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    UniqueNameAttribute name_;
    DbTitleRef* type_;
    DbTitleRef* properties_;
    IntegerAttribute attributeIdentity_;

    friend keySpecifikation;
    friend ClassAttributes;
}; // Attribute

#endif
//-- EoF ------------------------------------------------------------
