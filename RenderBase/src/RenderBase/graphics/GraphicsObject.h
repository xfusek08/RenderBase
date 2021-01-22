#pragma once

#include <string>

namespace rb {

    class GraphicsObject
    {
        public:
            void fail(std::string message);
            std::string getErrorMessage() const { return errorMessage; }
            bool isOk() const { return errorMessage.empty(); }
        private:
            std::string errorMessage = "";
    };

}
