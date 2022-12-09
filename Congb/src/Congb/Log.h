#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Congb {

	class CONGB_API Log
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
#define CB_CORE_TRACE(...)	::Congb::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CB_CORE_INFO(...)	::Congb::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_WARN(...)	::Congb::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_ERROR(...)	::Congb::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CB_CORE_FATAL(...)	::Congb::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define CB_TRACE(...)		::Congb::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CB_INFO(...)		::Congb::Log::GetClientLogger()->info(__VA_ARGS__)
#define CB_WARN(...)		::Congb::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CB_ERROR(...)		::Congb::Log::GetClientLogger()->error(__VA_ARGS__)
#define CB_FATAL(...)		::Congb::Log::GetClientLogger()->fatal(__VA_ARGS__)


