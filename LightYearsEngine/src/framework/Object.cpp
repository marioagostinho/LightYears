#include "framework/Object.h"

namespace ly
{
	unsigned int Object::uniqueIDCounter = 0;
	unsigned int Object::GetNextAvaliableID()
	{
		return uniqueIDCounter++;
	}

	Object::Object()
		: mIsPendingDestroy(false),
		mUniqueID(GetNextAvaliableID())
	{

	}
	Object::~Object()
	{
	}

	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;
	}

	weak<Object> Object::GetWeakRef()
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}
}