#pragma once

namespace ly
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		void Destroy();
		bool IsPendingdDestroy() const { return mIsPendingDestroy; }

	private:
		bool mIsPendingDestroy;
	};
}