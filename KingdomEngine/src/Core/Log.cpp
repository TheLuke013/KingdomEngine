#include "KingdomEngine/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/sinks/basic_file_sink.h>

namespace KE
{

	std::shared_ptr<spdlog::logger> Log::logger;

	void Log::Init()
	{
		auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.txt", true);
		auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

		console_sink->set_pattern("%^[%T] %n: %v%$");
		file_sink->set_pattern("[%T] %n: %v");

		logger = std::make_shared<spdlog::logger>("LOG", spdlog::sinks_init_list{ console_sink, file_sink });
		spdlog::register_logger(logger);
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);
	}
}