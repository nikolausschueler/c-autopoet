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

An example
==========

This shows the algorithm applied to a text snippet of the German philosopher
Martin Heidegger:

```
Das Dasein ist ein Seiendes, das nicht nur unter anderem Seienden vorkommt. Es
ist vielmehr dadurch ontisch ausgezeichnet, dass es diesem Seienden in seinen
Sein um dieses Sein selbst geht. Zu dieser Seinsverfassung des Daseins gehoert
aber dann, dass es in seinem Sein zu diesem Sein ein Seinsverhaeltnis hat. Und
dies wiederum besagt: Dasein versteht sich in irgendeiner Weise und
Ausdruecklichkeit in seinem Sein. Diesem Seienden eignet, dass mit und durch
sein Sein dieses ihm selbst erschlossen ist. Seinsverstaendnis ist selbst eine
Seinsbestimmtheit des Daseins. Die ontische Auszeichnung des Daseins liegt
daran, dass es ontologisch ist.
```

Save the text to a file and run the program with:

```
$ poet -f -w 4 heidegger.txt
```

This gives you:

```
Das Daseinem Seins liegt daran, dass es ihm selbst ein ist. Seienden in
irgendeinem Seinsverhaeltnis ist. Sein. Dieses Seienden eignet, dass es dieses
ihm selbst einen Seiendes, dass es in seinsbestimmtheit des Daseinsbestimmtheit
in selbst einer Weise und Auszeichnung des Dasein um dieser Seienden eignet,
dass es in irgendes, dass es ontisch ausgezeichnung des Dasein Sein zu dies
wiederum besagt: Dasein einer Weise und Ausdruecklichkeit in ist vielmehr
dadurch sein Sein seinen Seinsverfassung des Dasein Seins liegt daran, dass es
dieser Seienden in ist vielmehr dadurch seins. Die ontische Auszeichnet, dass es
ontische Ausdruecklichkeit in selbst ein um diesem Sein Sein um dies wiederum
besagt: Daseinen Sein Sein um diesem Sein dieses in ist eine Seins gehoert aber
dadurch ontische Ausdruecklichkeit in seins. Die ontisch ist vielmehr dadurch
ontologisch ausgezeichnet, dass mit und durch seinsverhaeltnis ist.
```

Can you spot the difference?

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
