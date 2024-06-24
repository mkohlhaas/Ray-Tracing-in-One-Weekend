```shell
|main ✗|→ n=1
|main ✗|→ h=900
03:41:18 schmidh@pc1 build ±|main ✗|→ time parallel ./raytracer -s {1} -n {2} -w {3} -h {4} -o {1}.pnm ::: $(seq 0 $n $(echo "$h - $n" | bc)) ::: $n ::: 1600 ::: $h
...
real    12m46.431s
user    201m56.996s
sys     0m11.694s
```
