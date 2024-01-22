#pragma once

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#include <cstdint>
#include <chrono>

namespace MapleEngine
{
	class ENGINE_API ProjectUtils
	{
	private:
		static std::uint64_t m_IDCounter; // Used for Unique ID Generation

	public:
		static uint64_t GenerateUniqueID()
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

			m_IDCounter++;
			std::uint64_t ID = (timestamp << 32) | m_IDCounter;
			return ID;
		}
	};
}