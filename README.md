# Verbatim

An encoding scheme!


Imagine a word, and the word is "jamie".


and we want to encode it to the scheme ['v', 'e', 'r', 'b', 'a', 't', 'i', 'm']

```
v = 0
e = 1
r = 2
b = 3
a = 4
t = 5
i = 6
m = 7
```
jamie->


106, 97, 109, 105, 101 -> // in ascii values


1101010, 1100001, 1101101, 1101001, 1100101


110 (bits 37-39) is 6, translate to i


101 (bits 36-38) is 5, translate to t


011 (bits 33-35) is 3, translate to b


and so on. we can transform the word "jamie" into "brtaeiimrbat".


Check it out!
