import os
import secrets
import string

with open("code.txt") as f:
    code = f.read()

def obf():
    key = ''.join(secrets.choice(string.ascii_letters + string.digits) for i in range(len(code)))
    out_code = [chr(ord(a) ^ ord(b)) for a,b in zip(key,code)]
    os.remove("code.txt")
    return key, out_code

def deobf(key, c):
    out_code = [chr(ord(a) ^ ord(b)) for a,b in zip(key,c)]
    return "".join(out_code)

