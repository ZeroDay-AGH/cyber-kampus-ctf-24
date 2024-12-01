FROM python:3.9-slim-buster 

RUN apt update
RUN apt install -y socat
RUN pip install pycryptodome

WORKDIR /challenge
COPY . .

EXPOSE 1337

USER nobody

CMD ["socat", "-dd", "TCP-LISTEN:1337,reuseaddr,fork", "exec:python -u server.py"]
