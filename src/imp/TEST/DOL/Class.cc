//============ Class.cc
//=======================================================================

#include "DOL.hh"
#include "Class.hh"


// Include referenced classes:
#include "keySpecifikation.hh"
#include "ClassAttributes.hh"


//-----------------------------------------------------------------------
// Class::create

Class* Class::create(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Class_CLASS_ID, &key, 32);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// Class::update

Class* Class::update(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Class_CLASS_ID, &key, 32);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// Class::remove

Class* Class::remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Class_CLASS_ID, &key, 32);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// Class::openrlock

Class* Class::openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Class_CLASS_ID, &key, 32);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// Class::open

Class* Class::open(Name key,
	DbResultCode& result,
	Class* dol)
{
    DbTitle title (Class_CLASS_ID, &key, 32);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// Class::getClassNo

int Class::getClassNo()
{
    return Class_CLASS_ID;
}


//-----------------------------------------------------------------------
// Class::getIterator

ClassIterator* Class::getIterator()
{
    return new ClassIterator;
}


//-----------------------------------------------------------------------
// Class::open

Class* Class::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (Class*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case Class_CLASS_ID:
	    return new Class (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// Class::open

Class* Class::open(DbTitle *title, DbResultCode& result, Class* dol)
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
// Class::Class

Class::Class(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    Class::init(op);
}


//-----------------------------------------------------------------------
// Class::init

void Class::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	DbObject::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
    primaryKey_ = NULL;
    base_ = NULL;
    attributes_ = NULL;
}


//-----------------------------------------------------------------------
// Class::updateprimaryKey

keySpecifikation* Class::updateprimaryKey(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (primaryKey_ != NULL)
        title = primaryKey_->getTitle();
    else {
        primaryKey_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return keySpecifikation::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Class::removeprimaryKey

keySpecifikation* Class::removeprimaryKey(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (primaryKey_ != NULL)
        title = primaryKey_->getTitle();
    else {
        primaryKey_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return keySpecifikation::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Class::openrlockprimaryKey

keySpecifikation* Class::openrlockprimaryKey(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (primaryKey_ != NULL)
        title = primaryKey_->getTitle();
    else {
        primaryKey_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return keySpecifikation::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Class::openprimaryKey

keySpecifikation* Class::openprimaryKey(DbResultCode& result, keySpecifikation* dol)
{
    DbTitle* title;
    if (primaryKey_ != NULL)
        title = primaryKey_->getTitle();
    else {
        primaryKey_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return keySpecifikation::open(title, result, OPEN, NULL);
        else
            return keySpecifikation::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Class::primaryKey

void Class::primaryKey(keySpecifikation* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (primaryKey_ &&  primaryKey_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete primaryKey_;
	if (data)
            primaryKey_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    primaryKey_ = DbTitleRef::nilRef();
    }
    else error("Class::primaryKey");
}



//-----------------------------------------------------------------------
// Class::allocate

Boolean Class::allocate(void) // get
{
    Boolean temp;
    allocate_.get(theObject, 3, temp);
    return temp;
}


//-----------------------------------------------------------------------
// Class::allocate

void Class::allocate(Boolean data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        allocate_.set(theObject, 3, data);
    }
    else error("Class::allocate");
}

//-----------------------------------------------------------------------
// Class::searchallocate

ClassIterator* Class::searchallocate(Boolean value)
{
    return new ClassIterator (3, (void*) &value, 1);
}



//-----------------------------------------------------------------------
// Class::updatebase

Class* Class::updatebase(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (base_ != NULL)
        title = base_->getTitle();
    else {
        base_->get(theObject, 4, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return Class::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Class::removebase

Class* Class::removebase(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (base_ != NULL)
        title = base_->getTitle();
    else {
        base_->get(theObject, 4, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Class::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Class::openrlockbase

Class* Class::openrlockbase(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (base_ != NULL)
        title = base_->getTitle();
    else {
        base_->get(theObject, 4, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Class::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Class::openbase

Class* Class::openbase(DbResultCode& result, Class* dol)
{
    DbTitle* title;
    if (base_ != NULL)
        title = base_->getTitle();
    else {
        base_->get(theObject, 4, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return Class::open(title, result, OPEN, NULL);
        else
            return Class::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Class::base

void Class::base(Class* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (base_ &&  base_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete base_;
	if (data)
            base_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    base_ = DbTitleRef::nilRef();
    }
    else error("Class::base");
}



//-----------------------------------------------------------------------
// Class::createattributes

ClassAttributes* Class::createattributes(DbResultCode& result)

{
   if (operation != CREATE && operation != UPDATE) {
	result = FAILED;
	return NULL;
   }
   return attributes_ = new ClassAttributes (ClassAttributes_CLASS_ID, this, result);
}

//-----------------------------------------------------------------------
// Class::openattributes

ClassAttributes* Class::openattributes(DbResultCode& result)
{
   if (attributes_ != NULL) {
      result = SUCCEEDED;
      return attributes_;
   }
   else {
      char* buf = new char[2*sizeof(int)];
      theObject->getValue(5, buf);
      LocalReferense* ref = (LocalReferense*) buf;
      if (ref->clid == 0 && ref->lid == 0) {    // 4f - Nil reference
	 result = OBJECT_NOT_FOUND;
         return NULL;   	
      }
      DbTitle* title = new DbTitle(-1, -1, ref->clid, ref->lid);
      return attributes_ = new ClassAttributes (title, operation, this, result);
   }
}







//-----------------------------------------------------------------------
// Class::prepare

DbResultCode Class::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (primaryKey_ != NULL) {
        DbTitle* title = primaryKey_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            primaryKey_->prepare(theObject, &temp);  //byt namn
    }
    if (base_ != NULL) {
        DbTitle* title = base_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            base_->prepare(theObject, &temp);  //byt namn
    }
    if (attributes_ != NULL) {
        result = attributes_->prepare();
        if (result != SUCCEEDED)
            return result;
    }   
    return DbObject::prepare();
}


//-----------------------------------------------------------------------
// Class::commit

void Class::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (primaryKey_ != NULL) {
        primaryKey_->commit(theObject, 2);
	if (primaryKey_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete primaryKey_;
	primaryKey_ = NULL;
    }
    if (base_ != NULL) {
        base_->commit(theObject, 4);
	if (base_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete base_;
	base_ = NULL;
    }
    if (attributes_ != NULL) {
        title = attributes_->commitSubObject();
        if (title != NULL)
            theObject->putValue(5, title);
    }
    attributes_ = NULL;
    DbObject::commit();
}


//-----------------------------------------------------------------------
// Class::rollback

void Class::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (primaryKey_)
	if (primaryKey_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete primaryKey_;
    primaryKey_ = NULL;
    if (base_)
	if (base_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete base_;
    base_ = NULL;
    if (attributes_ != NULL)
        attributes_->rollbackSubObject();
    attributes_ = NULL;
    DbObject::rollback();
}


//-----------------------------------------------------------------------
// ClassIterator::ClassIterator

ClassIterator::ClassIterator()
{
    attrNumber = -1;
    index = -1;
}


//-----------------------------------------------------------------------
// ClassIterator::ClassIterator

ClassIterator::ClassIterator(AttributeIndex attr, void* value, int length)
{
    attrNumber = attr;
    memcpy(searchValue, value, length);
    index = -1;
}


//-----------------------------------------------------------------------
// ClassIterator::updateNext

Class* ClassIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Class* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Class_CLASS_ID, index, object);
        else 
            result = dbmanager->search(Class_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Class_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Class::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// ClassIterator::openrlockNext

Class* ClassIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Class* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Class_CLASS_ID, index, object);
        else 
            result = dbmanager->search(Class_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Class_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Class::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// ClassIterator::openNext

Class* ClassIterator::openNext(DbResultCode& result, Class* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Class* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Class_CLASS_ID, index, object);
        else 
           result = dbmanager->search(Class_CLASS_ID, attrNumber,
				      index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Class_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = Class::open(&title, result, OPEN, NULL);
	else
            temp = Class::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// ClassIterator::reset

void ClassIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
