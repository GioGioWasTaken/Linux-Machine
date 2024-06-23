# The main idea

in RSA, our trapdoor function is :

See [[Euler_totient_function]] and .

![[Pasted image 20240624000838.png]]
 in this example, `11` is our `plaintext` and `131` is our `ciphertext`. So, how do we go the other way around?

 ![[Pasted image 20240624001104.png]]
 So in order for RSA to work, d(e(x)) must be equivalent Identity(x) for every input X.

so, d(e(x)) can be shown by means of:

![[Pasted image 20240624001321.png]]

See [[Euler's_Theorem]] for the base formula.

If we multiply each side by x^phi(n) , since x^phi(n) =1 %n, and since  1 %n =1 for every n, we can simplify the below expression, and assert:

![[Pasted image 20240624001837.png]]
multiply both sides by x, and we now have an equality to explore.
![[Pasted image 20240624002102.png]]

Therefore:

![[Pasted image 20240624002219.png]]

This can be naively solved iteratively,  by trying every k until we reach the solution.iteratively


Fortunately, Euclid has saved us from this pain, with the [[Extended_Euclidian_Algorithm]]


![[Pasted image 20240624003135.png]]
We must make the private-key b infeasible to calculate. 

This is getting really `number theory` heavy, so paused for the time being. The main idea is to use the fact P(n) is multiplicative(
p(x\*y) =  p(x) \* p(y)
) for `relatively prime` numbers, and this can be used to make some values easily calculable to the key knower and infeasibly calculable to malicious actors. 