What is it?
==========

This is my Autopoet program, written in C. It is an implementation of the
"Dissociated Press" algorithm https://en.wikipedia.org/wiki/Dissociated_press.

I use it as an extended form of "Hello World" when I want to play with a
programming language.

Important note: Because of the programs history, only versions up from tag
"standalone" can be compiled successfully on your machine. For more information,
see section "History".

Usage
=====

You can compile and install it with:

```
$ make install
```

Tests can be run with:

```
$ make test
```

I also included a Vagrantfile. With

```
$ make vagrant
```

you can set up a Vagrant VM where the code is built and the tests are run. This
of course requires that you have Vagrant installed. You can get it here:
https://www.vagrantup.com/.

History
=======

Note: This code has a long history, dating back to at least 2001. I have split
it out of a bigger "dev" repo and prepared it for GitHub. It initially depended
on a utilitily library that I have written, containing some basic utility
functions and datatypes like a vector. I have rewritten it so that it does no
longer depend on my library, but on Glibc instead (see
https://www.gnu.org/software/libc/). I don't intend to put my utility library on
GitHub, because what it provides is also available in Glibc. Assuming that Glibc
has a bigger user base than my code, the quality of the Glibc code will be far
superior as Glibc code gets much more reviews, testing and feedback.

Notes
=====

As I never really was able to wrap my head around Automake, I went back to a
hand-written Makefile. I kept configure, though. This is the way it is done in
the Git sourcecode and as Git's sourcecode is a good example of a clean build
setup, I tried to modell my Makefile after it.

As the not-so-successful use of Automake in recent years surely weakenend my
Makefile writing skills, the Makefile surely leaves room for improvment, but it
works and I think it's a good starting point.
