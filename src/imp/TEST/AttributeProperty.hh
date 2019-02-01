//============ AttributeProperty.hh
//=======================================================================

#ifndef _AttributeProperty_hh
#define _AttributeProperty_hh

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
// AttributeProperty

#ifndef AttributeProperty_CLASS_ID
#define AttributeProperty_CLASS_ID 8
#endif


class AttributeProperty : public DbAbstractObject {
public:
    static AttributeProperty* create(DbResultCode& result, LocalTransaction* trId);

    int getClassNo();


    // Attribute interface
    Boolean null(void); // get
    void null(Boolean data); // set

    Value* updateinitial(DbResultCode& result, LocalTransaction* trId);
    Value* removeinitial(DbResultCode& result, LocalTransaction* trId);
    Value* openrlockinitial(DbResultCode& result, LocalTransaction* trId);
    Value* openinitial(DbResultCode& result, Value* dol = NULL);
    void initial(Value* data); // set

    Value* updatereset(DbResultCode& result, LocalTransaction* trId);
    Value* removereset(DbResultCode& result, LocalTransaction* trId);
    Value* openrlockreset(DbResultCode& result, LocalTransaction* trId);
    Value* openreset(DbResultCode& result, Value* dol = NULL);
    void reset(Value* data); // set


protected:
    // Constructors
    AttributeProperty(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
        DbTitle* title);

    AttributeProperty(ClassIdentity classIdentity, DbResultCode& result);

    static AttributeProperty* open(DbTitle* title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId);

    static AttributeProperty* open(DbTitle* title,
	DbResultCode& result,
	AttributeProperty* dol);

    void init(DBOperation);

    // Transaction handling
    DbResultCode prepare();
    void commit();
    void rollback();

private:
    BooleanAttribute null_;
    DbTitleRef* initial_;
    DbTitleRef* reset_;

    friend Attribute;
}; // AttributeProperty

#endif
//-- EoF ------------------------------------------------------------
