#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "engine/Engine.h"
#include "modules/MathModule.h"

class Showcase {
public:
    static void run() {
        MathModule module;
        Engine engine;

        std::vector<std::string> addParams;
        addParams.push_back("arg1");
        addParams.push_back("arg2");

        ArgsMap addDefaults;
        addDefaults["arg1"] = 0;
        addDefaults["arg2"] = 0;

        Wrapper<MathModule, int, int> addWrapper(
            &module,
            &MathModule::add,
            addParams,
            addDefaults
        );
        engine.registerCommand("add", &addWrapper);

        std::vector<std::string> mulParams;
        mulParams.push_back("arg1");
        mulParams.push_back("arg2");

        ArgsMap mulDefaults;
        mulDefaults["arg1"] = 1;
        mulDefaults["arg2"] = 1;

        Wrapper<MathModule, int, int> mulWrapper(
            &module,
            &MathModule::mul,
            mulParams,
            mulDefaults
        );
        engine.registerCommand("mul", &mulWrapper);

        std::vector<std::string> linearParams;
        linearParams.push_back("arg1");
        linearParams.push_back("arg2");
        linearParams.push_back("arg3");

        ArgsMap linearDefaults;
        linearDefaults["arg1"] = 0;
        linearDefaults["arg2"] = 0;
        linearDefaults["arg3"] = 0;

        Wrapper<MathModule, int, int, int> linearWrapper(
            &module,
            &MathModule::linear,
            linearParams,
            linearDefaults
        );

        engine.registerCommand("linear", &linearWrapper);

        std::cout << "Showcase: Engine demonstration" << std::endl;

        ArgsMap args1;
        args1["arg1"] = 2;
        args1["arg2"] = 3;
        int resAdd = engine.execute("add", args1);
        std::cout << "add(arg1=2, arg2=3) = " << resAdd << std::endl;

        ArgsMap args2;
        args2["arg2"] = 5;
        int resAddDefault = engine.execute("add", args2);
        std::cout << "add(arg2=5, arg1 default=0) = " << resAddDefault << std::endl;

        ArgsMap args3;
        args3["arg3"] = 4;
        args3["arg1"] = 2;
        args3["arg2"] = 10;
        int resLinear = engine.execute("linear", args3);
        std::cout << "linear(arg1=2, arg2=10, arg3=4) = "
            << resLinear << " (ожидаем 2*10+4=24)" << std::endl;

        ArgsMap args4;
        int resLinearDefault = engine.execute("linear", args4);
        std::cout << "linear(all defaults) = " << resLinearDefault << std::endl;
    }
};
