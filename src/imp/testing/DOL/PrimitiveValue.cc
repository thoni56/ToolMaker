//============ PrimitiveValue.cc
//=======================================================================

#include "DOL.hh"
#include "PrimitiveValue.hh"

// Include subclasses:
#include "IntegerValue.hh"
#include "FloatValue.hh"
#include "BooleanValue.hh"
#include "StringValue.hh"
#include "NilValue.hh"



//-----------------------------------------------------------------------
// PrimitiveValue::create

PrimitiveValue* PrimitiveValue::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(PrimitiveValue_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// PrimitiveValue::getClassNo

int PrimitiveValue::getClassNo()
{
    return PrimitiveValue_CLASS_ID;
}



//-----------------------------------------------------------------------
// PrimitiveValue::open

PrimitiveValue* PrimitiveValue::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (PrimitiveValue*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case PrimitiveValue_CLASS_ID:
	    return new PrimitiveValue (object, tempObject, op, trId, title);
	case IntegerValue_CLASS_ID:
	    return (PrimitiveValue*) new IntegerValue (object, tempObject, op, trId, title);
	case FloatValue_CLASS_ID:
	    return (PrimitiveValue*) new FloatValue (object, tempObject, op, trId, title);
	case BooleanValue_CLASS_ID:
	    return (PrimitiveValue*) new BooleanValue (object, tempObject, op, trId, title);
	case StringValue_CLASS_ID:
	    return (PrimitiveValue*) new StringValue (object, tempObject, op, trId, title);
	case NilValue_CLASS_ID:
	    return (PrimitiveValue*) new NilValue (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// PrimitiveValue::open

PrimitiveValue* PrimitiveValue::open(DbTitle *title, DbResultCode& result, PrimitiveValue* dol)
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
// PrimitiveValue::PrimitiveValue

PrimitiveValue::PrimitiveValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    PrimitiveValue::init(op);
}


//-----------------------------------------------------------------------
// PrimitiveValue::init

void PrimitiveValue::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	Value::init(op);
    if (op == CREATE) {
    }
    int i = 0;
}




//-----------------------------------------------------------------------
// PrimitiveValue::prepare

DbResultCode PrimitiveValue::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return Value::prepare();
}


//-----------------------------------------------------------------------
// PrimitiveValue::commit

void PrimitiveValue::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    Value::commit();
}


//-----------------------------------------------------------------------
// PrimitiveValue::rollback

void PrimitiveValue::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    Value::rollback();
}







//-- EoF ------------------------------------------------------------
