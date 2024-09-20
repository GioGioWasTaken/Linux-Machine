# Primitives

- For now it seems that only the name of the lover is our primitive

# Defenses: 
- NX is enabled
- There is a stack canary 

# Attack vectors

- There is a very interesting call to system at `0x08048935`. 



# Program flow :

Descompiled code snippet(modified): 
```C

protect(`Primitive`);
local_18 = strlen(`Primitive`);

/* this is essentially a */ cat(prolog,primitive,epilog):

memcpy(loveletter + idx,prolog,local_20); 
idx = idx + (short)local_20;
memcpy(loveletter + idx,`Primitive`,local_18);
idx = idx + (short)local_18;
memcpy(loveletter + idx,epilog,local_1c);
idx = idx + (short)local_1c;

```

I can't do anything with these memcpy calls. This seems pretty safe, so let's look inside the protect function, and see what it does:

```C

protect(){
    // a bunch of movs to continuos memory addreses.  
    char * str = "#&;`'\"|*?~<>^()[]{}$\\,""

        // pseudocode
    while(input[i]!='\0'){
        if(isInside(input[i], str)){
            replaceInput()
        }
    }
}

```

- it changes everything that could be used to read the contents of a file with echo, to the unicode value of a heart.
- There is some flaw in the logic, that causes a segfault when enough illegal chars are detected.
- try running gdb with this input: $$$$$$$$$$$$$$$$$$$$$$$$$$ to figure out what's really going on inside the function

