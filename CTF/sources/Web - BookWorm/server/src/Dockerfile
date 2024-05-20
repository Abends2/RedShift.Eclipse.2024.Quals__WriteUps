FROM golang:1.22

LABEL authors="Danila Bogdanov"

WORKDIR /app

COPY src .

RUN go build -o app_book_list file_path_traversal/cmd/Books

RUN useradd -m EclipseCTF{../e7c/p455wd_hun73r}

CMD ["./app_book_list"]

EXPOSE 80
