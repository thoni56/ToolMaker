//============ Relation.cc
//=======================================================================

#include "DOL.hh"
#include "Relation.hh"


// Include referenced classes:
#include "Class.hh"


//-----------------------------------------------------------------------
// Relation::create

Relation* Relation::create(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Relation_CLASS_ID, &key, 32);
    return open(&title, result, CREATE, trId);
}



//-----------------------------------------------------------------------
// Relation::update

Relation* Relation::update(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Relation_CLASS_ID, &key, 32);
    return open(&title, result, UPDATE, trId);
}


//-----------------------------------------------------------------------
// Relation::remove

Relation* Relation::remove(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Relation_CLASS_ID, &key, 32);
    return open(&title, result, REMOVE, trId);
}


//-----------------------------------------------------------------------
// Relation::openrlock

Relation* Relation::openrlock(Name key,
	DbResultCode& result,
	LocalTransaction* trId)
{
    DbTitle title (Relation_CLASS_ID, &key, 32);
    return open(&title, result, OPENRLOCK, trId);
}


//-----------------------------------------------------------------------
// Relation::open

Relation* Relation::open(Name key,
	DbResultCode& result,
	Relation* dol)
{
    DbTitle title (Relation_CLASS_ID, &key, 32);
    if (dol == NULL)
        return open(&title, result, OPEN, NULL);
    else
        return open(&title, result, dol);
}


//-----------------------------------------------------------------------
// Relation::getClassNo

int Relation::getClassNo()
{
    return Relation_CLASS_ID;
}


//-----------------------------------------------------------------------
// Relation::getIterator

RelationIterator* Relation::getIterator()
{
    return new RelationIterator;
}


//-----------------------------------------------------------------------
// Relation::open

Relation* Relation::open(DbTitle *title,
	DbResultCode& result,
	DBOperation op,
	LocalTransaction* trId)
{
    DbBaseObject* object;
    DbBaseObject* tempObject;
    LocalTransItem* item;
    if (item=trId->find(title))
	return (Relation*) item;
    result = DbAbstractObject::open(title, op, object, tempObject);
    if (result != SUCCEEDED) 
	return NULL;
    else {
	switch (object->getClassId()) {
	case Relation_CLASS_ID:
	    return new Relation (object, tempObject, op, trId, title);
	default:
	    result = OBJECT_NOT_SUBCLASS;
            return NULL;
	}
    }
}


//-----------------------------------------------------------------------
// Relation::open

Relation* Relation::open(DbTitle *title, DbResultCode& result, Relation* dol)
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
// Relation::Relation

Relation::Relation(DbBaseObject* object,
	DbBaseObject* tempObject,
	DBOperation op,
	LocalTransaction* trId,
	DbTitle* title)
    : (object, tempObject, op, trId, title)
{
    Relation::init(op);
}


//-----------------------------------------------------------------------
// Relation::init

void Relation::init(DBOperation op, Boolean initBase)
{
    if (initBase)
	DbObject::init(op, initBase);
    if (op == CREATE) {
    }
    int i = 0;
    from_ = NULL;
    to_ = NULL;
}


//-----------------------------------------------------------------------
// Relation::updatefrom

Class* Relation::updatefrom(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (from_ != NULL)
        title = from_->getTitle();
    else {
        from_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return Class::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Relation::removefrom

Class* Relation::removefrom(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (from_ != NULL)
        title = from_->getTitle();
    else {
        from_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Class::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Relation::openrlockfrom

Class* Relation::openrlockfrom(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (from_ != NULL)
        title = from_->getTitle();
    else {
        from_->get(theObject, 2, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Class::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Relation::openfrom

Class* Relation::openfrom(DbResultCode& result, Class* dol)
{
    DbTitle* title;
    if (from_ != NULL)
        title = from_->getTitle();
    else {
        from_->get(theObject, 2, title);
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
// Relation::from

void Relation::from(Class* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (from_ &&  from_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete from_;
	if (data)
            from_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    from_ = DbTitleRef::nilRef();
    }
    else error("Relation::from");
}



//-----------------------------------------------------------------------
// Relation::updateto

Class* Relation::updateto(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (to_ != NULL)
        title = to_->getTitle();
    else {
        to_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
	return Class::open(title, result, UPDATE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Relation::removeto

Class* Relation::removeto(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (to_ != NULL)
        title = to_->getTitle();
    else {
        to_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Class::open(title, result, REMOVE, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}


//-----------------------------------------------------------------------
// Relation::openrlockto

Class* Relation::openrlockto(DbResultCode& result, LocalTransaction* trId)
{
    DbTitle* title;
    if (to_ != NULL)
        title = to_->getTitle();
    else {
        to_->get(theObject, 3, title);
    };
    if (title->getClassIdentity() != 0)     // 4f - Nil reference
        return Class::open(title, result, OPENRLOCK, trId);
    else {
	result = OBJECT_NOT_FOUND;
	return NULL;
    }
}



//-----------------------------------------------------------------------
// Relation::opento

Class* Relation::opento(DbResultCode& result, Class* dol)
{
    DbTitle* title;
    if (to_ != NULL)
        title = to_->getTitle();
    else {
        to_->get(theObject, 3, title);
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
// Relation::to

void Relation::to(Class* data) // set
{
    if (operation == UPDATE || operation == CREATE) {
	if (to_ &&  to_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete to_;
	if (data)
            to_ = new DbTitleRef(UPDATE, data->getTitle());
	else
	    to_ = DbTitleRef::nilRef();
    }
    else error("Relation::to");
}





//-----------------------------------------------------------------------
// Relation::prepare

DbResultCode Relation::prepare()
{
    DbResultCode result = SUCCEEDED;
    int i = 0;
    if (from_ != NULL) {
        DbTitle* title = from_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            from_->prepare(theObject, &temp);  //byt namn
    }
    if (to_ != NULL) {
        DbTitle* title = to_->getTitle();
        DbAbstractObject temp(title, OPEN, result);
        if (result == SUCCEEDED)
            to_->prepare(theObject, &temp);  //byt namn
    }
    return DbObject::prepare();
}


//-----------------------------------------------------------------------
// Relation::commit

void Relation::commit()
{
    if (theObject == NULL)
	return;
    DbTitle* title = NULL;
    int i = 0;
    if (from_ != NULL) {
        from_->commit(theObject, 2);
	if (from_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete from_;
	from_ = NULL;
    }
    if (to_ != NULL) {
        to_->commit(theObject, 3);
	if (to_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
	    delete to_;
	to_ = NULL;
    }
    DbObject::commit();
}


//-----------------------------------------------------------------------
// Relation::rollback

void Relation::rollback()
{
    if (theObject == NULL)
	return;
    int i = 0;
    if (from_)
	if (from_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete from_;
    from_ = NULL;
    if (to_)
	if (to_->getTitle()->getClassIdentity() != 0)     // 4f - Nil reference
    	    delete to_;
    to_ = NULL;
    DbObject::rollback();
}


//-----------------------------------------------------------------------
// RelationIterator::RelationIterator

RelationIterator::RelationIterator()
{
    attrNumber = -1;
    index = -1;
}



//-----------------------------------------------------------------------
// RelationIterator::updateNext

Relation* RelationIterator::updateNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Relation* temp;
    while (TRUE) {
        result = dbmanager->iterate(Relation_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Relation_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Relation::open(&title, result, UPDATE, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// RelationIterator::openrlockNext

Relation* RelationIterator::openrlockNext(DbResultCode& result, LocalTransaction* trId)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Relation* temp;
    while (TRUE) {
        result = dbmanager->iterate(Relation_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Relation_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        temp = Relation::open(&title, result, OPENRLOCK, trId);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// RelationIterator::openNext

Relation* RelationIterator::openNext(DbResultCode& result, Relation* dol)
{
    DataBaseManager* dbmanager = getDbManager_t();
    DbBaseObject* object;
    Relation* temp;
    while (TRUE) {
        result = dbmanager->iterate(Relation_CLASS_ID, index, object);
        if (result != SUCCEEDED)
	    return NULL;
        DbTitle title (Relation_CLASS_ID, -1,
		       object->getClid(), object->getLid());
        if (dol == NULL)
	    temp = Relation::open(&title, result, OPEN, NULL);
	else
            temp = Relation::open(&title, result, dol);
	if (result != OBJECT_NOT_SUBCLASS)
	    return temp;
    }
}


//-----------------------------------------------------------------------
// RelationIterator::reset

void RelationIterator::reset()
{
    index = -1;
}

//-- EoF ------------------------------------------------------------
