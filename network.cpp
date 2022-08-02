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


std::string Docker::BridgeNetwork::retrieve_network_information() {
    return Docker::CliCalls::network_inspect(getName());
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
    return Docker::CliCalls::network_remove(getName());
}


/*
std::string Docker::Network::getUnusedIp() {
    std::string filename{"data/" + name};
    std::fstream fs{filename, std::fstream::in};
    std::string s;
    std::vector<int> output;
    while (getline(fs, s)) {
        size_t pos{0};
        int num{0};
        std::string token;
        while((pos = s.find(":")) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + 1);
            ++num;
            if (num == 1) {
                size_t sub_pos{0};
                while((sub_pos = token.find(".") != std::string::npos)) {
                    token.erase(0, sub_pos);
                }
                output.push_back(std::stoi(token));
            }
        }
    }
    int notUsedNumber{-1};
    // will return 2 if no node exists in network file. 2 is the lowest
    // possible ip to be free since the host will allways be 1
    for (int i = 2; i < 255; ++i) {
        if(std::find(output.begin(), output.end(), i) == output.end()) {
            notUsedNumber = i;
            break;
        }
    }
    if (notUsedNumber == -1) {
        return "error"; // if no ip was free
    }
    // build full ip via deletion of last number and subnet mask
    int cnt{0};
    size_t pos{0};
    while (cnt != 3) {
        pos = subnet.find('.', pos);
        ++cnt;
        ++pos;
    }
    // subnet = subnet.substr(0, pos); TODO just for safety still here
    return subnet.substr(0, pos) + std::to_string(notUsedNumber);
}
*/

