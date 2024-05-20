FROM python:3.11-slim-buster

WORKDIR /app

COPY . /app

EXPOSE 36363

CMD pip install -r requirements.txt

CMD python ./app/src/server.py
