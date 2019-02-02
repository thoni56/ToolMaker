//============ Element.cc
//=======================================================================

#include "DOL.hh"
#include "Element.hh"

// Include subclasses:
#include "PersistentElement.hh"
#include "VolatileElement.hh"

// Include referenced classes:


//-----------------------------------------------------------------------
// Element::create

Element* Element::create(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Element_CLASS_ID, &key, 64);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// Element::update

Element* Element::update(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Element_CLASS_ID, &key, 64);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// Element::remove

Element* Element::remove(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Element_CLASS_ID, &key, 64);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// Element::openrlock

Element* Element::openrlock(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Element_CLASS_ID, &key, 64);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// Element::open

Element* Element::open(UniqueName key,
	DbResultCode& result,
	Element* dol)
{
    DbTitle title (Element_CLASS_ID, &key, 64);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// Element::getClassNo

int Element::getClassNo()
{
    return Element_CLASS_ID;
}


//-----------------------------------------------------------------------
// Element::getIterator

ElementIterator* Element::getIterator()
{
    return new ElementIterator;
}


//-----------------------------------------------------------------------
// Element::open

Element* Element::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (Element*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case Element_CLASS_ID:
	    return new Element (object, tempObject, op, trId, title);
	case PersistentElement_CLASS_ID:
	    return (Element*) new PersistentElement (object, tempObject, op, trId, title);
	case VolatileElement_CLASS_ID:
	    return (Element*) new VolatileElement (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// Element::open

Element* Element::open(DbTitle *title, DbResultCode& result, Element* dol)
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
// Element::Element

Element::Element(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    Element::init(op);
}


//-----------------------------------------------------------------------
// Element::init

void Element::init(DBOperation op)
{
    if (op == CREATE) {
        // next_ = DbTitleRef::nilRef();    // 4f - Nil reference
    }
    int i = 0;
    next_ = NULL;
}


//-----------------------------------------------------------------------
// Element::name

UniqueName Element::name(void) // get
{
    UniqueName temp;
    name_.get(theObject, 0, temp);
    return temp;
}


//-----------------------------------------------------------------------
// Element::searchname

ElementIterator* Element::searchname(UniqueName value)
{
    return new ElementIterator (0, (void*) &value, 64);
}



//-----------------------------------------------------------------------
// Element::updatenext

Element* Element::updatenext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return Element::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Element::removenext

Element* Element::removenext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Element::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Element::openrlocknext

Element* Element::openrlocknext(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Element::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Element::opennext

Element* Element::opennext(DbResultCode& result, Element* dol)
{
    DbTitle* title;
    if (next_ != NULL)
        title = next_->getTitle();
    else {
        next_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return Element::open(title, result, OPEN, NULL);
        else
            return Element::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Element::next

void Element::next(Element* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (next_ &&  next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete next_;
	if (data)
            next_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    next_ = DbTitleRef::nilRef();
    }
    else error("Element::next");
}





//-----------------------------------------------------------------------
// Element::prepare

DbResultCode Element::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (next_ != NULL) {
        DbTitle* title = next_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            next_->prepare(theObject, &temp);  //byt namn
    }
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// Element::commit

void Element::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (next_ != NULL) {
        next_->commit(theObject, 1);
	if (next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete next_;
	next_ = NULL;
    }
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// Element::rollback

void Element::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (next_)
	if (next_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete next_;
    next_ = NULL;
    DbAbstractObject::rollback();
}


//-----------------------------------------------------------------------
// ElementIterator::ElementIterator

ElementIterator::ElementIterator()
{
    attrNumber = -1;
    index = -1;
}


//-----------------------------------------------------------------------
// ElementIterator::ElementIterator

ElementIterator::ElementIterator(AttributeIndex attr, void* value, int length)
{
    attrNumber = attr;
    memcpy(searchValue, value, length);
    index = -1;
}


//-----------------------------------------------------------------------
// ElementIterator::updateNext

Element* ElementIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Element* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Element_CLASS_ID, index, object);
        else 
            result = dbmanager->search(Element_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Element_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Element::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// ElementIterator::openrlockNext

Element* ElementIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Element* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Element_CLASS_ID, index, object);
        else 
            result = dbmanager->search(Element_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Element_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Element::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// ElementIterator::openNext

Element* ElementIterator::openNext(DbResultCode& result, Element* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Element* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Element_CLASS_ID, index, object);
        else 
           result = dbmanager->search(Element_CLASS_ID, attrNumber,
				      index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Element_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = Element::open(&title, result, OPEN, NULL);
	else
            temp = Element::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// ElementIterator::reset

void ElementIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
