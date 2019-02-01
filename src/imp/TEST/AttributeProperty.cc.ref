//============ AttributeProperty.cc
//=======================================================================

#include "DOL.hh"
#include "AttributeProperty.hh"


// Include referenced classes:
#include "Value.hh"


//-----------------------------------------------------------------------
// AttributeProperty::create

AttributeProperty* AttributeProperty::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(AttributeProperty_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// AttributeProperty::getClassNo

int AttributeProperty::getClassNo()
{
    return AttributeProperty_CLASS_ID;
}



//-----------------------------------------------------------------------
// AttributeProperty::open

AttributeProperty* AttributeProperty::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (AttributeProperty*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case AttributeProperty_CLASS_ID:
	    return new AttributeProperty (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// AttributeProperty::open

AttributeProperty* AttributeProperty::open(DbTitle *title, DbResultCode& result, AttributeProperty* dol)
{
    result = dol->reOpen(title);
    if (result != SUCCEEDED) 
        return NULL;
    else {
        dol->init(OPEN);
        return dol;
    }
}


//-----------------------------------------------------------------------
// AttributeProperty::AttributeProperty

AttributeProperty::AttributeProperty(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    AttributeProperty::init(op);
}


//-----------------------------------------------------------------------
// AttributeProperty::init

void AttributeProperty::init(DBOperation op)
{
    if (op == CREATE) {
    }
    int i = 0;
    initial_ = NULL;
    reset_ = NULL;
}


//-----------------------------------------------------------------------
// AttributeProperty::null

Boolean AttributeProperty::null(void) // get
{
    Boolean temp;
    null_.get(theObject, 1, temp);
    return temp;
}


//-----------------------------------------------------------------------
// AttributeProperty::null

void AttributeProperty::null(Boolean data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        null_.set(theObject, 1, data);
    }
    else error("AttributeProperty::null");
}


//-----------------------------------------------------------------------
// AttributeProperty::updateinitial

Value* AttributeProperty::updateinitial(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (initial_ != NULL)
        title = initial_->getTitle();
    else {
        initial_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return Value::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeProperty::removeinitial

Value* AttributeProperty::removeinitial(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (initial_ != NULL)
        title = initial_->getTitle();
    else {
        initial_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Value::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeProperty::openrlockinitial

Value* AttributeProperty::openrlockinitial(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (initial_ != NULL)
        title = initial_->getTitle();
    else {
        initial_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Value::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// AttributeProperty::openinitial

Value* AttributeProperty::openinitial(DbResultCode& result, Value* dol)
{
    DbTitle* title;
    if (initial_ != NULL)
        title = initial_->getTitle();
    else {
        initial_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return Value::open(title, result, OPEN, NULL);
        else
            return Value::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeProperty::initial

void AttributeProperty::initial(Value* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (initial_ &&  initial_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete initial_;
	if (data)
            initial_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    initial_ = DbTitleRef::nilRef();
    }
    else error("AttributeProperty::initial");
}



//-----------------------------------------------------------------------
// AttributeProperty::updatereset

Value* AttributeProperty::updatereset(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (reset_ != NULL)
        title = reset_->getTitle();
    else {
        reset_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return Value::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeProperty::removereset

Value* AttributeProperty::removereset(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (reset_ != NULL)
        title = reset_->getTitle();
    else {
        reset_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Value::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeProperty::openrlockreset

Value* AttributeProperty::openrlockreset(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (reset_ != NULL)
        title = reset_->getTitle();
    else {
        reset_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Value::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// AttributeProperty::openreset

Value* AttributeProperty::openreset(DbResultCode& result, Value* dol)
{
    DbTitle* title;
    if (reset_ != NULL)
        title = reset_->getTitle();
    else {
        reset_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return Value::open(title, result, OPEN, NULL);
        else
            return Value::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// AttributeProperty::reset

void AttributeProperty::reset(Value* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (reset_ &&  reset_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete reset_;
	if (data)
            reset_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    reset_ = DbTitleRef::nilRef();
    }
    else error("AttributeProperty::reset");
}





//-----------------------------------------------------------------------
// AttributeProperty::prepare

DbResultCode AttributeProperty::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (initial_ != NULL) {
        DbTitle* title = initial_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            initial_->prepare(theObject, &temp);  //byt namn
    }
    if (reset_ != NULL) {
        DbTitle* title = reset_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            reset_->prepare(theObject, &temp);  //byt namn
    }
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// AttributeProperty::commit

void AttributeProperty::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (initial_ != NULL) {
        initial_->commit(theObject, 2);
	if (initial_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete initial_;
	initial_ = NULL;
    }
    if (reset_ != NULL) {
        reset_->commit(theObject, 3);
	if (reset_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete reset_;
	reset_ = NULL;
    }
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// AttributeProperty::rollback

void AttributeProperty::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (initial_)
	if (initial_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete initial_;
    initial_ = NULL;
    if (reset_)
	if (reset_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete reset_;
    reset_ = NULL;
    DbAbstractObject::rollback();
}







//-- EoF ------------------------------------------------------------
