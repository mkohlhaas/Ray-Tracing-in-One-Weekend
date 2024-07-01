# README

```shell
cd build
rm fu*
ninja
./raytracer > fu.pnm
feh
```

- reread book and comment code

  - ray should be part of hit_record_t
  - set ray and object in hit_record_t before calling hit functions

- Notes:
  - inline seems to be `obsolete`
    - disassembly code in gdb with 'layout asm'
    - compiler in-lines in release build automagically
  - performance debug : release = 2 : 1 (release build needs half of debug's execution time)
