import hashlib
import random
import string
import time

def genRandomBlock(N):
    return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(N)).encode("utf-8")


def hashBlock(N):
    sha256 = hashlib.sha256();

    while (1):
        sha256.update(genRandomBlock(N))

    return sha256

def main():
    hashBlock(256)
    return


if __name__ == '__main__':
    main()
