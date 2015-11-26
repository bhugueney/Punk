# Punk 
## Simplicity Tool Kit

Punk, It is a group of commands line tools, to solve Np-Complete & NP-Hard Problems Easy, 
they are founded, in the ABSTRACT BINARY SEARCH, 
result of 2 years of research, on the universal theory of numbers. 

See ABS in Action https://www.youtube.com/watch?v=NlkiWQ9QNBo

Punk-Research = Independent + Anarchist + Knowledge

(Also Visit: Research for Supercomputing on Standard Machines
https://github.com/maxtuno/Etudes-on-Supercomputing)

About Me: <Oscar Riveros> 
I'm just what time...

The binaries included are for OS X, you need compile the files for you OS, for SHA3 cracker its necessary Crypto++,

TIP: Optimize Compilation Parameters

![Punk](https://raw.githubusercontent.com/maxtuno/Punk/master/logo.png)

The license in simple terms, says that you can use freely, while respecting the authorship of the technology,
and mention explicitly its author, when deal with commercial purposes, this includes universities and companies, 
provided they have express permission of Oscar Riveros <oscar.riveros@gmail.com> for profit with this algorithm, technology and knowledge.
and should always include the following license:

Their use for purposes contrary to the law, is expressly prohibited only allowed legal use.

EXPLICIT LICENCE 

Copyright (c) 2015+ Oscar Riveros. All rights reserved. oscar.riveros@gmail.com
Without any restriction, Oscar Riveros reserved rights, patents and
commercialization of this knowledge and which derive directly from this work.

http://maxtuno.github.io/Punk

http://twitter.com/maxtuno

http://www.reverbnation.com/maxtuno

http://soundcloud.com/maxtuno

http://www.jango.com/music/Oscar+Riveros

http://mx-clojure.blogspot.cl

http://independent.academia.edu/oarr

https://github.com/maxtuno/Phi

# Problems

(See the examples on bin folder for each tool.)

## SSP & SSP_CLUSTER

Subset Sum Problem

Usage: ./abs_ssp universe<path> log<0|1>

universe: 1º value of file is the target, the rest are the set. (only sets no mult-isets)

## OR

Usage: ./abs_or universe<path> pallete<path> zero<number> <0|1>(min, max) log<0|1>

An system [0, 1, -10, 30, 40, 0, 0, 20] with inputs and outputs, 0 are dynamics, 
and can be replaced by any element of the palette, [3, 7, 10, -1, -7],
You need find the minimal or maximal, around a predefined 0, (for example if you need al most 100 on your system and need to find the min, your zero is 100),

(This problem is of my authorship)

## MCP

Usage: ./abs_mcp universe<path> log<0|1>

Separate an set in two set with the same size and same sum. (only sets no mult-isets)

Maximum Constrained Partition (https://www.nada.kth.se/~viggo/wwwcompendium/node152.html)
   

## CRACKER

SHA3 Cracker

Usage: ./abs_cracker hash<path> alphabet<path> kel<number> ker<number> algorithm<224|256|384|512> log<0|1>

hash: File with hashes

alphabeth: a, b, c, d... 1, 2, 3... A, B, C... =)(... etc... (writhe on plain text)

kel, ker: try by yourself, but with 0, 0 is ok (a lot can be shortened with suitable values, time to resolution).

algorithm: SHA3_224, SHA3_256, SHA3_384, SHA3_512 (write only 224, 256, 384, 512)

log: visual loging... 


## PRIMALITY

Composite Number Problem
 
Badass primality test, include all the RSA numbers from wiki, for test.
 
Usage: ./abs_primality numbers<path>
