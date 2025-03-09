# BitcoinKeys: A program for working with Bitcoin keys. 

Bitcoin uses secp256k1, an SEC elliptic curve.

## Usage

### Literals

* decimal numbers are integers mod secp256k1 base point order. 
* hexidecimal numbers are bitcoin numbers.
* hex strings represent raw data. 
* strings

### Keys

* numbers have == != > < >= <= + - * / ^ << >>
* pubkeys have == != + 
* pubkey * number -> pubkey
* binary data has ++ === == != > < >= <= + - * / % ^ && || & |

valid (pubkey) -> bool
sign (secret, bin) -> bin
verify (pubkey, bin) -> bool

push
abs

SHA_1
SHA_2_

## Build

```
mkdir build
cd build
conan install ..
cmake .. 
make
```

Binary file will be in `build/bin`. 
