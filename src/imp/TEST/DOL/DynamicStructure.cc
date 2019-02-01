//============ DynamicStructure.cc
//=======================================================================

#include "DOL.hh"
#include "DynamicStructure.hh"


// Include referenced classes:
#include "PersistentElement.hh"


//-----------------------------------------------------------------------
// DynamicStructure::create

DynamicStructure* DynamicStructure::create(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DynamicStructure_CLASS_ID, &key, 32);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// DynamicStructure::update

DynamicStructure* DynamicStructure::update(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DynamicStructure_CLASS_ID, &key, 32);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// DynamicStructure::remove

DynamicStructure* DynamicStructure::remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DynamicStructure_CLASS_ID, &key, 32);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// DynamicStructure::openrlock

DynamicStructure* DynamicStructure::openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DynamicStructure_CLASS_ID, &key, 32);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// DynamicStructure::open

DynamicStructure* DynamicStructure::open(Name key,
	DbResultCode& result,
	DynamicStructure* dol)
{
    DbTitle title (DynamicStructure_CLASS_ID, &key, 32);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// DynamicStructure::getClassNo

int DynamicStructure::getClassNo()
{
    return DynamicStructure_CLASS_ID;
}


//-----------------------------------------------------------------------
// DynamicStructure::getIterator

DynamicStructureIterator* DynamicStructure::getIterator()
{
    return new DynamicStructureIterator;
}


//-----------------------------------------------------------------------
// DynamicStructure::open

DynamicStructure* DynamicStructure::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (DynamicStructure*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case DynamicStructure_CLASS_ID:
	    return new DynamicStructure (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// DynamicStructure::open

DynamicStructure* DynamicStructure::open(DbTitle *title, DbResultCode& result, DynamicStructure* dol)
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
// DynamicStructure::DynamicStructure

DynamicStructure::DynamicStructure(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    DynamicStructure::init(op);
}


//-----------------------------------------------------------------------
// DynamicStructure::init

void DynamicStructure::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	Structure::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
    dynamic_ = NULL;
}


//-----------------------------------------------------------------------
// DynamicStructure::updatedynamic

PersistentElement* DynamicStructure::updatedynamic(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (dynamic_ != NULL)
        title = dynamic_->getTitle();
    else {
        dynamic_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return PersistentElement::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// DynamicStructure::removedynamic

PersistentElement* DynamicStructure::removedynamic(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (dynamic_ != NULL)
        title = dynamic_->getTitle();
    else {
        dynamic_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return PersistentElement::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// DynamicStructure::openrlockdynamic

PersistentElement* DynamicStructure::openrlockdynamic(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (dynamic_ != NULL)
        title = dynamic_->getTitle();
    else {
        dynamic_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return PersistentElement::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// DynamicStructure::opendynamic

PersistentElement* DynamicStructure::opendynamic(DbResultCode& result, PersistentElement* dol)
{
    DbTitle* title;
    if (dynamic_ != NULL)
        title = dynamic_->getTitle();
    else {
        dynamic_->get(theObject, 3, title);
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
// DynamicStructure::dynamic

void DynamicStructure::dynamic(PersistentElement* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (dynamic_ &&  dynamic_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete dynamic_;
	if (data)
            dynamic_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    dynamic_ = DbTitleRef::nilRef();
    }
    else error("DynamicStructure::dynamic");
}





//-----------------------------------------------------------------------
// DynamicStructure::prepare

DbResultCode DynamicStructure::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (dynamic_ != NULL) {
        DbTitle* title = dynamic_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            dynamic_->prepare(theObject, &temp);  //byt namn
    }
    return Structure::prepare();
}


//-----------------------------------------------------------------------
// DynamicStructure::commit

void DynamicStructure::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (dynamic_ != NULL) {
        dynamic_->commit(theObject, 3);
	if (dynamic_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete dynamic_;
	dynamic_ = NULL;
    }
    Structure::commit();
}


//-----------------------------------------------------------------------
// DynamicStructure::rollback

void DynamicStructure::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (dynamic_)
	if (dynamic_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete dynamic_;
    dynamic_ = NULL;
    Structure::rollback();
}


//-----------------------------------------------------------------------
// DynamicStructureIterator::DynamicStructureIterator

DynamicStructureIterator::DynamicStructureIterator()
{
    attrNumber = -1;
    index = -1;
}



//-----------------------------------------------------------------------
// DynamicStructureIterator::updateNext

DynamicStructure* DynamicStructureIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DynamicStructure* temp;
    while (TRUE) {
        result = dbmanager->iterate(DynamicStructure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DynamicStructure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = DynamicStructure::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DynamicStructureIterator::openrlockNext

DynamicStructure* DynamicStructureIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DynamicStructure* temp;
    while (TRUE) {
        result = dbmanager->iterate(DynamicStructure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DynamicStructure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = DynamicStructure::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DynamicStructureIterator::openNext

DynamicStructure* DynamicStructureIterator::openNext(DbResultCode& result, DynamicStructure* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DynamicStructure* temp;
    while (TRUE) {
        result = dbmanager->iterate(DynamicStructure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DynamicStructure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = DynamicStructure::open(&title, result, OPEN, NULL);
	else
            temp = DynamicStructure::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DynamicStructureIterator::reset

void DynamicStructureIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
