Enjoy having everything divided into a million directories and sub-directories? Their names are too long? Still want to use the cd command? Hermes has got you covered!

Hermes is a CLI utility written in Rust meant to make your navigating through different directories in the terminal much more friction-less. It doesn't aim to replace cd, it aims to be used together with it. You decide where Hermes takes you.

Use with hermes, or hs.

- Hermes' main feature is setting marks in directories. By setting a mark, you allow yourself to jump to that directory.
- use ```hs -n -new n```  where n is the mark number, to set the current directory as a mark.
-  use ```hs n``` to jump to the n'th marked directory  
- use ```hs -n ~/some/dir n``` to mark a specific directory.
- use ```hs -list or -ls```  to list all marks
- remove a mark with ```hs -r n```
- switch two marks by doing ```hs -s n m```, where n and m are two numbers. They don't have to both be bounded, so this command is also used for rebounding a mark to a different number.
- use ```hs dirname``` for Hermes to search all of your marks for a directory, and enter it. If there are any conflicts, use fzf to resolve them. 
  - ```hs dirname``` is a recursive search. It searches (by default) 2 directories deep inside the marked directories.
    - so ```hs buffer_overflow``` will be entered, when its path is .../Pwnable.kr/Toddlers_bottle/buffer_overflow
  - specify the max amount of directory depth to search ```hs -depth n dirname```. Change it in the hermes config.
- use ```hs -f -freq n``` to get a list of your n most used directories, in a fzf menu, and enter the one you select.
