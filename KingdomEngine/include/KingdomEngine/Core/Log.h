#ifndef LOG_H
#define LOG_H

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace KE
{
	class Log
	{
	public:
		static void Init(const std::string& logsFileName);

		static std::shared_ptr<spdlog::logger>& GetLogger() { return logger; }

	private:
		static std::shared_ptr<spdlog::logger> logger;
	};

}

#define LOG_TRACE(...)		   ::KE::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)		   ::KE::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)		   ::KE::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		   ::KE::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)		   ::KE::Log::GetLogger()->critical(__VA_ARGS__)

#endif
