#include <container-impl.hpp>
#include <docker.hpp>
#include <algorithm>


std::string Docker::ContainerImpl::execute(const std::string& command){
    return Docker::CliCalls::container_execute(id, command);
}
void Docker::ContainerImpl::attach(){
    Docker::CliCalls::container_attach(id);
}


std::string Docker::ContainerImpl::get_status() {
    return Docker::CliCalls::container_list("--filter id=" + id + " --all --format \"{{.Status}}\"");
}
std::string Docker::ContainerImpl::get_name() {
    auto name = Docker::CliCalls::container_list("--filter id=" + id + " --all --format \"{{.Names}}\"");
    name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
    return name;
}
std::string Docker::ContainerImpl::start() {
    return Docker::CliCalls::container_start(id);
}
std::string Docker::ContainerImpl::stop() {
    return Docker::CliCalls::container_stop(id);
}
std::string Docker::ContainerImpl::pause() {
    return Docker::CliCalls::container_pause(id);
}
std::string Docker::ContainerImpl::unpause() {
    return Docker::CliCalls::container_unpause(id);
}
std::string Docker::ContainerImpl::remove() {
    return Docker::CliCalls::container_remove(id);
}
