# README

```shell
cd build
rm fu*
ninja
./raytracer > fu.pnm
feh
```

- command line arguments (file, scanline#)
- write to file (instead of stdout)
- hitlist as hittable (with hit() function)
- GNU Parallel & pamcat from netpbm
