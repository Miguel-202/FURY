#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace FURY
{
	class FURY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
// Core log macros
#define FURY_CORE_TRACE(...)	::FURY::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FURY_CORE_INFO(...)		::FURY::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FURY_CORE_WARN(...)		::FURY::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FURY_CORE_ERROR(...)	::FURY::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FURY_CORE_FATAL(...)	::FURY::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros

#define FURY_TRACE(...)			::FURY::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FURY_INFO(...)			::FURY::Log::GetClientLogger()->info(__VA_ARGS__)
#define FURY_WARN(...)			::FURY::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FURY_ERROR(...)			::FURY::Log::GetClientLogger()->error(__VA_ARGS__)
#define FURY_FATAL(...)			::FURY::Log::GetClientLogger()->fatal(__VA_ARGS__)