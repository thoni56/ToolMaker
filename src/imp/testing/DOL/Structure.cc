//============ Structure.cc
//=======================================================================

#include "DOL.hh"
#include "Structure.hh"

// Include subclasses:
#include "PersistentStructure.hh"
#include "DynamicStructure.hh"

// Include referenced classes:
#include "VolatileElement.hh"


//-----------------------------------------------------------------------
// Structure::create

Structure* Structure::create(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Structure_CLASS_ID, &key, 32);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// Structure::update

Structure* Structure::update(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Structure_CLASS_ID, &key, 32);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// Structure::remove

Structure* Structure::remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Structure_CLASS_ID, &key, 32);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// Structure::openrlock

Structure* Structure::openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Structure_CLASS_ID, &key, 32);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// Structure::open

Structure* Structure::open(Name key,
	DbResultCode& result,
	Structure* dol)
{
    DbTitle title (Structure_CLASS_ID, &key, 32);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// Structure::getClassNo

int Structure::getClassNo()
{
    return Structure_CLASS_ID;
}


//-----------------------------------------------------------------------
// Structure::getIterator

StructureIterator* Structure::getIterator()
{
    return new StructureIterator;
}


//-----------------------------------------------------------------------
// Structure::open

Structure* Structure::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (Structure*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case Structure_CLASS_ID:
	    return new Structure (object, tempObject, op, trId, title);
	case PersistentStructure_CLASS_ID:
	    return (Structure*) new PersistentStructure (object, tempObject, op, trId, title);
	case DynamicStructure_CLASS_ID:
	    return (Structure*) new DynamicStructure (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// Structure::open

Structure* Structure::open(DbTitle *title, DbResultCode& result, Structure* dol)
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
// Structure::Structure

Structure::Structure(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    Structure::init(op);
}


//-----------------------------------------------------------------------
// Structure::init

void Structure::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	DbEntity::init(op);
    if (op == CREATE) {
    }
    int i = 0;
    volatile_ = NULL;
}


//-----------------------------------------------------------------------
// Structure::updatevolatile

VolatileElement* Structure::updatevolatile(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (volatile_ != NULL)
        title = volatile_->getTitle();
    else {
        volatile_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return VolatileElement::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Structure::removevolatile

VolatileElement* Structure::removevolatile(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (volatile_ != NULL)
        title = volatile_->getTitle();
    else {
        volatile_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return VolatileElement::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Structure::openrlockvolatile

VolatileElement* Structure::openrlockvolatile(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (volatile_ != NULL)
        title = volatile_->getTitle();
    else {
        volatile_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return VolatileElement::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Structure::openvolatile

VolatileElement* Structure::openvolatile(DbResultCode& result, VolatileElement* dol)
{
    DbTitle* title;
    if (volatile_ != NULL)
        title = volatile_->getTitle();
    else {
        volatile_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return VolatileElement::open(title, result, OPEN, NULL);
        else
            return VolatileElement::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Structure::volatile

void Structure::volatile(VolatileElement* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (volatile_ &&  volatile_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete volatile_;
	if (data)
            volatile_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    volatile_ = DbTitleRef::nilRef();
    }
    else error("Structure::volatile");
}





//-----------------------------------------------------------------------
// Structure::prepare

DbResultCode Structure::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (volatile_ != NULL) {
        DbTitle* title = volatile_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            volatile_->prepare(theObject, &temp);  //byt namn
    }
    return DbEntity::prepare();
}


//-----------------------------------------------------------------------
// Structure::commit

void Structure::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (volatile_ != NULL) {
        volatile_->commit(theObject, 2);
	if (volatile_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete volatile_;
	volatile_ = NULL;
    }
    DbEntity::commit();
}


//-----------------------------------------------------------------------
// Structure::rollback

void Structure::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (volatile_)
	if (volatile_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete volatile_;
    volatile_ = NULL;
    DbEntity::rollback();
}


//-----------------------------------------------------------------------
// StructureIterator::StructureIterator

StructureIterator::StructureIterator()
{
    attrNumber = -1;
    index = -1;
}



//-----------------------------------------------------------------------
// StructureIterator::updateNext

Structure* StructureIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Structure* temp;
    while (TRUE) {
        result = dbmanager->iterate(Structure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Structure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Structure::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// StructureIterator::openrlockNext

Structure* StructureIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Structure* temp;
    while (TRUE) {
        result = dbmanager->iterate(Structure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Structure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Structure::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// StructureIterator::openNext

Structure* StructureIterator::openNext(DbResultCode& result, Structure* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Structure* temp;
    while (TRUE) {
        result = dbmanager->iterate(Structure_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Structure_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = Structure::open(&title, result, OPEN, NULL);
	else
            temp = Structure::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// StructureIterator::reset

void StructureIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
