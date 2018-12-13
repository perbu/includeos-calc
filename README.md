# includeos-calc
IncludeOS Calculator - TCP based


A simple example service built on IncludeOS. Its a TCP service which takes strings though port 2000 and computes them.

Example usage: 

```
perbu:~$ nc 10.0.0.42 2000
-Welcome to the serverless calculator
-Please enter the operation to perform. Format: a+b | a-b | a*b | a/b
5/8
0.625000
perbu:~$
```