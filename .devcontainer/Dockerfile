# FROM gigamonkey/gigamonkey-lib:v2.3

FROM gigamonkey/gigamonkey-base-dev:v2.2.1

ADD https://api.github.com/repos/DanielKrawisz/data/git/refs/heads/master /root/data_version.json
RUN git clone --depth 1 --branch master https://github.com/DanielKrawisz/data.git /tmp/data
RUN cmake -G Ninja -B /tmp/data/build -S /tmp/data -DPACKAGE_TESTS=OFF
RUN cmake --build /tmp/data/build -j 4
RUN cmake --install /tmp/data/build

ADD https://api.github.com/repos/Gigamonkey-BSV/Gigamonkey/git/refs/heads/master /root/gigamonkey_version.json
RUN git clone --depth 1 --branch master https://github.com/Gigamonkey-BSV/Gigamonkey.git /tmp/gigamonkey
RUN cmake -G Ninja -B /tmp/gigamonkey/build -S /tmp/gigamonkey -DPACKAGE_TESTS=OFF
RUN cmake --build /tmp/gigamonkey/build -j 4
RUN cmake --install /tmp/gigamonkey/build