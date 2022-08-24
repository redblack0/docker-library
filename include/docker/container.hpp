#ifndef CONTAINER_INTERFACE_HPP
#define CONTAINER_INTERFACE_HPP

#include <string>

namespace Docker {
    class Container {
        public :
            // execute commands inside container
            virtual std::string execute(const std::string& command) = 0;
            virtual std::string attach() = 0;
            // container status control
            virtual std::string get_status() = 0;
            virtual std::string start() = 0;
            virtual std::string stop() = 0;
            virtual std::string pause() = 0;
            virtual std::string unpause() = 0;
            // dangerous
            virtual std::string remove() = 0;
            virtual std::string get_name() = 0;
            inline std::string get_id() { return id; }
        protected :
            inline Container(const std::string& id) : id(id) {}
            inline Container(Container& c) : id(c.id) {}
            std::string id;
    };
}

#endif