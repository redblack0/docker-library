#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>


#include <docker/factory.hpp>
#include <docker/errors.hpp>
// #include <container.hpp>
// #include <network.hpp>


int main(void) {
    std::string test_network_name{"dash-devnet-tool-test-network-name"};
    std::string subnet{"10.0.0.0/8"};
    std::string ip{"10.0.0.3"};
    std::string image_name{"hello-world"};
    //Docker::Container* c;
    
    Docker::Network* n = nullptr;
    std::string error{""};
    try {
        n = Docker::Factory::network_create(test_network_name, subnet);
        n->remove();
    } catch ( ... ) { error = "error was thrown"; }
    delete n;
    if (error != "") throw std::logic_error(error);
}