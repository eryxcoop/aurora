ARG PYTHON_BASE_IMAGE="python:3.9-slim-bullseye"

FROM ${PYTHON_BASE_IMAGE}

RUN apt-get update && apt-get upgrade -y && apt-get install -y git curl udev vim
RUN curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/master/scripts/99-platformio-udev.rules | tee /etc/udev/rules.d/99-platformio-udev.rules

ENV USER vscode
RUN useradd -m $USER

WORKDIR /home/$USER

RUN usermod -a -G dialout $USER
RUN usermod -a -G plugdev $USER

USER $USER
ENV PATH=$PATH":/home/${USER}/.local/bin"

RUN pip install -U platformio
RUN pio platform install https://github.com/platformio/platform-espressif32.git --with-package framework-arduinoespressif32
RUN pio system prune --force