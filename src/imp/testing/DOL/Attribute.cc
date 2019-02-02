//============ Attribute.cc
//=======================================================================

#include "DOL.hh"
#include "Attribute.hh"


// Include referenced classes:
#include "AttributeType.hh"
#include "AttributeProperty.hh"


//-----------------------------------------------------------------------
// Attribute::create

Attribute* Attribute::create(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Attribute_CLASS_ID, &key, 64);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// Attribute::update

Attribute* Attribute::update(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Attribute_CLASS_ID, &key, 64);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// Attribute::remove

Attribute* Attribute::remove(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Attribute_CLASS_ID, &key, 64);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// Attribute::openrlock

Attribute* Attribute::openrlock(UniqueName key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Attribute_CLASS_ID, &key, 64);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// Attribute::open

Attribute* Attribute::open(UniqueName key,
	DbResultCode& result,
	Attribute* dol)
{
    DbTitle title (Attribute_CLASS_ID, &key, 64);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// Attribute::getClassNo

int Attribute::getClassNo()
{
    return Attribute_CLASS_ID;
}


//-----------------------------------------------------------------------
// Attribute::getIterator

AttributeIterator* Attribute::getIterator()
{
    return new AttributeIterator;
}


//-----------------------------------------------------------------------
// Attribute::open

Attribute* Attribute::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (Attribute*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case Attribute_CLASS_ID:
	    return new Attribute (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// Attribute::open

Attribute* Attribute::open(DbTitle *title, DbResultCode& result, Attribute* dol)
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
// Attribute::Attribute

Attribute::Attribute(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    Attribute::init(op);
}


//-----------------------------------------------------------------------
// Attribute::init

void Attribute::init(DBOperation op)
{
    if (op == CREATE) {
    }
    int i = 0;
    type_ = NULL;
    properties_ = NULL;
}


//-----------------------------------------------------------------------
// Attribute::name

UniqueName Attribute::name(void) // get
{
    UniqueName temp;
    name_.get(theObject, 0, temp);
    return temp;
}


//-----------------------------------------------------------------------
// Attribute::searchname

AttributeIterator* Attribute::searchname(UniqueName value)
{
    return new AttributeIterator (0, (void*) &value, 64);
}



//-----------------------------------------------------------------------
// Attribute::updatetype

AttributeType* Attribute::updatetype(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (type_ != NULL)
        title = type_->getTitle();
    else {
        type_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return AttributeType::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Attribute::removetype

AttributeType* Attribute::removetype(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (type_ != NULL)
        title = type_->getTitle();
    else {
        type_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return AttributeType::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Attribute::openrlocktype

AttributeType* Attribute::openrlocktype(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (type_ != NULL)
        title = type_->getTitle();
    else {
        type_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return AttributeType::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Attribute::opentype

AttributeType* Attribute::opentype(DbResultCode& result, AttributeType* dol)
{
    DbTitle* title;
    if (type_ != NULL)
        title = type_->getTitle();
    else {
        type_->get(theObject, 1, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return AttributeType::open(title, result, OPEN, NULL);
        else
            return AttributeType::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Attribute::type

void Attribute::type(AttributeType* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (type_ &&  type_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete type_;
	if (data)
            type_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    type_ = DbTitleRef::nilRef();
    }
    else error("Attribute::type");
}



//-----------------------------------------------------------------------
// Attribute::updateproperties

AttributeProperty* Attribute::updateproperties(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (properties_ != NULL)
        title = properties_->getTitle();
    else {
        properties_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return AttributeProperty::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Attribute::removeproperties

AttributeProperty* Attribute::removeproperties(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (properties_ != NULL)
        title = properties_->getTitle();
    else {
        properties_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return AttributeProperty::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Attribute::openrlockproperties

AttributeProperty* Attribute::openrlockproperties(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (properties_ != NULL)
        title = properties_->getTitle();
    else {
        properties_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return AttributeProperty::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Attribute::openproperties

AttributeProperty* Attribute::openproperties(DbResultCode& result, AttributeProperty* dol)
{
    DbTitle* title;
    if (properties_ != NULL)
        title = properties_->getTitle();
    else {
        properties_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0) {     // 4f - Nil reference
        if (dol == NULL)
	    return AttributeProperty::open(title, result, OPEN, NULL);
        else
            return AttributeProperty::open(title, result, dol);
    }
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Attribute::properties

void Attribute::properties(AttributeProperty* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (properties_ &&  properties_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete properties_;
	if (data)
            properties_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    properties_ = DbTitleRef::nilRef();
    }
    else error("Attribute::properties");
}



//-----------------------------------------------------------------------
// Attribute::attributeIdentity

Integer Attribute::attributeIdentity(void) // get
{
    Integer temp;
    attributeIdentity_.get(theObject, 3, temp);
    return temp;
}


//-----------------------------------------------------------------------
// Attribute::attributeIdentity

void Attribute::attributeIdentity(Integer data) // set
{
    if (operation == UPDATE || operation == CREATE) {
        attributeIdentity_.set(theObject, 3, data);
    }
    else error("Attribute::attributeIdentity");
}

//-----------------------------------------------------------------------
// Attribute::searchattributeIdentity

AttributeIterator* Attribute::searchattributeIdentity(Integer value)
{
    return new AttributeIterator (3, (void*) &value, 4);
}





//-----------------------------------------------------------------------
// Attribute::prepare

DbResultCode Attribute::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (type_ != NULL) {
        DbTitle* title = type_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            type_->prepare(theObject, &temp);  //byt namn
    }
    if (properties_ != NULL) {
        DbTitle* title = properties_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            properties_->prepare(theObject, &temp);  //byt namn
    }
    return DbAbstractObject::prepare();
}


//-----------------------------------------------------------------------
// Attribute::commit

void Attribute::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (type_ != NULL) {
        type_->commit(theObject, 1);
	if (type_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete type_;
	type_ = NULL;
    }
    if (properties_ != NULL) {
        properties_->commit(theObject, 2);
	if (properties_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete properties_;
	properties_ = NULL;
    }
    DbAbstractObject::commit();
}


//-----------------------------------------------------------------------
// Attribute::rollback

void Attribute::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (type_)
	if (type_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete type_;
    type_ = NULL;
    if (properties_)
	if (properties_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete properties_;
    properties_ = NULL;
    DbAbstractObject::rollback();
}


//-----------------------------------------------------------------------
// AttributeIterator::AttributeIterator

AttributeIterator::AttributeIterator()
{
    attrNumber = -1;
    index = -1;
}


//-----------------------------------------------------------------------
// AttributeIterator::AttributeIterator

AttributeIterator::AttributeIterator(AttributeIndex attr, void* value, int length)
{
    attrNumber = attr;
    memcpy(searchValue, value, length);
    index = -1;
}


//-----------------------------------------------------------------------
// AttributeIterator::updateNext

Attribute* AttributeIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Attribute* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Attribute_CLASS_ID, index, object);
        else 
            result = dbmanager->search(Attribute_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Attribute_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Attribute::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// AttributeIterator::openrlockNext

Attribute* AttributeIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Attribute* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Attribute_CLASS_ID, index, object);
        else 
            result = dbmanager->search(Attribute_CLASS_ID, attrNumber,
				       index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Attribute_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Attribute::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// AttributeIterator::openNext

Attribute* AttributeIterator::openNext(DbResultCode& result, Attribute* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Attribute* temp;
    while (TRUE) {
        if (attrNumber == -1)
            result = dbmanager->iterate(Attribute_CLASS_ID, index, object);
        else 
           result = dbmanager->search(Attribute_CLASS_ID, attrNumber,
				      index, searchValue, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Attribute_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = Attribute::open(&title, result, OPEN, NULL);
	else
            temp = Attribute::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// AttributeIterator::reset

void AttributeIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
