//============ PersistentStructure.cc
//=======================================================================

#include "DOL.hh"
#include "PersistentStructure.hh"


// Include referenced classes:
#include "PersistentElement.hh"


//-----------------------------------------------------------------------
// PersistentStructure::create

PersistentStructure* PersistentStructure::create(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PersistentStructure_CLASS_ID, &key, 32);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// PersistentStructure::update

PersistentStructure* PersistentStructure::update(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PersistentStructure_CLASS_ID, &key, 32);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// PersistentStructure::remove

PersistentStructure* PersistentStructure::remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PersistentStructure_CLASS_ID, &key, 32);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// PersistentStructure::openrlock

PersistentStructure* PersistentStructure::openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PersistentStructure_CLASS_ID, &key, 32);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// PersistentStructure::open

PersistentStructure* PersistentStructure::open(Name key,
	DbResultCode& result,
	PersistentStructure* dol)
{
    DbTitle title (PersistentStructure_CLASS_ID, &key, 32);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// PersistentStructure::getClassNo

int PersistentStructure::getClassNo()
{
    return PersistentStructure_CLASS_ID;
}


//-----------------------------------------------------------------------
// PersistentStructure::getIterator

PersistentStructureIterator* PersistentStructure::getIterator()
{
    return new PersistentStructureIterator;
}


//-----------------------------------------------------------------------
// PersistentStructure::open

PersistentStructure* PersistentStructure::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (PersistentStructure*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case PersistentStructure_CLASS_ID:
	    return new PersistentStructure (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// PersistentStructure::open

PersistentStructure* PersistentStructure::open(DbTitle *title, DbResultCode& result, PersistentStructure* dol)
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
// PersistentStructure::PersistentStructure

PersistentStructure::PersistentStructure(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    PersistentStructure::init(op);
}


//-----------------------------------------------------------------------
// PersistentStructure::init

void PersistentStructure::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	Structure::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
    persistent_ = NULL;
}


//-----------------------------------------------------------------------
// PersistentStructure::updatepersistent

PersistentElement* PersistentStructure::updatepersistent(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (persistent_ != NULL)
        title = persistent_->getTitle();
    else {
        persistent_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return PersistentElement::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// PersistentStructure::removepersistent

PersistentElement* PersistentStructure::removepersistent(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (persistent_ != NULL)
        title = persistent_->getTitle();
    else {
        persistent_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return PersistentElement::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// PersistentStructure::openrlockpersistent

PersistentElement* PersistentStructure::openrlockpersistent(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (persistent_ != NULL)
        title = persistent_->getTitle();
    else {
        persistent_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return PersistentElement::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// PersistentStructure::openpersistent

PersistentElement* PersistentStructure::openpersistent(DbResultCode& result, PersistentElement* dol)
{
    DbTitle* title;
    if (persistent_ != NULL)
        title = persistent_->getTitle();
    else {
        persistent_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return PersistentElement::open(title, result, OPEN, NULL);
        else
            return PersistentElement::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// PersistentStructure::persistent

void PersistentStructure::persistent(PersistentElement* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (persistent_ &&  persistent_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete persistent_;
	if (data)
            persistent_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    persistent_ = DbTitleRef::nilRef();
    }
    else error("PersistentStructure::persistent");
}





//-----------------------------------------------------------------------
// PersistentStructure::prepare

DbResultCode PersistentStructure::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (persistent_ != NULL) {
        DbTitle* title = persistent_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            persistent_->prepare(theObject, &temp);  //byt namn
    }
    return Structure::prepare();
}


//-----------------------------------------------------------------------
// PersistentStructure::commit

void PersistentStructure::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (persistent_ != NULL) {
        persistent_->commit(theObject, 3);
	if (persistent_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete persistent_;
	persistent_ = NULL;
    }
    Structure::commit();
}


//-----------------------------------------------------------------------
// PersistentStructure::rollback

void PersistentStructure::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (persistent_)
	if (persistent_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete persistent_;
    persistent_ = NULL;
    Structure::rollback();
}


//-----------------------------------------------------------------------
// PersistentStructureIterator::PersistentStructureIterator

PersistentStructureIterator::PersistentStructureIterator()
{
    attrNumber = -1;
    index = -1;
}



//-----------------------------------------------------------------------
// PersistentStructureIterator::updateNext

PersistentStructure* PersistentStructureIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PersistentStructure* temp;
    while (TRUE) {
        result = dbmanager->iterate(PersistentStructure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PersistentStructure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = PersistentStructure::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PersistentStructureIterator::openrlockNext

PersistentStructure* PersistentStructureIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PersistentStructure* temp;
    while (TRUE) {
        result = dbmanager->iterate(PersistentStructure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PersistentStructure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = PersistentStructure::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PersistentStructureIterator::openNext

PersistentStructure* PersistentStructureIterator::openNext(DbResultCode& result, PersistentStructure* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PersistentStructure* temp;
    while (TRUE) {
        result = dbmanager->iterate(PersistentStructure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PersistentStructure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = PersistentStructure::open(&title, result, OPEN, NULL);
	else
            temp = PersistentStructure::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PersistentStructureIterator::reset

void PersistentStructureIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
