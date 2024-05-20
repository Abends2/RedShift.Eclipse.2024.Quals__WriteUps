FROM python:3.11-slim-buster

RUN mkdir -p /app

ADD . /app

WORKDIR /app

COPY ./requirements.txt /app/requirements.txt

RUN pip install -r requirements.txt

EXPOSE 8888

ENTRYPOINT ["python", "server.py"]