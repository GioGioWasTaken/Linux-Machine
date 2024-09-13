# Ah yes, my favourite part of exploit development
![Typical experience when de-
veloping exploit in mock environment
first (illustration).](assets/mock_env.png)

![Typical experience when de-
veloping exploit directly in target envi-
ronment (illustration).](assets/target_env.png)

## We don't have access to the assembly:

- I am yet to have been in this situation. This makes exploit development near impossible.

## A difference between machines:


## Issue of Dependencies:

Perhaps the biggest issue we have to take into account when considering toy vs real solutions is that of dependencies.

- install the missing dependencies. We probably don’t have permissions to do this, but it is worth a shot

- use a static, compiled language such as C, C++, Rust or Golang that we feel comfortable and productive with (that’s
relatively speaking, of course; nothing is as comfortable and productive as Python). Compile for the target machine
architecture and simply run the executable in the target environment. This may be a handful of work, but will eliminate
the vast majority of dependency issues.

-  use Python with pyinstaller. pyinstaller can convert Python scripts into executable programs:
pyinstaller --onefile script.py .

-  force executables to be linked statically. Some run-time libraries we’re relying on might not be available on the target
environment, which will cause executables to crash and complain about missing libraries.
    - Otherwise, another solution is to use `staticx` on a dynamically-linked executable to obtain a statically-linked version: 
	- e.g. staticx input_dynamic_executable output_static_executable .

-  look for an alternative on the target system. For instance, as we mentioned before, the pwnable servers don’t have
the pexpect Python library installed, but do have pwntools which offer analogous functionality. Note that pwntools
is only implemented for Python 2 and not Python 3.

-  sigh and implement the functionality ourselves. We should proceed with caution. If we are not super comfortable with
the problem domain, chances are this will end badly.
