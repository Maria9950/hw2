#include "engine/Engine.h"

Engine::Engine() = default;

int Engine::execute(const std::string& name, const ArgsMap& args) const {
    std::unordered_map<std::string, CommandFunc>::const_iterator it =
        commands_.find(name);

    if (it == commands_.end()) {
        throw std::runtime_error("Engine: unknown command: " + name);
    }

    const CommandFunc& func = it->second;
    return func(args);
}
