#ifndef DOCKER_NETWORK_HPP
#define DOCKER_NETWORK_HPP

#include <string>
#include <docker/network.hpp>

namespace Docker {
    class BridgeNetwork : public Network {
        public :
            BridgeNetwork(const std::string& name);
            BridgeNetwork(const std::string& name, const std::string& subnet);

            // public class methods
            std::string filter(const std::string& filter);
            std::string filter_by_name(const std::string& name);
            // delete the network
            std::string remove();

        private :
            // private subroutines
            std::string analyse_status_for_subnet(const std::string& status);
            std::string retrieve_network_information();
    };
}

#endif