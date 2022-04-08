#pragma once

#include <QString>

namespace QUrho {
    class Application {
    public:
        static int execute(int argc, char **argv);
    private:
        static void SetupEnvironment();
        static void SetEnvironmentVariable(const char* variableName, const QString variableValue);
    };
}
