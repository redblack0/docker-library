#include <docker/factory.hpp>   // for base classes
#include <docker.hpp>           // for cli calls
#include <container-impl.hpp>   // for specific container
#include <network-impl.hpp>     // for specific network


#include <algorithm>
#include <iostream>


Docker::Container* Docker::Factory::container_create(   const std::string& image, 
                                                        const mount& mount) {
    return container_create(image, "", "", mount);
}
Docker::Container* Docker::Factory::container_create(   const std::string& image, 
                                                        const std::string& network_name, 
                                                        const std::string& container_ip, 
                                                        const mount& mount) {
    auto container_id = Docker::CliCalls::container_create(image, network_name, container_ip, mount);
    container_id.erase(std::remove(container_id.begin(), container_id.end(), '\n'), container_id.end());
    Container* c = new ContainerImpl{container_id};
    return c;
}
Docker::Container* Docker::Factory::container_connect(const std::string& id_or_name) {
    Docker::CliCalls::container_inspect(id_or_name);
    return new ContainerImpl{id_or_name};
}


Docker::Network* Docker::Factory::network_create(const std::string& name) {
    Docker::CliCalls::network_create(name);
    return new BridgeNetwork{name};
}
Docker::Network* Docker::Factory::network_create(const std::string& name, const std::string& subnet) {
    Docker::CliCalls::network_create(name, subnet);
    return new BridgeNetwork{name, subnet};
}
Docker::Network* Docker::Factory::network_connect(const std::string& name) {
    Docker::CliCalls::network_inspect(name);
    return new BridgeNetwork{name};
}


std::string Docker::Factory::network_filter(const std::string& filter) {
    return Docker::CliCalls::network_list(filter);
}
std::string Docker::Factory::network_filter_by_name(const std::string& name) {
    return network_filter("--filter name=" + name + " --format \"{{.Name}}\"");
}
