# Use the official Kali Linux rolling image
FROM debian:bookworm-slim AS base

FROM base AS setup

WORKDIR /app

RUN apt-get update --fix-missing
RUN apt-get install -y --no-install-recommends make --fix-missing
RUN apt-get install -y --no-install-recommends build-essential --fix-missing

RUN mkdir ./tmp
RUN mkdir -p ./dist/linux_x64

FROM setup AS build

WORKDIR /app

# Copy project files
COPY ./include ./include
COPY ./src ./src
COPY ./Makefile ./Makefile


RUN make clean && make build
