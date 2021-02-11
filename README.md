# interval-timer

*A multi-threaded, POSIX compliant, high precision interval timer for your terminal*

## Compilation

### GCC
`gcc main.c -lpthread` 
### TCC
`tcc main.c -lpthread`

## Syntax

interval-timer \[flags\] \[interval length\] \[interval count\]

## Performance

| Interval length (Seconds) | Interval count | Time (MM:SS.sss) | Ideal Time (MM:SS.sss)| Drift (MM:SS.sss) |       Error (%)       |
| :-----------------------: | :------------: | :--------------: | :-------------------: | :---------------: | :-------------------: |
|            05             |       02       |    00:10.003     |       00:10.000       |     00:00.003     |   0.03%               |
|            60             |       30       |    30:00.210     |       30:00.000       |     00:00.210     |   0.007%              |

The longer you run the program, the more accurate it becomes, curiously. Using threads also reduced my time drift over 30 minutes from 15 seconds to 0.21 seconds, a 98.6% decrease.
