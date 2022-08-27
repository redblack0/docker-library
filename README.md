# docker-library

An independent library for getting access to the Docker-CLI from direct C++-methods.
With the use of the boost process library CLI calls get wrapped by the container, network and factory classes.
These 3 classes build the interface for the library and make their methods available for code linking to the lib.

    class Docker::Container
    class Docker::Network
    namespace Docker::Factory

The convenience header docker/interface.hpp wrapps these header files together.
Almost every method can throw an `Docker::ErrorResponseFromDaemon`, which means the subshell executing the command got something written on stderr.

Currently builds only the static lib and a little test, if Testing was activated from higher up the CMake chain.
