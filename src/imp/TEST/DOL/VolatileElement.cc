//============ VolatileElement.cc
//=======================================================================

#include "DOL.hh"
#include "VolatileElement.hh"




//-----------------------------------------------------------------------
// VolatileElement::create

VolatileElement* VolatileElement::create(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (VolatileElement_CLASS_ID, &key, 64);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// VolatileElement::update

VolatileElement* VolatileElement::update(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (VolatileElement_CLASS_ID, &key, 64);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// VolatileElement::remove

VolatileElement* VolatileElement::remove(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (VolatileElement_CLASS_ID, &key, 64);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// VolatileElement::openrlock

VolatileElement* VolatileElement::openrlock(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (VolatileElement_CLASS_ID, &key, 64);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// VolatileElement::open

VolatileElement* VolatileElement::open(UniqueName key,
	DbResultCode& result,
	VolatileElement* dol)
{
    DbTitle title (VolatileElement_CLASS_ID, &key, 64);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// VolatileElement::getClassNo

int VolatileElement::getClassNo()
{
    return VolatileElement_CLASS_ID;
}


//-----------------------------------------------------------------------
// VolatileElement::getIterator

VolatileElementIterator* VolatileElement::getIterator()
{
    return new VolatileElementIterator;
}


//-----------------------------------------------------------------------
// VolatileElement::open

VolatileElement* VolatileElement::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (VolatileElement*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case VolatileElement_CLASS_ID:
	    return new VolatileElement (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// VolatileElement::open

VolatileElement* VolatileElement::open(DbTitle *title, DbResultCode& result, VolatileElement* dol)
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
// VolatileElement::VolatileElement

VolatileElement::VolatileElement(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    VolatileElement::init(op);
}


//-----------------------------------------------------------------------
// VolatileElement::init

void VolatileElement::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	Element::init(op);
    if (op == CREATE) {
    }
    int i = 0;
}


//-----------------------------------------------------------------------
// VolatileElement::type

Name VolatileElement::type(void) // get
{
    Name temp;
    type_.get(theObject, 2, temp);
    return temp;
}


//-----------------------------------------------------------------------
// VolatileElement::type

void VolatileElement::type(Name data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        type_.set(theObject, 2, data);
    }
    else error("VolatileElement::type");
}

//-----------------------------------------------------------------------
// VolatileElement::searchtype

VolatileElementIterator* VolatileElement::searchtype(Name value)
{
    return new VolatileElementIterator (2, (void*) &value, 32);
}





//-----------------------------------------------------------------------
// VolatileElement::prepare

DbResultCode VolatileElement::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    return Element::prepare();
}


//-----------------------------------------------------------------------
// VolatileElement::commit

void VolatileElement::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    Element::commit();
}


//-----------------------------------------------------------------------
// VolatileElement::rollback

void VolatileElement::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    Element::rollback();
}


//-----------------------------------------------------------------------
// VolatileElementIterator::VolatileElementIterator

VolatileElementIterator::VolatileElementIterator()
{
    attrNumber = -1;
    index = -1;
}


//-----------------------------------------------------------------------
// VolatileElementIterator::VolatileElementIterator

VolatileElementIterator::VolatileElementIterator(AttributeIndex attr, void* value, int length)
{
    attrNumber = attr;
    memcpy(searchValue, value, length);
    index = -1;
}


//-----------------------------------------------------------------------
// VolatileElementIterator::updateNext

VolatileElement* VolatileElementIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    VolatileElement* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(VolatileElement_CLASS_ID, index, object);
        else 
            result = dbmanager->search(VolatileElement_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (VolatileElement_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = VolatileElement::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// VolatileElementIterator::openrlockNext

VolatileElement* VolatileElementIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    VolatileElement* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(VolatileElement_CLASS_ID, index, object);
        else 
            result = dbmanager->search(VolatileElement_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (VolatileElement_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = VolatileElement::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// VolatileElementIterator::openNext

VolatileElement* VolatileElementIterator::openNext(DbResultCode& result, VolatileElement* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    VolatileElement* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(VolatileElement_CLASS_ID, index, object);
        else 
           result = dbmanager->search(VolatileElement_CLASS_ID, attrNumber,
				      index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (VolatileElement_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = VolatileElement::open(&title, result, OPEN, NULL);
	else
            temp = VolatileElement::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// VolatileElementIterator::reset

void VolatileElementIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
