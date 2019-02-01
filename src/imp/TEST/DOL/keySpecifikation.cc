//============ keySpecifikation.cc
//=======================================================================

#include "DOL.hh"
#include "keySpecifikation.hh"


// Include referenced classes:
#include "Attribute.hh"


//-----------------------------------------------------------------------
// keySpecifikation::create

keySpecifikation* keySpecifikation::create(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title = DbTitle::generateTitle(keySpecifikation_CLASS_ID);
    return open(title, result, CREATE, trId);
}







//-----------------------------------------------------------------------
// keySpecifikation::getClassNo

int keySpecifikation::getClassNo()
{
    return keySpecifikation_CLASS_ID;
}



//-----------------------------------------------------------------------
// keySpecifikation::open

keySpecifikation* keySpecifikation::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (keySpecifikation*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case keySpecifikation_CLASS_ID:
	    return new keySpecifikation (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// keySpecifikation::open

keySpecifikation* keySpecifikation::open(DbTitle *title, DbResultCode& result, keySpecifikation* dol)
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
// keySpecifikation::keySpecifikation

keySpecifikation::keySpecifikation(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    keySpecifikation::init(op);
}


//-----------------------------------------------------------------------
// keySpecifikation::init

void keySpecifikation::init(DBOperation op)
{
    if (op == CREATE) {
    }
    int i = 0;
    name_ = NULL;
}


//-----------------------------------------------------------------------
// keySpecifikation::updatename

Attribute* keySpecifikation::updatename(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (name_ != NULL)
        title = name_->getTitle();
    else {
        name_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return Attribute::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// keySpecifikation::removename

Attribute* keySpecifikation::removename(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (name_ != NULL)
        title = name_->getTitle();
    else {
        name_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Attribute::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// keySpecifikation::openrlockname

Attribute* keySpecifikation::openrlockname(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (name_ != NULL)
        title = name_->getTitle();
    else {
        name_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Attribute::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// keySpecifikation::openname

Attribute* keySpecifikation::openname(DbResultCode& result, Attribute* dol)
{
    DbTitle* title;
    if (name_ != NULL)
        title = name_->getTitle();
    else {
        name_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return Attribute::open(title, result, OPEN, NULL);
        else
            return Attribute::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// keySpecifikation::name

void keySpecifikation::name(Attribute* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (name_ &&  name_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete name_;
	if (data)
            name_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    name_ = DbTitleRef::nilRef();
    }
    else error("keySpecifikation::name");
}



//-----------------------------------------------------------------------
// keySpecifikation::indexStructure

Name keySpecifikation::indexStructure(void) // get
{
    Name temp;
    indexStructure_.get(theObject, 2, temp);
    return temp;
}


//-----------------------------------------------------------------------
// keySpecifikation::indexStructure

void keySpecifikation::indexStructure(Name data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        indexStructure_.set(theObject, 2, data);
    }
    else error("keySpecifikation::indexStructure");
}




//-----------------------------------------------------------------------
// keySpecifikation::prepare

DbResultCode keySpecifikation::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (name_ != NULL) {
        DbTitle* title = name_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            name_->prepare(theObject, &temp);  //byt namn
    }
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// keySpecifikation::commit

void keySpecifikation::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (name_ != NULL) {
        name_->commit(theObject, 1);
	if (name_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete name_;
	name_ = NULL;
    }
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// keySpecifikation::rollback

void keySpecifikation::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (name_)
	if (name_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete name_;
    name_ = NULL;
    DbAbstractObject::rollback();
}







//-- EoF ------------------------------------------------------------
