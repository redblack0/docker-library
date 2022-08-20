#ifndef DOCKER_NETWORK_INTERFACE_HPP
#define DOCKER_NETWORK_INTERFACE_HPP

#include <string>

namespace Docker {
    class Network {
        public :
            // getter for attributes
            inline std::string get_name() { return name; }
            inline std::string get_subnet() { return subnet; }

            // public class methods
            // virtual <std::vector<std::string>> get_connected_container() = 0;

            // delete the network
            virtual std::string remove() = 0;

        protected :
            inline Network(const std::string& name) :name(name) {}
            inline Network(const std::string& name, const std::string& subnet) : name(name), subnet(subnet) {}
            inline void set_subnet(const std::string& subnet) { this->subnet = subnet; }

        private :
            std::string name;
            std::string subnet;
    };
}

#endif