#ifndef DOCKERNETWORK_HPP
#define DOCKERNETWORK_HPP

#include <string>
#include <network.hpp>

namespace Docker {
    class BridgeNetwork : public Network {
        public :
            BridgeNetwork(const std::string& name);
            BridgeNetwork(const std::string& name, const std::string& subnet);

            // public class methods
            // std::string getUnusedIp();
            // delete the network
            std::string remove();

        private :
            // private subroutines
            std::string analyse_status_for_subnet(const std::string& status);
            std::string retrieve_network_information();
    };
}

#endif