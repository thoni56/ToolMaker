//============ DynamicString.cc
//=======================================================================

#include "DOL.hh"
#include "DynamicString.hh"


// Include referenced classes:


//-----------------------------------------------------------------------
// DynamicString::create

DynamicString* DynamicString::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(DynamicString_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// DynamicString::getClassNo

int DynamicString::getClassNo()
{
    return DynamicString_CLASS_ID;
}



//-----------------------------------------------------------------------
// DynamicString::open

DynamicString* DynamicString::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (DynamicString*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case DynamicString_CLASS_ID:
	    return new DynamicString (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// DynamicString::open

DynamicString* DynamicString::open(DbTitle *title, DbResultCode& result, DynamicString* dol)
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
// DynamicString::DynamicString

DynamicString::DynamicString(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    DynamicString::init(op);
}


//-----------------------------------------------------------------------
// DynamicString::init

void DynamicString::init(DBOperation op)
{
    if (op == CREATE) {
        // next_ = DbTitleRef::nilRef();    // 4f - Nil reference
    }
    int i = 0;
    next_ = NULL;
}


//-----------------------------------------------------------------------
// DynamicString::string

DynString DynamicString::string(void) // get
{
    DynString temp;
    string_.get(theObject, 1, temp);
    return temp;
}


//-----------------------------------------------------------------------
// DynamicString::string

void DynamicString::string(DynString data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        string_.set(theObject, 1, data);
    }
    else error("DynamicString::string");
}


//-----------------------------------------------------------------------
// DynamicString::updatenext

DynamicString* DynamicString::updatenext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return DynamicString::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// DynamicString::removenext

DynamicString* DynamicString::removenext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return DynamicString::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// DynamicString::openrlocknext

DynamicString* DynamicString::openrlocknext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return DynamicString::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// DynamicString::opennext

DynamicString* DynamicString::opennext(DbResultCode& result, DynamicString* dol)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 2, title);
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
// DynamicString::next

void DynamicString::next(DynamicString* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (next_ &&  next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete next_;
	if (data)
            next_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    next_ = DbTitleRef::nilRef();
    }
    else error("DynamicString::next");
}





//-----------------------------------------------------------------------
// DynamicString::prepare

DbResultCode DynamicString::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (next_ != NULL) {
        DbTitle* title = next_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            next_->prepare(theObject, &temp);  //byt namn
    }
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// DynamicString::commit

void DynamicString::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (next_ != NULL) {
        next_->commit(theObject, 2);
	if (next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete next_;
	next_ = NULL;
    }
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// DynamicString::rollback

void DynamicString::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (next_)
	if (next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete next_;
    next_ = NULL;
    DbAbstractObject::rollback();
}







//-- EoF ------------------------------------------------------------

