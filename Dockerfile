FROM ubuntu:20.04

WORKDIR /Source

RUN apt-get update make
RUN make

COPY .