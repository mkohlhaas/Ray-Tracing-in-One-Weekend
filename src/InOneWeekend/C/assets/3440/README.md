```shell
05:36:12 schmidh@pc1 build ±|main ✗|→ w=3440
05:36:17 schmidh@pc1 build ±|main ✗|→ h=1440
05:36:20 schmidh@pc1 build ±|main ✗|→ n=10
05:36:33 schmidh@pc1 build ±|main ✗|→ time parallel ./raytracer -s {1} -n {2} -w {3} -h {4} -o {1}.pnm ::: $(seq 0 $n $(echo "$h - $n" | bc)) ::: $n ::: $w ::: $h
...
real    43m28.924s
user    672m50.831s
sys     0m12.609s
```

```shell
for i in $(seq 0 10 1430);do echo $i.pnm;done | xargs pnmcat -tb > res.pnm
```

```shell
sed -w (0 10 1430)
```
