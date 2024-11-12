FROM ubuntu:22.04

RUN apt-get update 
RUN apt-get install -y socat

RUN useradd -UM ctf

COPY ./potion_brewing_exam /home/ctf/potion_brewing_exam
COPY ./flag.txt /home/ctf/flag.txt
RUN chown ctf:ctf /home/ctf/flag.txt && chmod 644 /home/ctf/flag.txt

WORKDIR /home/ctf
USER ctf

EXPOSE 13371
CMD ["socat", "tcp-l:13371,reuseaddr,fork", "EXEC:./potion_brewing_exam"]
