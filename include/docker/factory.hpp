#ifndef DOCKER_FACTORY_HPP
#define DOCKER_FACTORY_HPP

#include <docker/container.hpp>
#include <docker/network.hpp>
#include <tuple>

namespace Docker {
    typedef std::tuple<std::string, std::string> mount;
    namespace Factory {
        Container* container_create(const std::string& image, const mount& mount = std::make_tuple("",""));
        //Container container_create(const std::string& image, Network& n);
        Container* container_create(    const std::string& image, 
                                        const std::string& network_name, 
                                        const std::string& container_ip, 
                                        const mount& mount = std::make_tuple("",""));
        Container* container_connect(const std::string& id_or_name);

        Network* network_create(const std::string& name);
        Network* network_create(const std::string& name, const std::string& subnet);
        Network* network_connect(const std::string& name);

        std::string network_filter(const std::string& filter);
        std::string network_filter_by_name(const std::string& name);
    }
}

#endif