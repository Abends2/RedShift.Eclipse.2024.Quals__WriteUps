import asyncio
import argparse
import rsa


hello_message = b"""
    Hello, you can get your encrypted flag with n and e with a random key using RSA.
    Type "exit" to close the connection or "help" for more information.
    """

help_message = b"""
    help - show this message
    exit - close the connection
    get_flag - get encrypted flag
    str2int <string> - convert string to integer
    int2str <int> - convert integer to string
    """

flag = b"EclipseCTF{S@me_m3ss@ges_1s_n0t_s0_g00d}"

flag_int = rsa.pkcs1.transform.bytes2int(flag)
input_prompt = b"\n>>> "


async def handler(reader: asyncio.StreamReader, writer: asyncio.StreamWriter):
    print("New connection!")

    writer.write(hello_message)
    writer.write(input_prompt)
    await writer.drain()
    try:
        while True:
            data = await reader.readline()
            message = data.decode().strip()
            match message.split(" ")[0]:
                case "exit":
                    break
                case "help":
                    writer.write(help_message)
                case "get_flag":
                    (public_key, private_key) = rsa.newkeys(512, exponent=3)
                    answer = f"""
    Encrypted flag: {pow(flag_int, private_key.e, public_key.n)}
    Random n: {public_key.n}
    Random e: {public_key.e}
                    """.encode()
                    writer.write(answer)
                case "str2int":
                    data = message.rsplit(" ", 1)[1].strip()
                    answer = b"\n" + str(rsa.pkcs1.transform.bytes2int(data.encode())).encode() + b"\n"
                    writer.write(answer)
                case "int2str":
                    data = message.rsplit(" ", 1)[1].strip()
                    answer = b"\n" + rsa.pkcs1.transform.int2bytes(int(data)) + b"\n"
                    writer.write(answer)
            await writer.drain()
            writer.write(input_prompt)
        writer.close()

    except OverflowError as f:
        print(f)
        writer.close()


async def start_service(host: str, port: int):
    service = await asyncio.start_server(handler, host, port)
    await service.serve_forever()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--host', default="0.0.0.0")
    parser.add_argument('--port', type=int, default=10000)

    ConnectionInfoParsed = parser.parse_args()
    HOST = ConnectionInfoParsed.host
    PORT = ConnectionInfoParsed.port

    print(f"Starting tcp server on {HOST}:{PORT}")
    asyncio.run(start_service(HOST, PORT))


if __name__ == "__main__":
    main()
