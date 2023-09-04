#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

namespace MapleEngine
{
	class IApplication
	{
	public:
		virtual ~IApplication() = default;
		virtual void Run() = 0;
	};

	extern "C" ENGINE_API IApplication* CreateApplication();
}