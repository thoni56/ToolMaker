//============ StringValue.cc
//=======================================================================

#include "DOL.hh"
#include "StringValue.hh"


// Include referenced classes:
#include "DynamicString.hh"


//-----------------------------------------------------------------------
// StringValue::create

StringValue* StringValue::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(StringValue_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// StringValue::getClassNo

int StringValue::getClassNo()
{
    return StringValue_CLASS_ID;
}



//-----------------------------------------------------------------------
// StringValue::open

StringValue* StringValue::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (StringValue*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case StringValue_CLASS_ID:
	    return new StringValue (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// StringValue::open

StringValue* StringValue::open(DbTitle *title, DbResultCode& result, StringValue* dol)
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
// StringValue::StringValue

StringValue::StringValue(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    StringValue::init(op);
}


//-----------------------------------------------------------------------
// StringValue::init

void StringValue::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	PrimitiveValue::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
    value_ = NULL;
}


//-----------------------------------------------------------------------
// StringValue::updatevalue

DynamicString* StringValue::updatevalue(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (value_ != NULL)
        title = value_->getTitle();
    else {
        value_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return DynamicString::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// StringValue::removevalue

DynamicString* StringValue::removevalue(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (value_ != NULL)
        title = value_->getTitle();
    else {
        value_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return DynamicString::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// StringValue::openrlockvalue

DynamicString* StringValue::openrlockvalue(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (value_ != NULL)
        title = value_->getTitle();
    else {
        value_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return DynamicString::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// StringValue::openvalue

DynamicString* StringValue::openvalue(DbResultCode& result, DynamicString* dol)
{
    DbTitle* title;
    if (value_ != NULL)
        title = value_->getTitle();
    else {
        value_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return DynamicString::open(title, result, OPEN, NULL);
        else
            return DynamicString::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// StringValue::value

void StringValue::value(DynamicString* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (value_ &&  value_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete value_;
	if (data)
            value_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    value_ = DbTitleRef::nilRef();
    }
    else error("StringValue::value");
}





//-----------------------------------------------------------------------
// StringValue::prepare

DbResultCode StringValue::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (value_ != NULL) {
        DbTitle* title = value_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            value_->prepare(theObject, &temp);  //byt namn
    }
    return PrimitiveValue::prepare();
}


//-----------------------------------------------------------------------
// StringValue::commit

void StringValue::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (value_ != NULL) {
        value_->commit(theObject, 2);
	if (value_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete value_;
	value_ = NULL;
    }
    PrimitiveValue::commit();
}


//-----------------------------------------------------------------------
// StringValue::rollback

void StringValue::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (value_)
	if (value_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete value_;
    value_ = NULL;
    PrimitiveValue::rollback();
}







//-- EoF ------------------------------------------------------------
