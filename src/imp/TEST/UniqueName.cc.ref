//============ UniqueName.cc
//=======================================================================

#include "DOL.hh"
#include "UniqueName.hh"


//-----------------------------------------------------------------------
// UniqueName::UniqueName

UniqueName::UniqueName(char *arg1,char *arg2)
{
    memset(base, 0, 32);
    strcpy(base, arg1);
    memset(name, 0, 32);
    strcpy(name, arg2);
}

//-----------------------------------------------------------------------
// UniqueName::UniqueName

UniqueName::UniqueName()
{}

//-----------------------------------------------------------------------
// UniqueName::operator==

Boolean UniqueName::operator==(UniqueName x)
{
    return memcmp(this, &x, 64) == 0;
}

//-----------------------------------------------------------------------
// UniqueName::operator<

Boolean UniqueName::operator<(UniqueName x)
{
    return memcmp(this, &x, 64) < 0;
}


//-----------------------------------------------------------------------
// UniqueNameAttribute::get

DbResultCode UniqueNameAttribute::get(DbBaseObject* dbObject, AttributeIndex index, UniqueName& buffer)
{	
    return dbObject->getValue(index, &buffer);
}

//-----------------------------------------------------------------------
// UniqueNameAttribute::get

DbResultCode UniqueNameAttribute::get(DbBaseObject* dbObject, AttributeIndex index, UniqueName& buffer, int arrayindex)
{	
    return dbObject->getSlice(index, arrayindex*64, 64, &buffer);
}

//-----------------------------------------------------------------------
// UniqueNameAttribute::set

DbResultCode UniqueNameAttribute::set(DbBaseObject* dbObject, AttributeIndex index, UniqueName buffer)
{	
    return dbObject->putValue(index, &buffer);
}

//-----------------------------------------------------------------------
// UniqueNameAttribute::set

DbResultCode UniqueNameAttribute::set(DbBaseObject* dbObject, AttributeIndex index, UniqueName buffer, int arrayindex)
{	
    return dbObject->putSlice(index, arrayindex*64, 64, &buffer);
}

//-- EoF ------------------------------------------------------------
