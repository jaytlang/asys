FROM ubuntu:20.04
MAINTAINER jaytlang@mit.edu

RUN apt-get update && \
	apt-get install -y --no-install-recommends qemu-system-misc git curl \
	make ca-certificates libmpc-dev clang-format vim

RUN mkdir /work
WORKDIR /work
RUN curl -sSf https://web.mit.edu/jaytlang/www/ethwinter/bootstrap.sh | /bin/sh
ENV PATH /work/asys/env/bin:$PATH

RUN apt-get purge curl -y && apt-get autoremove --purge -y
WORKDIR /work/asys

