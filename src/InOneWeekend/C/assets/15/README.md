```shell
03:11:42 schmidh@pc1 build ±|main ✗|→ n=15
03:13:04 schmidh@pc1 build ±|main ✗|→ h=900
03:13:13 schmidh@pc1 build ±|main ✗|→ time parallel ./raytracer -s {1} -n {2} -w {3} -h {4} -o {1}.pnm ::: $(seq 0 $n $(echo "$h - $n" | bc)) ::: $n ::: 1600 ::: $h
...
real    13m11.521s
user    195m37.894s
sys     0m4.736s
```
