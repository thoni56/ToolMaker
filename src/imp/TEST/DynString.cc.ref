//============ DynString.cc
//=======================================================================

#include "DOL.hh"
#include "DynString.hh"


//-----------------------------------------------------------------------
// DynString::DynString

DynString::DynString(Boolean arg1,Integer_16 arg2,char *arg3)
{
    full = arg1;
    length = arg2;
    memset(buffer, 0, 200);
    strcpy(buffer, arg3);
}

//-----------------------------------------------------------------------
// DynString::DynString

DynString::DynString()
{}

//-----------------------------------------------------------------------
// DynString::operator==

Boolean DynString::operator==(DynString x)
{
    return memcmp(this, &x, 203) == 0;
}

//-----------------------------------------------------------------------
// DynString::operator<

Boolean DynString::operator<(DynString x)
{
    return memcmp(this, &x, 203) < 0;
}


//-----------------------------------------------------------------------
// DynStringAttribute::get

DbResultCode DynStringAttribute::get(DbBaseObject* dbObject, AttributeIndex index, DynString& buffer)
{	
    return dbObject->getValue(index, &buffer);
}

//-----------------------------------------------------------------------
// DynStringAttribute::get

DbResultCode DynStringAttribute::get(DbBaseObject* dbObject, AttributeIndex index, DynString& buffer, int arrayindex)
{	
    return dbObject->getSlice(index, arrayindex*203, 203, &buffer);
}

//-----------------------------------------------------------------------
// DynStringAttribute::set

DbResultCode DynStringAttribute::set(DbBaseObject* dbObject, AttributeIndex index, DynString buffer)
{	
    return dbObject->putValue(index, &buffer);
}

//-----------------------------------------------------------------------
// DynStringAttribute::set

DbResultCode DynStringAttribute::set(DbBaseObject* dbObject, AttributeIndex index, DynString buffer, int arrayindex)
{	
    return dbObject->putSlice(index, arrayindex*203, 203, &buffer);
}

//-- EoF ------------------------------------------------------------
