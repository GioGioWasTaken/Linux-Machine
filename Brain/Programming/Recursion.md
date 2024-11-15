# The 5 steps of solving a problem recursively:

- What's the smallest possible input?
- Think about different examples
- How can I solve case 3 with case 2?
- How can I solve case X with case X-1?
- translate logic to code.

# Sources to practice recursion problems:

[coding bat](https://codingbat.com/java)
[leetcode comment describing a general approach](https://leetcode.com/problems/permutations/solutions/18239/a-general-approach-to-backtracking-questions-in-java-subsets-permutations-combination-sum-palindrome-partioning/)
[Huge compendium of problems solved with recursion](https://www.techiedelight.com/recursion-practice-problems-with-solutions/)






# a note on recursion as a tool in production:
"
I get that this is about HOW to do recursion.  But nobody ever addresses the question of WHY/WHEN to do recursion.j

For example.  Every one of these tasks can be solved without recursion or iteration.  Recursion is literally the slowest most cumbersome method.  The problem is this:  If you focus on Recursion as the "cool new tool" for your toolbox - then every time you see a problem that can be broken into sub-problems, you'll use recursion!

Nobody teaches you to recognise when it's the "right" tool : /

Here's a default:  Recursion is almost always the wrong tool for the job! ... it's almost a tool of last resort!  Certainly it's not the right tool for most of the recursion examples you'll see online.

I sense a rage storm brewing ... but, don't sh-tpost me just yet...

Now, I have to be careful.  I'm really not trying to dump on anyone here... recursion is a very cool paradigm to understand, definitely.  But, like any tool... you need to know when it's use is appropriate.

How bad can it be?  It gets the job done...

To answer that, let me introduce you to Ted.  Ted is a builder, and he's come to work on your house.  Ted has all the latest tools at his disposal, but he's never been shown when/why to use them ... let's follow Ted around...

Hanging some picture frames?  No problem... Nails go in holes... So, Ted drills some holes and puts nails in them.  Job done!

Putting up a heavy bookshelf?  No problem ... Ted hammers a few screws into the wall.  Perfect!

Need a new roof??? ... Well, Ted realised very early in his career, that the ONLY way to build roofs is to start with the foundations and work upwards... it's literally the only way that makes sense.  So, he bulldozes the house and starts again : )

Ted, to be fair, is a truly terrible builder : /

Software Development is an Engineering Discipline it's not just the How that's important... anyone can learn the How.  Even Ted.   It's the Why and the When... and it seems like nobody is teaching that, mainly because... well, it gets complicated : /

... It also offends anyone who's just cracked recursion, and is feeling (quite rightly) very proud of themselves.

Take the first example... (I know, I know... again, hear me out)

It certainly "looks" VERY recursive... and that's the danger.  When you've just got a shiny new hammer, everything around you looks like a nail!  But it's obviously a great example of When NOT to do recursion.  It's a great teaching prop - but an awful candidate.

So, if you're going to look at the problem long enough to understand its recursive nature ... you should probably also see that it's almost half of a square.  We all know a square can be formed by two triangles!   We notice that we can put two identical triangle-ish shapes together and they almost make a square... but it's shape is a little off :

The shape is (n) by (n+1) ... or (n+1) by (n) ... So, it's slightly rectangular!  One side is exactly 1 larger than the other.

And if a rectangle is Width * Height .... Then our triangle MUST be (Width * Height) / 2

The solution is : N * (N+1) / 2 ... nothing fancy.  We just had to ignore the shiny recursive pattern in front of our eyes : )))

But you all know that (hopefully), so why am I mentioning it?

Before you all get mad at me...

Yes... I know the first example is just to teach recursion in a simple way.  I do 'get' that!  ... Realise, that I'm just using it as an obvious example of how a pattern that looks VERY recursive isn't always a good candidate.  Unfortunately, it usually isn't so obvious!

Remember: If you're looking at a problem through "recursive glasses" ... it WILL soon look recursive ; )

Even worse, many people around you will congratulate you on choosing a GREAT tool ... it's just not the RIGHT tool: /


So, learn recursion.  But...

- Recognise that recursion is awfully restrictive for a hundred reasons you probably won't fully appreciate till later.
- Recursion is almost always the wrong tool for the job !!!  Consider it a red flag, and think a little more first.
- Perversely, it also happens to be the thing they're prompting you to demonstrate in a job interview : O

And be aware that every problem given here, has a nice neat fixed-time expression ... in fact, it's hard to find a "recursion example" that doesn't have a linear or iterative expression.

Now... I'm an (admittedly grumpy) old ASM coder, but here's some facts that might shock you...

The Josephus Problem : It looks recursive... but is solvable in 3 CPU Opcodes.  Literally, the whole compiled code takes less space than it takes to store the word "Josephus", and it has no loops, uses no memory, makes no calls and uses no stack!  It isn't any more complex in a high level language either ... just nicer to read.

The Towers of Hanoi : ... Wow, now that MUST be recursive, right ???  I mean... look at it go!  Now, I know when I say this, a whole bunch of people will get salty... but the solution is only ONE opcode!  Just a few bytes!  That one opcode can calculate any 'move' of the solution, independently of the others ... so, you can just call it in a loop if you want the full solution.  The C/C++ code for it is just a couple of short lines!  I doubt the python is much bigger (I don't use Python)

Binary Count Problems : Similar to the "Towers Of Hanoi problem", any problem which is tied to a binary sequence will look VERY recursive.  This is because a binary count looks very recursive...  Learn to spot when apparent recursion is just following a binary sequence!  It happens so often you'll start seeing it everywhere!   It can make the difference between a simple counter (iterative) solution ... and a very expensive, inflexible and utterly pointless recursive solution.

The Steps Problem : and any recursive-looking problem that requires you to use the Fibonacci sequence.   Fibonacci looks VERY recursive... and the solution to avoiding recursion isn't exactly obvious ... but Fibonacci turns up SO often in algorithms that you should probably be aware that you can calculate any Fibonacci number N, without solving ANY previous Fibonacci number... so, in production code, you'd NEVER use a recursive solution !

If interested, look up "Fibonacci Dijkstra" for a massive speed-up ... and "Fibonacci Benet" for a clever recursion-avoiding trick to memorise and put in your mental toolbox : )


And, don't feel bad... really!  It takes experience to start spotting alternatives to recursion... and sometimes (rarely) recursion really IS the right solution... although, even then, you have much nicer options for implementing it that will become apparent with other tools, like Queues and Thread pools.

So, having said all that...

Don't get me wrong... if you're trying to ace an interview, and the problem looks recursive.  They're probably hoping you'll show them a recursive solution and be able to explain it to them.  So, for GODS SAKE LEARN RECURSION!

This video is GREAT for that... truly!  One of the best.

But, afterwards, if you really want to stand out to the interviewer ... mention it!  Say "Of course, I'm not entirely sure it's a recursive problem... I think it can be solved in linear time" ... see if they just say "No, it's fine, you've done what we wanted" ... or, if they say "Really?  Explain..."

Then, you can wow them with ... well, not just the size of your toolbox : )

... but your deeper understanding of the Whys and Whens... and, importantly, the When Nots ; )

In conclusion

Stick with it!  Practice!  Learn it inside out... till you're ready to explain it to an interviewer!  Then be prepared to spend the rest of your career avoiding it - and I mean "like a crazy Ex girlfriend/boyfriend" level of avoiding  ; ))))

Trust me, it's usually the right instinct.

Don't be Ted the Builder. "



In resposen to a comment referring to the simplcity in writing recursion:

"

Call recursion STILL isn't the right tool..


Are you saying that, as long as you're not selling it to customers, you should get into the habit of writing terrible, inefficient, hard-to-read code ?

But let's assume you have one of those rare problems that actually IS fundamentally recursive... ie.  Not the typical examples of Hanoi, Josephus, et al...


You said : "Sometimes you care a lot more about the time of the programmer than the runtime"

I hear that argument a lot : /

Okay, since you mention it - let's explore call stack recursion from a Time-To-Code standpoint...

... to do so, I'll imagine sanitising a call-recursion approach :

1. Replace one call with another

What is so difficult about using a pushfront(params) or pushback(params) instead of the DFS or BFS self call?

Surely, you'd likely admit that it's no more difficult to call workQueue.push(params) than to call myRecursiveFunction(params) 

... is one convenient than the other?  Does one save you some time?


2. Loop till done

Let's simplify the program flow, which is currently unreadable.

Isn't this far more beautiful...

do { ... } while(!workQueue.isEmpty) ;

... Now, this actually LOOKS like a loop!  And it has a well defined end condition, right where you expect to find it.

I can set other simple conditions, such as a flag that that early exits!  Yours would have to fully unwind the groaning stack using some global signal variable... and the flow would be identical to the same code running to completion : /  So, your flow is ALL kinds of wrong.

Also... I'd have spent no time head-scratching the call sequence or trying to imagine how various conditions might propagate : )

I'm sure you'll agree that my loop is more efficient, very readable, far more flexible and almost trivial in terms of coding.

It also has a sane control flow and doesn't cause a mess that needs to be cleaned up just so that it can exit gracefully.

I'll let you decide which is faster to write from the top down and places less cognitive load on the coder.

Conclusion?

Do you REALLY save any time writing recursive calls? ... or, are you only using call-stack recursion because it's :

"this real cool thing I learned at uni"


I'd argue that the workqueue is easier to write for, is far less prone to error than an ugly call recursive approach.... and also, less likely to crash out with a fatal stack overflow error ten minutes (or hours, or days) in : )

It's equivalent in terms of Lines of Code, it scales, it's machine friendly, it's easier to read and ... crucially, it also avoids gumming up the precious stack with exponential bullshit.
"
