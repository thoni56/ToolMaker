//============ PredefinedType.cc
//=======================================================================

#include "DOL.hh"
#include "PredefinedType.hh"




//-----------------------------------------------------------------------
// PredefinedType::create

PredefinedType* PredefinedType::create(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PredefinedType_CLASS_ID, &key, 32);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// PredefinedType::update

PredefinedType* PredefinedType::update(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PredefinedType_CLASS_ID, &key, 32);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// PredefinedType::remove

PredefinedType* PredefinedType::remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PredefinedType_CLASS_ID, &key, 32);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// PredefinedType::openrlock

PredefinedType* PredefinedType::openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PredefinedType_CLASS_ID, &key, 32);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// PredefinedType::open

PredefinedType* PredefinedType::open(Name key,
	DbResultCode& result,
	PredefinedType* dol)
{
    DbTitle title (PredefinedType_CLASS_ID, &key, 32);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// PredefinedType::getClassNo

int PredefinedType::getClassNo()
{
    return PredefinedType_CLASS_ID;
}


//-----------------------------------------------------------------------
// PredefinedType::getIterator

PredefinedTypeIterator* PredefinedType::getIterator()
{
    return new PredefinedTypeIterator;
}


//-----------------------------------------------------------------------
// PredefinedType::open

PredefinedType* PredefinedType::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (PredefinedType*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case PredefinedType_CLASS_ID:
	    return new PredefinedType (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// PredefinedType::open

PredefinedType* PredefinedType::open(DbTitle *title, DbResultCode& result, PredefinedType* dol)
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
// PredefinedType::PredefinedType

PredefinedType::PredefinedType(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    PredefinedType::init(op);
}


//-----------------------------------------------------------------------
// PredefinedType::init

void PredefinedType::init(DBOperation op)
{
    if (op == CREATE) {
    }
    int i = 0;
}


//-----------------------------------------------------------------------
// PredefinedType::name

Name PredefinedType::name(void) // get
{
    Name temp;
    name_.get(theObject, 0, temp);
    return temp;
}


//-----------------------------------------------------------------------
// PredefinedType::searchname

PredefinedTypeIterator* PredefinedType::searchname(Name value)
{
    return new PredefinedTypeIterator (0, (void*) &value, 32);
}





//-----------------------------------------------------------------------
// PredefinedType::prepare

DbResultCode PredefinedType::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// PredefinedType::commit

void PredefinedType::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// PredefinedType::rollback

void PredefinedType::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    DbAbstractObject::rollback();
}


//-----------------------------------------------------------------------
// PredefinedTypeIterator::PredefinedTypeIterator

PredefinedTypeIterator::PredefinedTypeIterator()
{
    attrNumber = -1;
    index = -1;
}


//-----------------------------------------------------------------------
// PredefinedTypeIterator::PredefinedTypeIterator

PredefinedTypeIterator::PredefinedTypeIterator(AttributeIndex attr, void* value, int length)
{
    attrNumber = attr;
    memcpy(searchValue, value, length);
    index = -1;
}


//-----------------------------------------------------------------------
// PredefinedTypeIterator::updateNext

PredefinedType* PredefinedTypeIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PredefinedType* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(PredefinedType_CLASS_ID, index, object);
        else 
            result = dbmanager->search(PredefinedType_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PredefinedType_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = PredefinedType::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PredefinedTypeIterator::openrlockNext

PredefinedType* PredefinedTypeIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PredefinedType* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(PredefinedType_CLASS_ID, index, object);
        else 
            result = dbmanager->search(PredefinedType_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PredefinedType_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = PredefinedType::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PredefinedTypeIterator::openNext

PredefinedType* PredefinedTypeIterator::openNext(DbResultCode& result, PredefinedType* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PredefinedType* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(PredefinedType_CLASS_ID, index, object);
        else 
           result = dbmanager->search(PredefinedType_CLASS_ID, attrNumber,
				      index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PredefinedType_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = PredefinedType::open(&title, result, OPEN, NULL);
	else
            temp = PredefinedType::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PredefinedTypeIterator::reset

void PredefinedTypeIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
