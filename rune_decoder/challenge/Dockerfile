# This is not the setup we use on server, but it should be enough to test exploits locally
FROM ubuntu:22.04

RUN apt-get update 
RUN apt-get install -y socat

RUN useradd -UM ctf

COPY ./rune_decoder /home/ctf/rune_decoder
COPY ./flag.txt /home/ctf/flag.txt
RUN chown root:root /home/ctf/flag.txt && chmod 644 /home/ctf/flag.txt

WORKDIR /home/ctf
USER ctf

EXPOSE 13373
CMD ["socat", "tcp-l:13373,reuseaddr,fork", "EXEC:./rune_decoder"]
