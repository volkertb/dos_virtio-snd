# syntax=docker/dockerfile:1
FROM ghcr.io/volkertb/debian-djgpp:v0.2 as builder

COPY . /src

WORKDIR /src

RUN make

RUN ls -lh virtsnd.exe

FROM ghcr.io/volkertb/cicd-qemu-dos-docker:v1.3

ARG DRIVE_C=/drive_c

COPY --from=builder /src/virtsnd.exe $DRIVE_C/

COPY deps/HDPMI32i.EXE $DRIVE_C/

RUN echo "HDPMI32i.EXE" > $DRIVE_C/CICD_DOS.BAT
RUN echo "virtsnd.exe" >> $DRIVE_C/CICD_DOS.BAT

# TODO : get `--enable-kvm` to work with that trick I got working with another Docker file (right uid and gid, etc.)
RUN qemu-system-i386 \
                      -nographic \
                      -blockdev driver=file,node-name=fd0,filename=/media/x86BOOT.img -device floppy,drive=fd0 \
                      -drive if=virtio,format=raw,file=fat:rw:$DRIVE_C \
                      -boot order=a \
                      -audiodev wav,id=snd0,path=$DRIVE_C/ac97_out.wav -device AC97,audiodev=snd0 \
                      -audiodev wav,id=snd1,path=$DRIVE_C/adlib_out.wav -device adlib,audiodev=snd1 \
                      -audiodev wav,id=snd2,path=$DRIVE_C/sb16_out.wav -device sb16,audiodev=snd2 \
                      -audiodev wav,id=snd3,path=$DRIVE_C/pcspk_out.wav -machine pcspk-audiodev=snd3
