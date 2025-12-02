#pragma once

#include <string>
#include <unordered_map>
#include <functional>
#include <stdexcept>

#include "wrapper/Wrapper.h"

class Engine {
public:
    Engine();

    template<typename Class, typename... Args>
    void registerCommand(const std::string& name,
        Wrapper<Class, Args...>* wrapper) {
        if (commands_.find(name) != commands_.end()) {
            throw std::runtime_error("Engine: command already registered: " + name);
        }

        commands_[name] = [wrapper](const ArgsMap& args) -> int {
            return wrapper->execute(args);
            };
    }

    int execute(const std::string& name, const ArgsMap& args) const;

private:
    using CommandFunc = std::function<int(const ArgsMap&)>;
    std::unordered_map<std::string, CommandFunc> commands_;
};
