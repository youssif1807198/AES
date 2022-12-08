# AES
AES Advanced Encryption Standards
• NIST Request New Algorithm in 1997
• AES is proposed by Dr. Joan Daemen and Dr.Vincent Rijmen, Belgium
• NIST Select AES (Rijndael) in 2001
• AES Replaces DES and 3DES
• Uses Modular Polynomial Arithmetic GF(2pow(8))
• Plaintext Block Size 16 Byte
• Variable Key Size 16 Byte
• Number of Rounds 10 Round
• Round Key Size 16 Byte
# Development
run executable by command line arguments
commands:
g++ -o AES AES.cpp main.cpp
# ENCRYPTION MODE
./AES encrypt <input plaintext path>  <input key path> <output cipher text path>
# DECRYPTION MODE
./AES  decrypt <input cipher text path> <input key path> <output decrypted text path>


