FROM gcc:14-bookworm AS build

RUN apt-get update \
    && apt-get install --no-install-recommends -y cmake \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

# Configure in the container so CMake generates a cache using container paths.
RUN cmake -S . -B build \
    -DCMAKE_EXE_LINKER_FLAGS="-static-libgcc -static-libstdc++" \
    && cmake --build build --parallel

FROM debian:bookworm-slim

WORKDIR /app
COPY --from=build /app/build/text_rpg /app/text_rpg

ENTRYPOINT ["/app/text_rpg"]
