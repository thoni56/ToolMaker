//============ Name.cc
//=======================================================================

#include "DOL.hh"
#include "Name.hh"


//-----------------------------------------------------------------------
// Name::Name

Name::Name(char *arg1)
{
    memset(value, 0, 32);
    strcpy(value, arg1);
}

//-----------------------------------------------------------------------
// Name::Name

Name::Name()
{}

//-----------------------------------------------------------------------
// Name::operator==

Boolean Name::operator==(Name x)
{
    return memcmp(this, &x, 32) == 0;
}

//-----------------------------------------------------------------------
// Name::operator<

Boolean Name::operator<(Name x)
{
    return memcmp(this, &x, 32) < 0;
}


//-----------------------------------------------------------------------
// NameAttribute::get

DbResultCode NameAttribute::get(DbBaseObject* dbObject, AttributeIndex index, Name& buffer)
{	
    return dbObject->getValue(index, &buffer);
}

//-----------------------------------------------------------------------
// NameAttribute::get

DbResultCode NameAttribute::get(DbBaseObject* dbObject, AttributeIndex index, Name& buffer, int arrayindex)
{	
    return dbObject->getSlice(index, arrayindex*32, 32, &buffer);
}

//-----------------------------------------------------------------------
// NameAttribute::set

DbResultCode NameAttribute::set(DbBaseObject* dbObject, AttributeIndex index, Name buffer)
{	
    return dbObject->putValue(index, &buffer);
}

//-----------------------------------------------------------------------
// NameAttribute::set

DbResultCode NameAttribute::set(DbBaseObject* dbObject, AttributeIndex index, Name buffer, int arrayindex)
{	
    return dbObject->putSlice(index, arrayindex*32, 32, &buffer);
}

//-- EoF ------------------------------------------------------------
