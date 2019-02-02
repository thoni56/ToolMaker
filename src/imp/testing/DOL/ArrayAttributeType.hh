//============ ArrayAttributeType.hh
//=======================================================================

#ifndef _ArrayAttributeType_hh
#define _ArrayAttributeType_hh

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
#include "AttributeType.hh"


//-----------------------------------------------------------------------
// ArrayAttributeType

#ifndef ArrayAttributeType_CLASS_ID
#define ArrayAttributeType_CLASS_ID 7
#endif



class ArrayAttributeType : public AttributeType {
public:
    static ArrayAttributeType* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    Integer lowIndex(void); // get
    void lowIndex(Integer data); // set

    Integer highIndex(void); // get
    void highIndex(Integer data); // set


protected:
    // Constructors
    ArrayAttributeType(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    ArrayAttributeType(ClassIdentity classIdentity, DbResultCode& result);

    static ArrayAttributeType* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static ArrayAttributeType* open(DbTitle* title,
	DbResultCode& result,
	ArrayAttributeType* dol);

    void init(DBOperation, Boolean initBase = FALSE);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    IntegerAttribute lowIndex_;
    IntegerAttribute highIndex_;

    friend AttributeType* AttributeType::open(DbTitle*, DbResultCode&, DBOperation, LocalTransaction*);
    friend AttributeType* AttributeType::open(DbTitle*, DbResultCode&, AttributeType*);
}; // ArrayAttributeType

#endif
//-- EoF ------------------------------------------------------------
