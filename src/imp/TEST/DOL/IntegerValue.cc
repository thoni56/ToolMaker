//============ IntegerValue.cc
//=======================================================================

#include "DOL.hh"
#include "IntegerValue.hh"




//-----------------------------------------------------------------------
// IntegerValue::create

IntegerValue* IntegerValue::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(IntegerValue_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// IntegerValue::getClassNo

int IntegerValue::getClassNo()
{
    return IntegerValue_CLASS_ID;
}



//-----------------------------------------------------------------------
// IntegerValue::open

IntegerValue* IntegerValue::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (IntegerValue*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case IntegerValue_CLASS_ID:
	    return new IntegerValue (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// IntegerValue::open

IntegerValue* IntegerValue::open(DbTitle *title, DbResultCode& result, IntegerValue* dol)
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
// IntegerValue::IntegerValue

IntegerValue::IntegerValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    IntegerValue::init(op);
}


//-----------------------------------------------------------------------
// IntegerValue::init

void IntegerValue::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	PrimitiveValue::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
}


//-----------------------------------------------------------------------
// IntegerValue::value

Integer IntegerValue::value(void) // get
{
    Integer temp;
    value_.get(theObject, 2, temp);
    return temp;
}


//-----------------------------------------------------------------------
// IntegerValue::value

void IntegerValue::value(Integer data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        value_.set(theObject, 2, data);
    }
    else error("IntegerValue::value");
}




//-----------------------------------------------------------------------
// IntegerValue::prepare

DbResultCode IntegerValue::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return PrimitiveValue::prepare();
}


//-----------------------------------------------------------------------
// IntegerValue::commit

void IntegerValue::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    PrimitiveValue::commit();
}


//-----------------------------------------------------------------------
// IntegerValue::rollback

void IntegerValue::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    PrimitiveValue::rollback();
}







//-- EoF ------------------------------------------------------------
