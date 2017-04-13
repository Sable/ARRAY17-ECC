# Experiments of ECC compiler

Content

- [Introduction](#introduction)
- [Configuration](#configuration)
- [Benchmarks](#benchmarks)
- [Feedback](#feedback)

## Introduction

This repository contains all benchmarks used in our paper "*An ELI-to-C
Compiler: Design, Implementation and Performance*". Each benchmark has at least
three versions: **C**, **ELI**, and **ECC**. (See [configuration](#configuration))

There two experiments we conducted in our paper.  The first experiment consists of
three benchmarks: [black-scholes](#black-scholes), [k-means](#k-means) and
[hotspot](#hotspot) are from popular benchmarks, which are originally written
in C.  We manually translate the code to ELI code which is later compiled by
the ECC.

The second experiment has another two benchmarks: [morgan](#morgan) and
[rprime](#rprime) are inherited from APL code.  APL and ELI are both array
programming languages.  Therefore, the two benchmarks are quite different from
the above three benchmarks.  We manually translate the code from ELI to C while
maintain its consistency.

We used a language to implement its compiler within itself.  Our compiler
(ECCE) was first written in ELI.  The ECCE was designed to emit C code based on
the ELI interpreter. In order to provide an indepdent ELI compiler, we
conducted bootstrapping to compile the ECCE to an functionally equivalent
compiler in C code.  Finally, an executable file was generated after compiled
by the GNU GCC compiler.  This compiler can compile ELI code to C code
without the help of the ELI interpreter, called **ECC**.

## Configuration

System information

- Name : Lynx
- OS   : Ubuntu 16.04.2 LTS
- GCC  : 5.4.0
- ELI  : v0.1a [download](http://fastarray.appspot.com/eli_linux_0.1a.tar.gz)

Data download

- Experimental data [[download, 163MB](http://www.sable.mcgill.ca/~hanfeng.c/array17/experiment-data.tar.gz)] (After unzipped, about 4GB)
- Source code [[download](/releases/latest)]

Benchmark versions:

    - [x] C       : C code
    - [x] ECC     : ECC-generated C code
    - [x] ELI     : ELI code
    - [x] C-Opt   : Optimized C code (i.e. hotspot)
    - [x] ECC-Opt : Optimized ECC-generated C code (i.e. rprime)

## Benchmarks

1. [black-scholes](#black-scholes)
2. [k-means](#k-means)
3. [hotspot](#hotspot)
4. [morgan](#morgan)
5. [rprime](#rprime)

### black-scholes

black-schole is a mathematical model of a financial market containing certain
derivative investment instruments.

Source: [Princeton PARSEC](http://parsec.cs.princeton.edu/download.htm)


### k-means

k-means clustering is a method of vector quantization originally from signal
processing, that is popular for cluster analysis in data mining.

Source: [Rodinia 2.3](http://lava.cs.virginia.edu/Rodinia/)


### Hotspot

hotSpot is a widely used tool to estimate processor temperature based on an
architectural floorplan and simulated power measurements.

Source: [Rodinia 2.3](http://lava.cs.virginia.edu/Rodinia/)


### morgan

The morgan benchmark comes from a financial application.  It has two functions:
*msum* and *morgan*, where morgan is the main function.


    @.r<-n msum a
    r<-((0,n-1)!.t)-0,(0,-n)!.t<-+\a
    @.

    @.r<-n morgan a;x;y;sx;sx2;sy;sy2;sxy
      x<-a[1;;]
      y<-a[2;;]
      sx<-n msum x
      sy<-n msum y
      sx2<-n msum x *. 2
      sy2<-n msum y *. 2
      sxy<-n msum x *  y
      r<-((sxy%n)-(sx*sy)%n*.2)%(|((sx2%n)+(sx%n)*.2)*.0.5)*(|(sy2%n)-(sy%n)*.2)*.0.5
    @.


### rprime

Give an integer number *n*, *rprime* finds all prime numbers up to n.

Input scale:

    100K 200K 400K 800K

## Feedback

Please contact [Hanfeng](mailto:hanfeng.chen@mail.mcgill.ca).

