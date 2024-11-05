FROM ubuntu:20.04

WORKDIR /Source

RUN apt-get update make
RUN make

COPY Source/CHIP-8 && \\
    Source/Display && \\
    Source/Headers && \\
    Soruce/main.cpp && \\
    Include/*