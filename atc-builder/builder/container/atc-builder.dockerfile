FROM debian:stable

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    rbenv \
    bear \
    make \
    python3-venv \
    clang-tidy \
    gcovr \
    g++ \
    libsdl2-dev \
    libsdl2-image-dev \
    cmake \
    && apt-get clean

RUN python3 -m venv /opt/venv
ENV PATH="/opt/venv/bin:$PATH"

RUN pip install --no-cache-dir \
    clang-html \
    pyyaml

ENV RBENV_ROOT=/usr/share/rbenv
ENV PATH="$RBENV_ROOT/shims:$RBENV_ROOT/bin:$PATH"

RUN rbenv init - && rbenv install 3.0.0 && rbenv global 3.0.0 && gem install roo