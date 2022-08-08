#ifndef DOCKER_CONTAINER_HPP
#define DOCKER_CONTAINER_HPP

#include <docker/container.hpp>

namespace Docker {
    class ContainerImpl : public Container {
        public :
            inline ContainerImpl(const std::string& id) : Container(id) {}
            inline ContainerImpl(ContainerImpl& dc) : Container(dc.id) {}

            // execute commands inside container
            std::string execute(const std::string& command);
            // container status control
            std::string getStatus();
            std::string start();
            std::string stop();
            std::string pause();
            std::string unpause();
            // dangerous
            std::string remove();
    };
}

#endif