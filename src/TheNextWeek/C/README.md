# README

```shell
cd build
rm fu*
ninja
./raytracer > fu.pnm
feh
```

- provide `object*` as separate input parameter for hit functions not in hit record parameter
- reduce malloc calls!
  - maybe in hit_fn_t ray should be a pointer
- Notes:
  - inline seems to be `obsolete`
    - disassembly code in gdb with 'layout asm'
    - compiler in-lines in release build automagically
  - performance debug : release = 2 : 1 (release build needs half of debug's execution time)
  - rr debug
