# RSA Implementation
An (insecure) implementation of textbook RSA.

## Build
To build the tests, run:
```
make -f maketest
```
To build the executable, run:
```
make
```    

## Usage

To create a keypair (`(name)` and `(name).priv`), run:
```
./rsa -k (name)
```

To encrypt a message, run:
```
./rsa -e (name)
```
This will prompt for a message plaintext. Use the `-q` option before `-e` to prevent printing help prompts (for instance if you wish to output the result to a file).

To decrypt a message, run:
```
./rsa -d (name)
```
This will prompt for a ciphertext. Use the `-q` option before `-d` to prevent printing help prompts (for instance if you wish to output the result to a file).
