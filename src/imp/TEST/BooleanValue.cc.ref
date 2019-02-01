//============ BooleanValue.cc
//=======================================================================

#include "DOL.hh"
#include "BooleanValue.hh"




//-----------------------------------------------------------------------
// BooleanValue::create

BooleanValue* BooleanValue::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(BooleanValue_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// BooleanValue::getClassNo

int BooleanValue::getClassNo()
{
    return BooleanValue_CLASS_ID;
}



//-----------------------------------------------------------------------
// BooleanValue::open

BooleanValue* BooleanValue::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (BooleanValue*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case BooleanValue_CLASS_ID:
	    return new BooleanValue (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// BooleanValue::open

BooleanValue* BooleanValue::open(DbTitle *title, DbResultCode& result, BooleanValue* dol)
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
// BooleanValue::BooleanValue

BooleanValue::BooleanValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    BooleanValue::init(op);
}


//-----------------------------------------------------------------------
// BooleanValue::init

void BooleanValue::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	PrimitiveValue::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
}


//-----------------------------------------------------------------------
// BooleanValue::value

Boolean BooleanValue::value(void) // get
{
    Boolean temp;
    value_.get(theObject, 2, temp);
    return temp;
}


//-----------------------------------------------------------------------
// BooleanValue::value

void BooleanValue::value(Boolean data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        value_.set(theObject, 2, data);
    }
    else error("BooleanValue::value");
}




//-----------------------------------------------------------------------
// BooleanValue::prepare

DbResultCode BooleanValue::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return PrimitiveValue::prepare();
}


//-----------------------------------------------------------------------
// BooleanValue::commit

void BooleanValue::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    PrimitiveValue::commit();
}


//-----------------------------------------------------------------------
// BooleanValue::rollback

void BooleanValue::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    PrimitiveValue::rollback();
}







//-- EoF ------------------------------------------------------------
