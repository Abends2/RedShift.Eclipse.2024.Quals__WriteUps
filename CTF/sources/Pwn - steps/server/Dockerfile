# Используем официальный образ Ubuntu как базовый
FROM gcc:latest

# Отключаем диалоговые окна при установке пакетов
ARG DEBIAN_FRONTEND=noninteractive

# Установка необходимых пакетов
RUN apt-get update && apt-get install -y \
    gcc-multilib \
    g++-multilib \
    gdb \
    socat \
    && rm -rf /var/lib/apt/lists/*

# Создаём рабочую директорию для нашего проекта
WORKDIR /

# Копируем исходный код сервера в контейнер
COPY pwn-revers.c .

RUN gcc -m32 -o vulnerable_server pwn-revers.c -fno-stack-protector -z execstack -no-pie -g
# Компилируем наш уязвимый сервер для 32-битной архитектуры с отключенной защитой стека и ASLR

# Открываем порт 12345 для взаимодействия с уязвимым сервером через socat
EXPOSE 12345

# Запускаем socat для перенаправления входящих TCP соединений на наш уязвимый сервер
CMD ["socat", "TCP-LISTEN:12345,reuseaddr,fork", "EXEC:./vulnerable_server1"]
