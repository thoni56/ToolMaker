//============ FloatValue.cc
//=======================================================================

#include "DOL.hh"
#include "FloatValue.hh"




//-----------------------------------------------------------------------
// FloatValue::create

FloatValue* FloatValue::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(FloatValue_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// FloatValue::getClassNo

int FloatValue::getClassNo()
{
    return FloatValue_CLASS_ID;
}



//-----------------------------------------------------------------------
// FloatValue::open

FloatValue* FloatValue::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (FloatValue*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case FloatValue_CLASS_ID:
	    return new FloatValue (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// FloatValue::open

FloatValue* FloatValue::open(DbTitle *title, DbResultCode& result, FloatValue* dol)
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
// FloatValue::FloatValue

FloatValue::FloatValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    FloatValue::init(op);
}


//-----------------------------------------------------------------------
// FloatValue::init

void FloatValue::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	PrimitiveValue::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
}


//-----------------------------------------------------------------------
// FloatValue::value

Float FloatValue::value(void) // get
{
    Float temp;
    value_.get(theObject, 2, temp);
    return temp;
}


//-----------------------------------------------------------------------
// FloatValue::value

void FloatValue::value(Float data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        value_.set(theObject, 2, data);
    }
    else error("FloatValue::value");
}




//-----------------------------------------------------------------------
// FloatValue::prepare

DbResultCode FloatValue::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return PrimitiveValue::prepare();
}


//-----------------------------------------------------------------------
// FloatValue::commit

void FloatValue::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    PrimitiveValue::commit();
}


//-----------------------------------------------------------------------
// FloatValue::rollback

void FloatValue::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    PrimitiveValue::rollback();
}







//-- EoF ------------------------------------------------------------
