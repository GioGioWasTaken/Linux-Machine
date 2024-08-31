A(){
    foo(){
    sysout("im in A");
}
}

B extends A(){
    foo(){
    sysout("im in B");
}
}

## Compile time

First during compile time, the compiler will check the right decleration
`a` ab  = new B()

it looks for the closest related method with B's sign in `a`. 

## Run time

then, the compiler will look at whatever it found during compile time.

Ah a `method that takes void` the compiler thinks. Well such a method also exists in `B`, the left side of the constructor call. So i'll take `B`'s method.

Had the method not been the exact same as the one found during compiliation, the compiler would have just chosen to use A's method.

e.g. if 

B extends A(){
    foo(String name){
    sysout("im in B, my name is "+name"!\n" );
}
}

then the compiler would just choose to use A's method.
