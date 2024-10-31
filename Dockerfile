FROM ubuntu:20.04

WORKDIR /src

RUN apt-get install cmake
RUN git clone https://github.com/libsdl-org/SDL.git && \\
    cd SDL && \\
    mkdir build && \\
    cmake --DCMAKE_BUILD_TYPE=Release && \\
    sudo make install


COPY src/* .