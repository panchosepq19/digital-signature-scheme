# Digital Signature with Pairing-Based Cryptography

This project demonstrates a basic implementation of a digital signature scheme using Pairing-Based Cryptography (PBC). The program reads a generator, a message, and a private key from an input file, hashes the message into an element of the elliptic curve group G1, and signs the message using the private key. The resulting signature is then saved to an output file.

## Table of Contents
- Installation
- Usage
- Input File Format
- Output File Format
- Dependencies
- License

## Installation

Clone the repository:

git clone https://github.com/panchosepq19.git

cd digital-signature-scheme

Install dependencies: Ensure you have the GMP and PBC libraries installed on your system. You can install them using the following commands on a Debian-based system:

sudo apt-get install libgmp-dev
sudo apt-get install libpbc-dev

Compile the program:

gcc -o sign sign.c -lgmp -lpbc

## Usage

Prepare the input file: 

The input file should contain the following information on separate lines:

Generator g1

Message m to be signed

Private key sk

Run the program:

./sign

Check the output: The output signature will be saved in the output file in the same directory.

## Input File Format

The input file should be formatted as follows:

Line 1: Generator g1 (in decimal format)

Line 2: Message m to be signed (as a string)

Line 3: Private key sk (in decimal format)

### Example:

12345678901234567890

Hello, World!

98765432109876543210

## Output File Format
The output file will contain the signature of the message. The signature is an element of the elliptic curve group G1, represented in a human-readable format using the element_fprintf function from the PBC library.

## Dependencies
GMP Library: For arbitrary precision arithmetic.

PBC Library: For pairing-based cryptographic operations.

## License
This project is licensed under the MIT License. 
