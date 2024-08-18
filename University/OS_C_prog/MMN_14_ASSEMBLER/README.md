# Why did I not have enough time?

-- Side note for the reader and grader, Roei Rahmani: The reason I'm writing all of this in English is that I use vim as my code editor, which gets really messy really quickly when you try to write in a language like Hebrew, which is read from the opposite side... Whenever I look or write hebrew text here, it's completely flipped (but I still tried to write it where needed so it's clearer for you).


- June: 
    - Not only did I have some bagrut exams, I also had to study for my other course, Intro to Java at the same time. 
- July:
    - Despite this supposedly being part of summer vacation, in actuality it's a test period. Pretty much every moed bet of every bagrut test, as well as some Moed Alephs, is during this period. I simply could not find the time to start working on the project, without hindering my school studying.
- August:
    - I started the project on august first. I was still getting used to everything that's unique about C, and was really struggeling at the start, sometimes spending an entire day debugging memory issues with undeclared variables, improperly malloc'd memory, UAF bugs, etc. Thankfully, I have gotten pretty good at mitigating those issues by the time I finished writing the preprocessor, but by then it was already the 10th... :(
    - 11th of August: I spent this entire day in an IDF facillity. I was summoned by the modiein department of Israeli Intelligence Corps(חיל המודיעין) because I had a יום מיונים for Gamma.

Leaving me with 1 week to finish the rest of the project...






## A couple of general notes:
-   Sometimes in comments I say "we" instead of I. This is not because I worked with another student, it simply feels like the more natural pronoun to use when explaining something.
    - Since i'm guiding you through my thinking process,  it's ought to be engaging, don't you think? :)


## Things I would have done had I had more time:


`first_pass.c`: 
- Modify the isValidLabel function to return proper error codes instead of a boolean value, so we can give the user meaningful feedback.  ~10-20 minutes
- Modify the way I handled labels: I put data string extern and entry labels all in the same table.  This would involve a lot of refactoring, so ~ 50 minutes - 1.5 hours

`second_pass.c`:
- on top of the original modification I wanted to make in the first_pass to the way I handled externals, I would have liked to have a special field for them, instead of using the `address` field, which i typically used to store the address the label points to, and not the addresses. Not only is this unorganized, since there could be multiple declerations, I've had to write to the external file while i'm discovering references to the label, which makes the program harder to read. ~ 1 hour 


`preprocessor.c` ~ 2-3 hours
- overall just rework the entirety of the preprocessor.c. My C skills improved tremendously throughout this project, When I wrote the preprocessor, I was still getting accustomed to working with strings and files, and wasn't adapt at parsing data at all, so the codebase is pretty messy, and overall Had I handled things differently in this early, critical step, it would have helped to ease the parsing load in my other files as well.

I did do my best to make it a bit better today.

To raise some more concrete points:
    - I would erase comments at the preprocessing step
    - I would fix whitespaces and commas at the preprocessing step (this would involve refactorin every parsing function I made in this project)
    - I would have used the util.c error function used to report all other errors.
    - Sometimes the preprocessor writes empty lines instead of just deleting the line completely. No harm done, but I would have liked to fix that.
