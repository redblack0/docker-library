#ifndef DOCKER_DOCKER_CLI_HPP
#define DOCKER_DOCKER_CLI_HPP

#include <docker/errors.hpp>
#include <string>
#include <tuple>

namespace Docker {
    inline void test_for_error(const std::string& err) { 
        if (err != "") throw Docker::ErrorResponseFromDaemon(err); 
    }

    namespace CliCalls {
        // container specific docker requests
        std::string container_create(   const std::string& image,
                                        const std::string& network_name,
                                        const  std::string& container_ip, 
                                        std::tuple<
                                            std::string, std::string
                                                                > mount);
        std::string container_execute(  const std::string& name, 
                                        const std::string& command);
        std::string container_list(     const std::string& = "");
        std::string container_inspect(  const std::string& name);
        void container_attach(   const std::string& name);
        // container status control methods
        std::string container_start(    const std::string& name);
        std::string container_stop(     const std::string& name);
        std::string container_pause(    const std::string& name);
        std::string container_unpause(  const std::string& name);
        std::string container_remove(   const std::string& name);


        // network specific docker calls
        std::string network_create( const std::string& name);
        std::string network_create( const std::string& name, 
                                    const std::string& subnet);
        std::string network_inspect(const std::string& name);
        std::string network_list(   const std::string& params);
        std::string network_remove( const std::string& name);
    }
}
#endif
