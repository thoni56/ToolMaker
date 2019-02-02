//============ DbEntity.cc
//=======================================================================

#include "DOL.hh"
#include "DbEntity.hh"

// Include subclasses:
#include "DbObject.hh"
#include "Class.hh"
#include "Relation.hh"
#include "Structure.hh"
#include "PersistentStructure.hh"
#include "DynamicStructure.hh"

// Include referenced classes:
#include "DynamicString.hh"


//-----------------------------------------------------------------------
// DbEntity::create

DbEntity* DbEntity::create(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DbEntity_CLASS_ID, &key, 32);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// DbEntity::update

DbEntity* DbEntity::update(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DbEntity_CLASS_ID, &key, 32);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// DbEntity::remove

DbEntity* DbEntity::remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DbEntity_CLASS_ID, &key, 32);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// DbEntity::openrlock

DbEntity* DbEntity::openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (DbEntity_CLASS_ID, &key, 32);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// DbEntity::open

DbEntity* DbEntity::open(Name key,
	DbResultCode& result,
	DbEntity* dol)
{
    DbTitle title (DbEntity_CLASS_ID, &key, 32);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// DbEntity::getClassNo

int DbEntity::getClassNo()
{
    return DbEntity_CLASS_ID;
}


//-----------------------------------------------------------------------
// DbEntity::getIterator

DbEntityIterator* DbEntity::getIterator()
{
    return new DbEntityIterator;
}


//-----------------------------------------------------------------------
// DbEntity::open

DbEntity* DbEntity::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (DbEntity*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case DbEntity_CLASS_ID:
	    return new DbEntity (object, tempObject, op, trId, title);
	case DbObject_CLASS_ID:
	    return (DbEntity*) new DbObject (object, tempObject, op, trId, title);
	case Class_CLASS_ID:
	    return (DbEntity*) new Class (object, tempObject, op, trId, title);
	case Relation_CLASS_ID:
	    return (DbEntity*) new Relation (object, tempObject, op, trId, title);
	case Structure_CLASS_ID:
	    return (DbEntity*) new Structure (object, tempObject, op, trId, title);
	case PersistentStructure_CLASS_ID:
	    return (DbEntity*) new PersistentStructure (object, tempObject, op, trId, title);
	case DynamicStructure_CLASS_ID:
	    return (DbEntity*) new DynamicStructure (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// DbEntity::open

DbEntity* DbEntity::open(DbTitle *title, DbResultCode& result, DbEntity* dol)
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
// DbEntity::DbEntity

DbEntity::DbEntity(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    DbEntity::init(op);
}


//-----------------------------------------------------------------------
// DbEntity::init

void DbEntity::init(DBOperation op)
{
    if (op == CREATE) {
    }
    int i = 0;
    version_ = NULL;
}


//-----------------------------------------------------------------------
// DbEntity::name

Name DbEntity::name(void) // get
{
    Name temp;
    name_.get(theObject, 0, temp);
    return temp;
}


//-----------------------------------------------------------------------
// DbEntity::searchname

DbEntityIterator* DbEntity::searchname(Name value)
{
    return new DbEntityIterator (0, (void*) &value, 32);
}



//-----------------------------------------------------------------------
// DbEntity::updateversion

DynamicString* DbEntity::updateversion(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (version_ != NULL)
        title = version_->getTitle();
    else {
        version_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return DynamicString::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// DbEntity::removeversion

DynamicString* DbEntity::removeversion(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (version_ != NULL)
        title = version_->getTitle();
    else {
        version_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return DynamicString::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// DbEntity::openrlockversion

DynamicString* DbEntity::openrlockversion(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (version_ != NULL)
        title = version_->getTitle();
    else {
        version_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return DynamicString::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// DbEntity::openversion

DynamicString* DbEntity::openversion(DbResultCode& result, DynamicString* dol)
{
    DbTitle* title;
    if (version_ != NULL)
        title = version_->getTitle();
    else {
        version_->get(theObject, 1, title);
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
// DbEntity::version

void DbEntity::version(DynamicString* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (version_ &&  version_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete version_;
	if (data)
            version_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    version_ = DbTitleRef::nilRef();
    }
    else error("DbEntity::version");
}





//-----------------------------------------------------------------------
// DbEntity::prepare

DbResultCode DbEntity::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (version_ != NULL) {
        DbTitle* title = version_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            version_->prepare(theObject, &temp);  //byt namn
    }
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// DbEntity::commit

void DbEntity::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (version_ != NULL) {
        version_->commit(theObject, 1);
	if (version_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete version_;
	version_ = NULL;
    }
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// DbEntity::rollback

void DbEntity::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (version_)
	if (version_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete version_;
    version_ = NULL;
    DbAbstractObject::rollback();
}


//-----------------------------------------------------------------------
// DbEntityIterator::DbEntityIterator

DbEntityIterator::DbEntityIterator()
{
    attrNumber = -1;
    index = -1;
}


//-----------------------------------------------------------------------
// DbEntityIterator::DbEntityIterator

DbEntityIterator::DbEntityIterator(AttributeIndex attr, void* value, int length)
{
    attrNumber = attr;
    memcpy(searchValue, value, length);
    index = -1;
}


//-----------------------------------------------------------------------
// DbEntityIterator::updateNext

DbEntity* DbEntityIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DbEntity* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(DbEntity_CLASS_ID, index, object);
        else 
            result = dbmanager->search(DbEntity_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DbEntity_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = DbEntity::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DbEntityIterator::openrlockNext

DbEntity* DbEntityIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DbEntity* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(DbEntity_CLASS_ID, index, object);
        else 
            result = dbmanager->search(DbEntity_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DbEntity_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = DbEntity::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DbEntityIterator::openNext

DbEntity* DbEntityIterator::openNext(DbResultCode& result, DbEntity* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    DbEntity* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(DbEntity_CLASS_ID, index, object);
        else 
           result = dbmanager->search(DbEntity_CLASS_ID, attrNumber,
				      index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (DbEntity_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = DbEntity::open(&title, result, OPEN, NULL);
	else
            temp = DbEntity::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// DbEntityIterator::reset

void DbEntityIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
