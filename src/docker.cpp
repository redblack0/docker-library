#include <docker.hpp>


#include <boost/process.hpp>
#include <sstream>


std::string execute(const std::string& command) {
    boost::process::ipstream cmd_stdout, cmd_stderr;
    boost::process::system(command, boost::process::std_out > cmd_stdout, boost::process::std_err > cmd_stderr);
    std::stringstream out, err;
    std::string s;
    while (getline(cmd_stderr, s)) err << s << std::endl;
    Docker::test_for_error(err.str());
    while (getline(cmd_stdout, s)) out << s << std::endl;
    return out.str();
}


std::string Docker::CliCalls::container_create(const std::string& image,const std::string& network_name,const std::string& container_ip) {
    if (image == "") return {"Error: must set an image for container to be built on!"};
    if (network_name != "") {
        // connect to network with static ip
        if (container_ip != "") return execute("docker container create -it --network " + network_name + " --ip " + container_ip + " " + image);
        // connect to network but with dynamic ip
        return execute("docker container create -it --network " + network_name + " " + image);
    }
    if (container_ip != "") {
        return {"Error: can not set ip when no network to connect to was given!"};
    }
    // create simple container -> connect to default network
    return execute("docker container create -it " + image);
}
std::string Docker::CliCalls::container_execute(const std::string& name, const std::string& command) {
    return execute("docker exec " + name + " " + command);
}
std::string Docker::CliCalls::container_list(const std::string& params) {
    return execute("docker container ls " + params);
}
std::string Docker::CliCalls::container_inspect(const std::string& name) {
    return execute("docker container inspect " + name);
}


std::string Docker::CliCalls::container_start(const std::string& name) {
    return execute("docker container start " + name);
}
std::string Docker::CliCalls::container_stop(const std::string& name) {
    return execute("docker container stop " + name);
}
std::string Docker::CliCalls::container_remove(const std::string& name) {
    return execute("docker container rm " + name);
}
std::string Docker::CliCalls::container_pause(const std::string& name) {
    return execute("docker container pause " + name);
}
std::string Docker::CliCalls::container_unpause(const std::string& name) {
    return execute("docker container unpause " + name);
}


std::string Docker::CliCalls::network_create(const std::string& name) {
    return execute("docker network create " + name);
}
std::string Docker::CliCalls::network_create(const std::string& name, const std::string& subnet) {
    return execute("docker network create --subnet=" + subnet + " " + name);
}
std::string Docker::CliCalls::network_inspect(const std::string& name) {
    return execute("docker network inspect " + name);
}
std::string Docker::CliCalls::network_list(const std::string& params) {
    return execute("docker network ls " + params);
}
std::string Docker::CliCalls::network_remove(const std::string& name) {
    return execute("docker network rm " + name);
}
