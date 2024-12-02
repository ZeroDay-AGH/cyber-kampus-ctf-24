#!/bin/bash
NAME="trust_issues"
docker rm -f $NAME
docker build --tag=$NAME . && \
docker run -p 5000:5000 --rm --name=$NAME $NAME
