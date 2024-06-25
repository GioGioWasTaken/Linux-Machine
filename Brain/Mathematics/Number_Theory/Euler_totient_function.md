# Relatively Prime numbers

It will be said that two numbers N and M are `Relatively Prime`, or `coprime`,  if and only if, their GCD (=`greatest common divisor`) is 1.

e.g. 
GCD(3,8) is 1
but: GCD(3,9) = 3, therefore they are not `coprime` or `relatively prime`

# Euler totient function

Is a function  P (I don't have greek letters) that counts how many positive numbers `relatively prime`  exist up to N with respect to N.

Essentially: P(n) = count(GCD(n,m)) for every m \<n
trivially from this definition, if n is a prime number, P(n) = p-1 (it is `relatively prime` to all numbers up to it except with itself.(since 1 is excluded))

read further about [[Euler's_Theorem]]
