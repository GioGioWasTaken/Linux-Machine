# Pseudocode: 

```c

int calc()
{
  _DWORD num_buffer[101]; // [esp+18h] [ebp-5A0h] BYREF
  _BYTE expr[1024]; // [esp+1ACh] [ebp-40Ch] BYREF
  unsigned int v3; // [esp+5ACh] [ebp-Ch]

  while ( 1 )
  {
    setZero(expr, 0x400);
    if ( !get_expr((int)expr, 1024) )
      break;
    setZero(num_buffer);
    if ( parse_expr((int)expr, num_buffer) )
    {
      printf("%d\n", num_buffer[num_buffer[0]]);
      fflush(stdout);
    }
  }
  return __readgsdword(0x14u) ^ v3;
}
int get_expr(char[] expr, size_t expr_size){
// just gets the expression. It allows [0-9] and these chars: / * % + -
}


int parse_expr(char[] expression,int[] nums){
    int i = 0
    int current_DigitOffset = expression;
    while(true){
        if(isDigit(expression[i])){
            i++;
        } else if(isOperation(expression[i])){
            digitAmount = expr + i -current_DigitOffset;
            char * num =  malloc(digitAmount);
            int num = atoi(num);


            int current_DigitOffset = expression + i +1;
        }
    }
}

int eval(_DWORD *num_buffer, char operations)
{
  int *result; // eax

  if ( operations == '+' )
  {
    num_buffer[num_count - 1] += num_buffer[num_count];
  }
  else if ( operations > '+' )
  {
    if ( operations == '-' )
    {
      num_buffer[num_count - 1] -= num_buffer[num_count];
    }
    else if ( operations == '/' )
    {
      num_buffer[num_count - 1] /= (int)num_buffer[num_count];
    }
  }
  else if ( operations == '*' )
  {
    num_buffer[num_count - 1] *= num_buffer[num_count];
  }
  result = num_buffer;
  --num_count;
  return result;
}


```




# Primitives:

Writing to the calculator. We need to find both an arbitrary read and write in order to get code execution, because there's ASLR, NX, and a Canary.


# Arbitrary read: 

By utilizing the fact the check for a valid expression, only invovles checking if the char after an operation is a number, and not the char before the operation as well:

``

we can modify an out of bounds value, and that value happens to be the `count` of the amount of numbers in the array.

then there's:
```c
  printf("%d\n", num_buffer[count]);
```

therefore, if we set count to say, address 0xdeadbeef, by means of incrementing/decrementing it, we will print the value:

```c

*((int * )num_buffer + 0xdeadbeef)

```

# Arbitrary write: 

(as demonstrated with the + operation)
Since we control the count, which is used to determine where to apply the operation, all we need to do now is to find a `count` s.t. num_buffer\[count]   :


```c

*( (int * ) num_buffer + (count-1)) += *( (int *) num_beffer + count)

```

since we are giving inputs of the form '-x' where x is offset from num_buffer we want to write to, the value of `count` before we overwrite it will always be 1.



# ROP chain:



num_buffer is located at $ebp - 0x5A0. calc's return addr is at $ebp + 0x4 

0x5a0+0x4 = 0x5a4 = 1444 /sizeof(int)  = 361


Therefore: 

let x = target_addr-134517746

then, -7+x will redirect code execution to the target address.

run:

```bash

ROPgadget --binary calc | grep "pop edi" 

```


0x80bc546: pop eax ; ret

0x80701d0 : pop edx ; pop ecx ; pop ebx ; ret



![Stack goal:](assets/stack_image.png)

NOTE: this is outdated. I wrote this before i realized that execve expects pointers to values passed through registers, and not the values themselves passed through registers (*face palms*)

we leak main's saved ebp on the stack, and calculate its offset from our base address (which is the address calc's return address is stored at.)

This way we can past pointers to controlled output. Pwned.
