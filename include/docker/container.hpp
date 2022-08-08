#ifndef CONTAINER_INTERFACE_HPP
#define CONTAINER_INTERFACE_HPP

#include <string>

namespace Docker {
    class Container {
        public :
            // execute commands inside container
            virtual std::string execute(const std::string& command) = 0;
            // container status control
            virtual std::string getStatus() = 0;
            virtual std::string start() = 0;
            virtual std::string stop() = 0;
            virtual std::string pause() = 0;
            virtual std::string unpause() = 0;
            // dangerous
            virtual std::string remove() = 0;
        protected :
            inline Container(const std::string& id) : id(id) {}
            inline Container(Container& c) : id(c.id) {}
            std::string id;
    };
}

#endif