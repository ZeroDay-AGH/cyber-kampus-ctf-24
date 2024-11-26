FROM ubuntu:22.04

RUN apt-get update 
RUN apt-get install -y socat

RUN useradd -UM ctf

COPY ./ancient_echoes /home/ctf/ancient_echoes
COPY ./flag.txt /home/ctf/flag.txt
RUN chown ctf:ctf /home/ctf/flag.txt && chmod 644 /home/ctf/flag.txt

WORKDIR /home/ctf
USER ctf

EXPOSE 13372
CMD ["socat", "tcp-l:13372,reuseaddr,fork", "EXEC:./ancient_echoes"]
