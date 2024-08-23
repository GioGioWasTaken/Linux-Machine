# NOTE (VERY IMPORTANT!!!!!!!): 

- When compiled, the file shows a few "implicit function declerations" warnings. THOSE HEADERS WERE INCLUDED. Both inside, and outside my own header files. This warning won't go away no matter what I try.


# Why did I not have enough time?

I do understand and accept completely that this won't make my point penality any lower, but I still wanted to explain myself: 

-- Side note for the reader and grader, Roei Rahmani: The reason I'm writing all of this in English is that I use vim as my code editor, which gets really messy really quickly when you try to write in a language like Hebrew, which is read from the opposite side... Whenever I look or write hebrew text here, it's completely flipped (but I still tried to write it where needed so it's clearer for you).


- June: 
    - Not only did I have some bagrut exams, I also had to study for my other course, Intro to Java at the same time. 
- July:
    - Despite this supposedly being part of summer vacation, in actuality it's a test period. Pretty much every moed bet of every bagrut test, as well as some Moed Alephs, is during this period. I simply could not find the time to start working on the project, without hindering my school studying.
- August:
    - I started the project on august first. I was still getting used to everything that's unique about C, and was really struggeling at the start, sometimes spending an entire day debugging memory issues with undeclared variables, improperly malloc'd memory, UAF bugs, etc. Thankfully, I have gotten pretty good at mitigating those issues by the time I finished writing the preprocessor, but by then it was already the 10th... :(
    - 11th of August: I spent this entire day in an IDF facillity. I was summoned by the modiein department of Israeli Intelligence Corps(חיל המודיעין) because I had a יום מיונים for Gamma.

Leaving me with 1 week to finish the rest of the project...

Still, it was fun to make, so I decided to name it AwesomeAssembler (see make file).






## A couple of general notes:
-   Sometimes in comments I say "we" instead of I. This is not because I worked with another student, it simply feels like the more natural pronoun to use when explaining something.
    - Since i'm guiding you through my thinking process,  it's ought to be engaging, don't you think? :)

- Sometimes you will see me declaring a fatal error and instantly exiting the program. If a memory allocation has failed, the entire state of the program is corrupted. This should practically never happen, but the program shouldn't continue execution in that state.

- .ext file won't be created if a label is declared (.extern label), but never used.

- strings depend on the correct " character being used in order to work.


## Things I would have done differently:


`first_pass.c`: 
- Modify the way I handled labels: I put data string extern and entry labels all in the same table.  This would involve a lot of refactoring. Also: just have label type field instead of boolean fields.

~ 50 minutes - 1.5 hours


`preprocessor.c` ~ ??? hours
- overall just rework the entirety of the preprocessor.c. My C skills improved tremendously throughout this project, When I wrote the preprocessor, I was still getting accustomed to working with strings and files, and wasn't adapt at parsing data at all, so the codebase is pretty messy, and overall Had I handled things differently in this early, critical step, it would have helped to ease the parsing load in my other files as well.

To raise some more concrete points:
    - I would erase comments at the preprocessing step
    - I would fix whitespaces and commas at the preprocessing step (this would involve refactorin every parsing function I made in this project)
    - I would have used the util.c error function used to report all other errors.
    - Sometimes the preprocessor writes empty lines instead of just deleting the line completely. No harm done, but I would have liked to fix that.


# Known Errors 

Planned on, but did not implement this: 
- when building the second and third word,  write a function to read the current opcode from the 4 most significant bits, and pass it as a parameter to `BuildOperand`, such that it's possible to check if the current amount or type of operands are valid or invalid
