#pragma once

#include<memory>

#include "framework/Core.h"

namespace ly
{
	class Object : public std::enable_shared_from_this<Object>
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		bool IsPendingdDestroy() const { return mIsPendingDestroy; }

		weak<Object> GetWeakRef();
		weak<const Object> GetWeakRef() const;

	private:
		bool mIsPendingDestroy;
	};
}