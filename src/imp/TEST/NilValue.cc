//============ NilValue.cc
//=======================================================================

#include "DOL.hh"
#include "NilValue.hh"




//-----------------------------------------------------------------------
// NilValue::create

NilValue* NilValue::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(NilValue_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// NilValue::getClassNo

int NilValue::getClassNo()
{
    return NilValue_CLASS_ID;
}



//-----------------------------------------------------------------------
// NilValue::open

NilValue* NilValue::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (NilValue*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case NilValue_CLASS_ID:
	    return new NilValue (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// NilValue::open

NilValue* NilValue::open(DbTitle *title, DbResultCode& result, NilValue* dol)
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
// NilValue::NilValue

NilValue::NilValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    NilValue::init(op);
}


//-----------------------------------------------------------------------
// NilValue::init

void NilValue::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	PrimitiveValue::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
}




//-----------------------------------------------------------------------
// NilValue::prepare

DbResultCode NilValue::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return PrimitiveValue::prepare();
}


//-----------------------------------------------------------------------
// NilValue::commit

void NilValue::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    PrimitiveValue::commit();
}


//-----------------------------------------------------------------------
// NilValue::rollback

void NilValue::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    PrimitiveValue::rollback();
}







//-- EoF ------------------------------------------------------------
