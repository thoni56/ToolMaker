//============ StructureValue.cc
//=======================================================================

#include "DOL.hh"
#include "StructureValue.hh"


// Include referenced classes:
#include "PrimitiveValue.hh"


//-----------------------------------------------------------------------
// StructureValue::create

StructureValue* StructureValue::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(StructureValue_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// StructureValue::getClassNo

int StructureValue::getClassNo()
{
    return StructureValue_CLASS_ID;
}



//-----------------------------------------------------------------------
// StructureValue::open

StructureValue* StructureValue::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (StructureValue*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case StructureValue_CLASS_ID:
	    return new StructureValue (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// StructureValue::open

StructureValue* StructureValue::open(DbTitle *title, DbResultCode& result, StructureValue* dol)
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
// StructureValue::StructureValue

StructureValue::StructureValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    StructureValue::init(op);
}


//-----------------------------------------------------------------------
// StructureValue::init

void StructureValue::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	Value::init(op);
    if (op == CREATE) {
    }
    int i = 0;
    values_ = NULL;
}


//-----------------------------------------------------------------------
// StructureValue::updatevalues

PrimitiveValue* StructureValue::updatevalues(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (values_ != NULL)
        title = values_->getTitle();
    else {
        values_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return PrimitiveValue::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// StructureValue::removevalues

PrimitiveValue* StructureValue::removevalues(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (values_ != NULL)
        title = values_->getTitle();
    else {
        values_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return PrimitiveValue::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// StructureValue::openrlockvalues

PrimitiveValue* StructureValue::openrlockvalues(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (values_ != NULL)
        title = values_->getTitle();
    else {
        values_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return PrimitiveValue::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// StructureValue::openvalues

PrimitiveValue* StructureValue::openvalues(DbResultCode& result, PrimitiveValue* dol)
{
    DbTitle* title;
    if (values_ != NULL)
        title = values_->getTitle();
    else {
        values_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return PrimitiveValue::open(title, result, OPEN, NULL);
        else
            return PrimitiveValue::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// StructureValue::values

void StructureValue::values(PrimitiveValue* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (values_ &&  values_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete values_;
	if (data)
            values_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    values_ = DbTitleRef::nilRef();
    }
    else error("StructureValue::values");
}





//-----------------------------------------------------------------------
// StructureValue::prepare

DbResultCode StructureValue::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (values_ != NULL) {
        DbTitle* title = values_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            values_->prepare(theObject, &temp);  //byt namn
    }
    return Value::prepare();
}


//-----------------------------------------------------------------------
// StructureValue::commit

void StructureValue::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (values_ != NULL) {
        values_->commit(theObject, 2);
	if (values_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete values_;
	values_ = NULL;
    }
    Value::commit();
}


//-----------------------------------------------------------------------
// StructureValue::rollback

void StructureValue::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (values_)
	if (values_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete values_;
    values_ = NULL;
    Value::rollback();
}







//-- EoF ------------------------------------------------------------
