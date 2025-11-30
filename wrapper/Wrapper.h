#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <stdexcept>
#include <utility>

using ArgsMap = std::unordered_map<std::string, int>;

template<typename Class, typename... Args>
class Wrapper {
public:
    using Method = int (Class::*)(Args...);

    Wrapper(Class* object,
        Method method,
        const std::vector<std::string>& paramNames,
        const ArgsMap& defaultArgs)
        : object_(object)
        , method_(method)
        , paramNames_(paramNames)
        , defaultArgs_(defaultArgs)
    {
        const std::size_t expected = sizeof...(Args);
        if (paramNames_.size() != expected) {
            throw std::runtime_error(
                "Wrapper: number of parameter names does not match method arity"
            );
        }
    }

    int execute(const ArgsMap& callArgs) const {
        const std::size_t N = sizeof...(Args);
        std::array<int, N> values;

        for (std::size_t i = 0; i < N; ++i) {
            const std::string& name = paramNames_[i];
            int value = 0;
            bool hasValue = false;

            ArgsMap::const_iterator itCall = callArgs.find(name);
            if (itCall != callArgs.end()) {
                value = itCall->second;
                hasValue = true;
            }

            if (!hasValue) {
                ArgsMap::const_iterator itDef = defaultArgs_.find(name);
                if (itDef != defaultArgs_.end()) {
                    value = itDef->second;
                    hasValue = true;
                }
            }

            if (!hasValue) {
                throw std::runtime_error("Wrapper: missing required argument: " + name);
            }

            values[i] = value;
        }

        return invokeWithArray(values, std::make_index_sequence<N>{});
    }

private:
    Class* object_;
    Method method_;
    std::vector<std::string> paramNames_;
    ArgsMap defaultArgs_;

    template<std::size_t N, std::size_t... I>
    int invokeWithArray(const std::array<int, N>& values,
        std::index_sequence<I...>) const {
        return (object_->*method_)(values[I]...);
    }
};
