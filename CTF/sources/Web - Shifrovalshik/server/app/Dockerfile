FROM python:3.8-slim

WORKDIR /app

COPY ./src .
COPY ./code.txt .
RUN pip install --no-cache-dir -r requirements.txt

RUN echo "EclipseCTF{Th1s_Pa$$w0rD_1S_f0R_Rc6}" > /flag.txt

ENV FLASK_APP=app
ENV FLASK_RUN_HOST=0.0.0.0

EXPOSE 5000

CMD ["flask", "run"]