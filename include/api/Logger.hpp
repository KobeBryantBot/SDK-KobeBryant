#pragma once
#include "Macros.hpp"
#include "fmt/format.h"
#include <filesystem>
#include <optional>

class Logger {
public:
    enum class LogLevel : int {
        Fatal = 0,
        Error = 1,
        Warn  = 2,
        Info  = 3, // Default
        Debug = 4,
    };

protected:
    std::string                          mTitle;
    LogLevel                             mLogLevel = LogLevel::Info;
    std::optional<std::filesystem::path> mFilePath = {};

public:
    KobeBryant_NDAPI explicit Logger();

    KobeBryant_NDAPI explicit Logger(std::string const& title);

    KobeBryant_API void setTitle(std::string const& title);

    KobeBryant_API void setLevel(LogLevel level);

    KobeBryant_API bool setFile(std::filesystem::path const& path);

    KobeBryant_API void printStr(LogLevel level, std::string const& data) const;

    KobeBryant_NDAPI std::string translate(std::string const& data, std::vector<std::string> const& params) const;

public:
    template <typename... Args>
    void fatal(fmt::format_string<Args...> fmt, Args&&... args) const {
        printStr(LogLevel::Fatal, fmt::vformat(fmt.get(), fmt::make_format_args(args...)));
    }

    void fatal(std::string const& msg, std::vector<std::string> const& params = {}) const {
        printStr(LogLevel::Fatal, translate(msg, params));
    }

    template <typename... Args>
    void error(fmt::format_string<Args...> fmt, Args&&... args) const {
        printStr(LogLevel::Error, fmt::vformat(fmt.get(), fmt::make_format_args(args...)));
    }

    void error(std::string const& msg, std::vector<std::string> const& params = {}) const {
        printStr(LogLevel::Error, translate(msg, params));
    }

    template <typename... Args>
    void warn(fmt::format_string<Args...> fmt, Args&&... args) const {
        printStr(LogLevel::Warn, fmt::vformat(fmt.get(), fmt::make_format_args(args...)));
    }

    void warn(std::string const& msg, std::vector<std::string> const& params = {}) const {
        printStr(LogLevel::Warn, translate(msg, params));
    }

    template <typename... Args>
    void info(fmt::format_string<Args...> fmt, Args&&... args) const {
        printStr(LogLevel::Info, fmt::vformat(fmt.get(), fmt::make_format_args(args...)));
    }

    void info(std::string const& msg, std::vector<std::string> const& params = {}) const {
        printStr(LogLevel::Info, translate(msg, params));
    }

    template <typename... Args>
    void debug(fmt::format_string<Args...> fmt, Args&&... args) const {
        printStr(LogLevel::Debug, fmt::vformat(fmt.get(), fmt::make_format_args(args...)));
    }

    void debug(std::string const& msg, std::vector<std::string> const& params = {}) const {
        printStr(LogLevel::Debug, translate(msg, params));
    }
};