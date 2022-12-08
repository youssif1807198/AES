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
g++ -o AES AES.cpp main.cpp
# ENCRYPTION MODE
./AES encrypt input_plaintext_path  input_key_path output_cipher_text_path
# DECRYPTION MODE
./AES  decrypt input_cipher_text_path input_key_path output_decrypted_text_path


