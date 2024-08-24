# DCL -> Deirror's Class Library
This library contains classes/data structures and functions which are just written in simpler way than the Microsoft ones. 

Preferably used for small project as in these classes there aren't all the implemented functions provided by Microsoft, but the most used ones + some made by me..

I provided a library which can be linked statically.

Steps
-
//My way of doing this kind of stuff

1.Create a folder (can be "Dependencies").

-In "Dependencies" you can create a folder with your library name(For instance, "DCL")

![Screenshot (606)](https://github.com/user-attachments/assets/d640dbde-b2c7-48ce-8736-25788e5bd1e6)

2.Create folders "include" and "lib"(can be src) in "Dependencies".

![Screenshot (602)](https://github.com/user-attachments/assets/0ef19c37-b122-47dd-ac40-82828054faff)

-In "include" put your header files(.h/.hpp), which you wish to use.

-In "lib"/"src" put your library files(.lib).

![Screenshot (603)](https://github.com/user-attachments/assets/c42c380a-7e0e-46dd-bb2d-9e74c75510f7)

![Screenshot (604)](https://github.com/user-attachments/assets/122d0ef3-2ec6-4581-af6b-888b84e6fbae)


3.Open your VS and click on Properties on your project

-Path is Configuration Properties/C/C++/General. There you want to add path to "include" in Additional Include Directories box.

![Screenshot (606)](https://github.com/user-attachments/assets/73be426b-aff8-4779-a6a1-8dccedbb9c70)

-Next go to Configuration Properties/Linker/General. In Additional Library Directories box write path to "lib".

![Screenshot (607)](https://github.com/user-attachments/assets/4d18d3c0-8d84-4faa-bc7d-fd65146623fd)

-Finally go to Configuration Properties/Linker/Input and write all the names of the library files in Additional Dependencies.

![Screenshot (609)](https://github.com/user-attachments/assets/1032bbc7-a4fb-46fc-aed0-451fe962a3a8)


That's how my library looks like when it comes down to structure.
-
![Screenshot (600)](https://github.com/user-attachments/assets/6eaec1f7-9d9d-444c-a068-3a49c531e738)
