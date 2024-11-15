#pragma once
#include "Macros.hpp"
#include "api/utils/ModuleUtils.hpp"
#include <Windows.h>
#include <functional>
#include <iostream>

class CommandRegistry {
public:
    CommandRegistry();

    CommandRegistry(const CommandRegistry&)            = delete;
    CommandRegistry& operator=(const CommandRegistry&) = delete;

protected:
    KobeBryant_NDAPI bool registerSimpleCommand(
        HMODULE                                              hModule,
        std::string const&                                   cmd,
        std::function<void(std::vector<std::string> const&)> callback
    );

public:
    KobeBryant_NDAPI static CommandRegistry& getInstance();

    inline bool
    registerSimpleCommand(std::string const& cmd, std::function<void(std::vector<std::string> const&)> callback) {
        return registerSimpleCommand(utils::getCurrentModuleHandle(), cmd, callback);
    }

    inline bool unregisterCommand(std::string const& cmd) {
        return unregisterCommand(utils::getCurrentModuleHandle(), cmd);
    }

    KobeBryant_NDAPI bool unregisterCommand(HMODULE hModule, std::string const& cmd);

    KobeBryant_API void executeCommand(std::string const& command);
};
