## General info

### Types of cryptosystems
1. Secret-key AKA `symmetric cryptography`. A secret key is used to both encode and decode messages. The key has to be exchanged over a secure channel. (essentially, only IRL.)
2.  Public-key AKA `assymetric cryptography`. A public key is used to encode messages, and a private one is used to decode them. 
		- Example: I publish a public key, and tell everyone "use this key to communicate with me!". Other people, do not know the private key. I then use my private key to decode these messages in my end. 
	- Unfortunately, `assymetric cryptography` is slow.
3. `Hybrid` - use `assymetric cryptography` to send the private key once, communicate with `symmetric cryptorgraphy` for added speed and no need for public keys.

### In every cryptosystem:
We would like to have a function that takes some number `X` and a key, and produces some number Y.


### Some terminology:

- When we say `private key` and `public key` we are referring to `assymetric cryptography`. 
- When we say `secret key` we are referring to `Symmetric cryptography`.
- When we want to refer to the `encryption function`, we refer to it as the `trapdoor function`. Originating from the fact it's practically impossible to find the number `X`, while only being given y.
- `Plaintext` is the pre-encryption data
- `Ciphertext` is the post-encryption data

[[RSA]]
[[Number_Theory]]
