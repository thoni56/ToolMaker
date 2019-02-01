//============ PersistentElement.cc
//=======================================================================

#include "DOL.hh"
#include "PersistentElement.hh"


// Include referenced classes:
#include "PredefinedType.hh"


//-----------------------------------------------------------------------
// PersistentElement::create

PersistentElement* PersistentElement::create(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PersistentElement_CLASS_ID, &key, 64);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// PersistentElement::update

PersistentElement* PersistentElement::update(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PersistentElement_CLASS_ID, &key, 64);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// PersistentElement::remove

PersistentElement* PersistentElement::remove(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PersistentElement_CLASS_ID, &key, 64);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// PersistentElement::openrlock

PersistentElement* PersistentElement::openrlock(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (PersistentElement_CLASS_ID, &key, 64);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// PersistentElement::open

PersistentElement* PersistentElement::open(UniqueName key,
	DbResultCode& result,
	PersistentElement* dol)
{
    DbTitle title (PersistentElement_CLASS_ID, &key, 64);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// PersistentElement::getClassNo

int PersistentElement::getClassNo()
{
    return PersistentElement_CLASS_ID;
}


//-----------------------------------------------------------------------
// PersistentElement::getIterator

PersistentElementIterator* PersistentElement::getIterator()
{
    return new PersistentElementIterator;
}


//-----------------------------------------------------------------------
// PersistentElement::open

PersistentElement* PersistentElement::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (PersistentElement*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case PersistentElement_CLASS_ID:
	    return new PersistentElement (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// PersistentElement::open

PersistentElement* PersistentElement::open(DbTitle *title, DbResultCode& result, PersistentElement* dol)
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
// PersistentElement::PersistentElement

PersistentElement::PersistentElement(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    PersistentElement::init(op);
}


//-----------------------------------------------------------------------
// PersistentElement::init

void PersistentElement::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	Element::init(op);
    if (op == CREATE) {
    }
    int i = 0;
    type_ = NULL;
}


//-----------------------------------------------------------------------
// PersistentElement::updatetype

PredefinedType* PersistentElement::updatetype(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (type_ != NULL)
        title = type_->getTitle();
    else {
        type_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return PredefinedType::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// PersistentElement::removetype

PredefinedType* PersistentElement::removetype(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (type_ != NULL)
        title = type_->getTitle();
    else {
        type_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return PredefinedType::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// PersistentElement::openrlocktype

PredefinedType* PersistentElement::openrlocktype(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (type_ != NULL)
        title = type_->getTitle();
    else {
        type_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return PredefinedType::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// PersistentElement::opentype

PredefinedType* PersistentElement::opentype(DbResultCode& result, PredefinedType* dol)
{
    DbTitle* title;
    if (type_ != NULL)
        title = type_->getTitle();
    else {
        type_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return PredefinedType::open(title, result, OPEN, NULL);
        else
            return PredefinedType::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// PersistentElement::type

void PersistentElement::type(PredefinedType* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (type_ &&  type_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete type_;
	if (data)
            type_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    type_ = DbTitleRef::nilRef();
    }
    else error("PersistentElement::type");
}



//-----------------------------------------------------------------------
// PersistentElement::size

Integer PersistentElement::size(void) // get
{
    Integer temp;
    size_.get(theObject, 3, temp);
    return temp;
}


//-----------------------------------------------------------------------
// PersistentElement::size

void PersistentElement::size(Integer data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        size_.set(theObject, 3, data);
    }
    else error("PersistentElement::size");
}

//-----------------------------------------------------------------------
// PersistentElement::searchsize

PersistentElementIterator* PersistentElement::searchsize(Integer value)
{
    return new PersistentElementIterator (3, (void*) &value, 4);
}





//-----------------------------------------------------------------------
// PersistentElement::prepare

DbResultCode PersistentElement::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (type_ != NULL) {
        DbTitle* title = type_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            type_->prepare(theObject, &temp);  //byt namn
    }
    return Element::prepare();
}


//-----------------------------------------------------------------------
// PersistentElement::commit

void PersistentElement::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (type_ != NULL) {
        type_->commit(theObject, 2);
	if (type_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete type_;
	type_ = NULL;
    }
    Element::commit();
}


//-----------------------------------------------------------------------
// PersistentElement::rollback

void PersistentElement::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (type_)
	if (type_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete type_;
    type_ = NULL;
    Element::rollback();
}


//-----------------------------------------------------------------------
// PersistentElementIterator::PersistentElementIterator

PersistentElementIterator::PersistentElementIterator()
{
    attrNumber = -1;
    index = -1;
}


//-----------------------------------------------------------------------
// PersistentElementIterator::PersistentElementIterator

PersistentElementIterator::PersistentElementIterator(AttributeIndex attr, void* value, int length)
{
    attrNumber = attr;
    memcpy(searchValue, value, length);
    index = -1;
}


//-----------------------------------------------------------------------
// PersistentElementIterator::updateNext

PersistentElement* PersistentElementIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PersistentElement* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(PersistentElement_CLASS_ID, index, object);
        else 
            result = dbmanager->search(PersistentElement_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PersistentElement_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = PersistentElement::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PersistentElementIterator::openrlockNext

PersistentElement* PersistentElementIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PersistentElement* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(PersistentElement_CLASS_ID, index, object);
        else 
            result = dbmanager->search(PersistentElement_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PersistentElement_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = PersistentElement::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PersistentElementIterator::openNext

PersistentElement* PersistentElementIterator::openNext(DbResultCode& result, PersistentElement* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    PersistentElement* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(PersistentElement_CLASS_ID, index, object);
        else 
           result = dbmanager->search(PersistentElement_CLASS_ID, attrNumber,
				      index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (PersistentElement_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = PersistentElement::open(&title, result, OPEN, NULL);
	else
            temp = PersistentElement::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// PersistentElementIterator::reset

void PersistentElementIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
