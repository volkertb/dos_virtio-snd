FROM ghcr.io/volkertb/debian-djgpp:v0.2

COPY . /src

WORKDIR /src

RUN make

RUN ls -lh virtsnd.exe
