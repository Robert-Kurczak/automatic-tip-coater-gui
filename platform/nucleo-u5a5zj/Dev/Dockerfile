FROM debian:stable

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    rbenv \
    make \
    g++ \
    libsdl2-dev \
    libsdl2-image-dev \
    && apt-get clean

ENV RBENV_ROOT=/usr/share/rbenv
ENV PATH="$RBENV_ROOT/shims:$RBENV_ROOT/bin:$PATH"

RUN rbenv init - && rbenv install 3.0.0 && rbenv global 3.0.0 && gem install roo