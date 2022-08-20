#include <network-impl.hpp>
#include <docker.hpp>


#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>


Docker::BridgeNetwork::BridgeNetwork(const std::string& name) : Network(name) {
    auto out = retrieve_network_information();
    set_subnet(analyse_status_for_subnet(out)); // can theoretically throw an error
}
Docker::BridgeNetwork::BridgeNetwork(const std::string& name, const std::string& subnet) : Network(name, subnet) { }


std::string Docker::BridgeNetwork::filter(const std::string& filter) {
    return Docker::CliCalls::network_list(filter);
}
std::string Docker::BridgeNetwork::filter_by_name(const std::string& name) {
    return filter("--filter name=" + name + " --format \"{{.Name}}\"");
}


std::string Docker::BridgeNetwork::retrieve_network_information() {
    return Docker::CliCalls::network_inspect(get_name());
}
std::string Docker::BridgeNetwork::analyse_status_for_subnet(const std::string& status) {
    std::string line;
    std::stringstream s{status}; // convert to stringstream for line separation
    while (getline(s, line)) {
        if (line.find("Subnet") != std::string::npos) {
            int cnt{0};
            size_t pos{0};
            while(cnt != 3) {
                pos = line.find('"', pos);
                ++cnt;
                ++pos;
            }
            size_t npos{line.find('"', pos)};
            return line.substr(pos, npos - pos);
        }
    }
    throw "error"; // should not occur if the network exists
}


std::string Docker::BridgeNetwork::remove() {
    return Docker::CliCalls::network_remove(get_name());
}
