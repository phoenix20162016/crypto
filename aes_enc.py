from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import logging
import secrets

class AESEncryptUtil:
  def __init__(self):
    self.key = bytes()
    self.iv = bytes()
    self.key_iv = None

  def get_key(self):
    return self.key_iv

  def gen_aes_key(self):
    hex_key = secrets.token_hex(16)
    hex_iv = secrets.token_hex(16)
    self.key = bytes.fromhex(hex_key)
    self.iv = bytes.fromhex(hex_iv)
    self.key_iv = "|".join([hex_key, hex_iv])
    print(f"key: {self.key} |||| len: {len(self.key)}")
    print(f"value: {self.iv}")
    print(f"key_iv: {self.key_iv}")
    return self.key_iv

  def import_aes_key(self, key_and_iv):
    hex_key, hex_iv = key_and_iv.split("|")
    self.key = bytes.fromhex(hex_key)
    self.iv = bytes.fromhex(hex_iv)

  def cbc_mode_encrypt(self, plaintext):
    if not self.key or not self.iv:
      raise Exception(f"import aes key first")
    cipher = AES.new(self.key, AES.MODE_CBC, self.iv)
    if isinstance(plaintext, str):
      plaintext = plaintext.encode("utf-8")

    plaintext_padded = pad(plaintext, AES.block_size)
    ciphertext = cipher.encrypt(plaintext_padded)
    return ciphertext

  def cbc_mode_decrypt(self, ciphertext):
    if not self.key or not self.iv:
      raise Exception(f"import aes key first")
    cipher = AES.new(self.key, AES.MODE_CBC, self.iv)
    plaintext = cipher.decrypt(ciphertext)
    plaintext = unpad(plaintext, AES.block_size)
    print(f"len: {len(plaintext)} plaintext bytes: {plaintext}")
    return plaintext.decode("utf-8")

  def encrypt(self, plaintext):
    if not self.key or not self.iv:
      raise Exception(f"import aes key first")
    cipher = AES.new(self.key, AES.MODE_GCM, self.iv)
    if isinstance(plaintext, str):
      plaintext = plaintext.encode("utf-8")

    plaintext_padded = pad(plaintext, AES.block_size)
    ciphertext, auth_tag = cipher.encrypt_and_digest(plaintext_padded)
    return ciphertext, auth_tag

  def decrypt(self, ciphertext, auth_tag):
    if not self.key or not self.iv:
      raise Exception(f"import aes key first")
    cipher = AES.new(self.key, AES.MODE_GCM, self.iv)
    plaintext = cipher.decrypt(ciphertext)
    plaintext = unpad(plaintext, AES.block_size)
    try:
      cipher.verify(auth_tag)
    except ValueError:
      print("Message check failed.")
    return plaintext.decode("utf-8")

if __name__ == '__main__':
  key_iv = "6e698f3d59ab81606d66b292c29cd8a9|0071b3580b41ca429a5674270f988f3e"
  content = hex_key = secrets.token_hex(1025)
  print(f"plaintext: {len(content)}")
  aes_util = AESEncryptUtil()
  aes_util.import_aes_key(key_iv)
  ciphertext = aes_util.cbc_mode_encrypt(content)
  print(f"ciphertext: {len(ciphertext)}")
  with open("result.bin", 'wb') as fd:
    fd.write(ciphertext)