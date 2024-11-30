FROM python:3.9-slim AS trust_issues_build

RUN pip install flask flask-sqlalchemy flask-login
RUN pip install pyjwt

FROM trust_issues_build

WORKDIR /app
COPY . /app

EXPOSE 5000

ENV FLASK_APP=main.py
ENV FLASK_DEBUG=0
ENV FLASK_SECRET_KEY=4b21c73abdf3112b83d548aae86d1c82187237d4c619cc40217098e5defba74c

CMD ["flask", "run", "--host=0.0.0.0"]
