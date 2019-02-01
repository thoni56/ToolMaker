//============ keySpecifikation.hh
//=======================================================================

#ifndef _keySpecifikation_hh
#define _keySpecifikation_hh

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
// keySpecifikation

#ifndef keySpecifikation_CLASS_ID
#define keySpecifikation_CLASS_ID 4
#endif


class keySpecifikation : public DbAbstractObject {
public:
    static keySpecifikation* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    Attribute* updatename(DbResultCode& result, LocalTransaction* trId);
    Attribute* removename(DbResultCode& result, LocalTransaction* trId);
    Attribute* openrlockname(DbResultCode& result, LocalTransaction* trId);
    Attribute* openname(DbResultCode& result, Attribute* dol = NULL);
    void name(Attribute* data); // set

    Name indexStructure(void); // get
    void indexStructure(Name data); // set


protected:
    // Constructors
    keySpecifikation(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    keySpecifikation(ClassIdentity classIdentity, DbResultCode& result);

    static keySpecifikation* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static keySpecifikation* open(DbTitle* title,
	DbResultCode& result,
	keySpecifikation* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    DbTitleRef* name_;
    NameAttribute indexStructure_;

    friend Class;
}; // keySpecifikation

#endif
//-- EoF ------------------------------------------------------------
