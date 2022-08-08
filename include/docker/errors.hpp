#ifndef DOCKER_ERRORS_HPP
#define DOCKER_ERRORS_HPP

#include <string>

namespace Docker {
    class ErrorResponseFromDaemon {
        public :
            ErrorResponseFromDaemon(std::string _stderr) : _stderr(_stderr) {}
            std::string output() { return _stderr; }
        
        private :
            std::string _stderr;
    };
}

#endif