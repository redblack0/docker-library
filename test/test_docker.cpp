#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>


#include <factory.hpp>
#include <errors.hpp>
// #include <container.hpp>
// #include <network.hpp>


int main(void) {
    std::string test_network_name{"dash-devnet-tool-test-network-name"};
    std::string subnet{"10.0.0.0/8"};
    std::string ip{"10.0.0.3"};
    std::string image_name{"hello-world"};
    //std::string image_name{"dash-docker"};
    
    Docker::Network* n = nullptr;
    //Docker::Container* c;
    std::string error{""};
    try {
         n = Docker::Factory::network_create(test_network_name, subnet);
    //     //c = Docker::Factory::container_create(image_name, n->getName(), ip);
    //     //c->start();

    //     try {
    //         n = Docker::Factory::network_create(test_network_name, subnet);
    //         throw std::logic_error("network name should have been taken");
    //     } catch ( ... ) { }
    //     // delete network -> MUST FAIL
    //     try {
    //         n->remove();
    //         throw std::logic_error("remove should have failed");
    //     } catch ( Docker::ErrorResponseFromDaemon e ) {}


    //     // delete container and network -> SHOULD WORK
    //     c->remove();
    //     n->remove();
    // } catch ( std::logic_error e ) {
    //     error = e.what();
    // } catch ( Docker::ErrorResponseFromDaemon e ) {
    //     error = e.output();
    } catch ( ... ) { }
    delete n;
    //delete c;


    std::cout << error << std::endl;


    // throw ...
}