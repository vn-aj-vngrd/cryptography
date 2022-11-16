from vernamcipher.cryptographic import Cryptographic

encrypted = "JKYRXRYAHSL"
key = Cryptographic.generate_key()

decrypted_data = Cryptographic.exclusive_operations(encrypted, key)

print(decrypted_data)