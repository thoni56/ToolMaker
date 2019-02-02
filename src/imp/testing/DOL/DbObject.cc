//============ DbObject.cc
//=======================================================================

#include "DOL.hh"
#include "DbObject.hh"

// Include subclasses:
#include "Class.hh"
#include "Relation.hh"



//-----------------------------------------------------------------------
// DbObject::create

DbObject* DbObject::create(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DbObject_CLASS_ID, &key, 32);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// DbObject::update

DbObject* DbObject::update(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DbObject_CLASS_ID, &key, 32);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// DbObject::remove

DbObject* DbObject::remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DbObject_CLASS_ID, &key, 32);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// DbObject::openrlock

DbObject* DbObject::openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DbObject_CLASS_ID, &key, 32);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// DbObject::open

DbObject* DbObject::open(Name key,
	DbResultCode& result,
	DbObject* dol)
{
    DbTitle title (DbObject_CLASS_ID, &key, 32);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// DbObject::getClassNo

int DbObject::getClassNo()
{
    return DbObject_CLASS_ID;
}


//-----------------------------------------------------------------------
// DbObject::getIterator

DbObjectIterator* DbObject::getIterator()
{
    return new DbObjectIterator;
}


//-----------------------------------------------------------------------
// DbObject::open

DbObject* DbObject::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (DbObject*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case DbObject_CLASS_ID:
	    return new DbObject (object, tempObject, op, trId, title);
	case Class_CLASS_ID:
	    return (DbObject*) new Class (object, tempObject, op, trId, title);
	case Relation_CLASS_ID:
	    return (DbObject*) new Relation (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// DbObject::open

DbObject* DbObject::open(DbTitle *title, DbResultCode& result, DbObject* dol)
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
// DbObject::DbObject

DbObject::DbObject(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    DbObject::init(op);
}


//-----------------------------------------------------------------------
// DbObject::init

void DbObject::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	DbEntity::init(op);
    if (op == CREATE) {
    }
    int i = 0;
}




//-----------------------------------------------------------------------
// DbObject::prepare

DbResultCode DbObject::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return DbEntity::prepare();
}


//-----------------------------------------------------------------------
// DbObject::commit

void DbObject::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    DbEntity::commit();
}


//-----------------------------------------------------------------------
// DbObject::rollback

void DbObject::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    DbEntity::rollback();
}


//-----------------------------------------------------------------------
// DbObjectIterator::DbObjectIterator

DbObjectIterator::DbObjectIterator()
{
    attrNumber = -1;
    index = -1;
}



//-----------------------------------------------------------------------
// DbObjectIterator::updateNext

DbObject* DbObjectIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DbObject* temp;
    while (TRUE) {
        result = dbmanager->iterate(DbObject_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DbObject_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = DbObject::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DbObjectIterator::openrlockNext

DbObject* DbObjectIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DbObject* temp;
    while (TRUE) {
        result = dbmanager->iterate(DbObject_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DbObject_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = DbObject::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DbObjectIterator::openNext

DbObject* DbObjectIterator::openNext(DbResultCode& result, DbObject* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DbObject* temp;
    while (TRUE) {
        result = dbmanager->iterate(DbObject_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DbObject_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = DbObject::open(&title, result, OPEN, NULL);
	else
            temp = DbObject::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DbObjectIterator::reset

void DbObjectIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
