<div align="center">
    <h1>🐦‍⬛ Surveyor</h1>
</div>

UCI Chess Engine written in C++.

### Estimated playing strength:

| Version | CCRL Blitz | COPE Bullet |
|---------|------------|-------------|
| ONE.1   | 2830*      | 2854        |

*Rough estimate based on games of known playing strength.

### Building

To build, simply use the makefile provided.

```shell
# native (both do the same)
make
make native

# avx2-bmi2
make avx2-bmi2

# x86-64
make x86-64
```

It is strongly recommended to use avx2-bmi2 at a minimum. Building as native will maximise
the speed of the program on your machine, but will produce a less portable buid.

### Non standard UCI commands:
 - go softtime \<ms\>
 - go softnodes \<nodes\>
 - go harddepth \<depth\>
 - bench
 - perft \<depth\> [standard]

### Acknowledgements
 - Lily (87Flowers), Lofty and Clockwork Authors for help and references for attack board style board representation.
 - Ciekce, Nanopixel and Stockfish Authors for references for search.
 - Naman Thanki for assisting with Windows builds.
