//============ ArrayAttributeType.cc
//=======================================================================

#include "DOL.hh"
#include "ArrayAttributeType.hh"




//-----------------------------------------------------------------------
// ArrayAttributeType::create

ArrayAttributeType* ArrayAttributeType::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(ArrayAttributeType_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// ArrayAttributeType::getClassNo

int ArrayAttributeType::getClassNo()
{
    return ArrayAttributeType_CLASS_ID;
}



//-----------------------------------------------------------------------
// ArrayAttributeType::open

ArrayAttributeType* ArrayAttributeType::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (ArrayAttributeType*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case ArrayAttributeType_CLASS_ID:
	    return new ArrayAttributeType (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// ArrayAttributeType::open

ArrayAttributeType* ArrayAttributeType::open(DbTitle *title, DbResultCode& result, ArrayAttributeType* dol)
{
    result = dol->reOpen(title);
    if (result != SUCCEEDED) 
        return NULL;
    else {
        dol->init(OPEN, TRUE);
        return dol;
    }
}


//-----------------------------------------------------------------------
// ArrayAttributeType::ArrayAttributeType

ArrayAttributeType::ArrayAttributeType(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    ArrayAttributeType::init(op);
}


//-----------------------------------------------------------------------
// ArrayAttributeType::init

void ArrayAttributeType::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	AttributeType::init(op);
    if (op == CREATE) {
    }
    int i = 0;
}


//-----------------------------------------------------------------------
// ArrayAttributeType::lowIndex

Integer ArrayAttributeType::lowIndex(void) // get
{
    Integer temp;
    lowIndex_.get(theObject, 2, temp);
    return temp;
}


//-----------------------------------------------------------------------
// ArrayAttributeType::lowIndex

void ArrayAttributeType::lowIndex(Integer data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        lowIndex_.set(theObject, 2, data);
    }
    else error("ArrayAttributeType::lowIndex");
}


//-----------------------------------------------------------------------
// ArrayAttributeType::highIndex

Integer ArrayAttributeType::highIndex(void) // get
{
    Integer temp;
    highIndex_.get(theObject, 3, temp);
    return temp;
}


//-----------------------------------------------------------------------
// ArrayAttributeType::highIndex

void ArrayAttributeType::highIndex(Integer data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        highIndex_.set(theObject, 3, data);
    }
    else error("ArrayAttributeType::highIndex");
}




//-----------------------------------------------------------------------
// ArrayAttributeType::prepare

DbResultCode ArrayAttributeType::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return AttributeType::prepare();
}


//-----------------------------------------------------------------------
// ArrayAttributeType::commit

void ArrayAttributeType::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    AttributeType::commit();
}


//-----------------------------------------------------------------------
// ArrayAttributeType::rollback

void ArrayAttributeType::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    AttributeType::rollback();
}







//-- EoF ------------------------------------------------------------
