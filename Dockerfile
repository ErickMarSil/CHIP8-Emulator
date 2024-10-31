FROM ubuntu:20.04

WORKDIR /Source

RUN apt-get install cmake
RUN cd Libs && \\
    git clone https://github.com/libsdl-org/SDL.git && \\
    cd SDL && \\
    mkdir build && \\
    cmake --DCMAKE_BUILD_TYPE=Release && \\
    sudo make install


COPY src/* .