# README

```shell
cd build
rm fu*
ninja
./raytracer > fu.pnm
feh
```

- subdirectories for scenes and textures
- check return values of mallocs (are they leading to immediate failure or returned back to calling functions?)
- reduce malloc calls!
  - maybe in hit_fn_t ray should be a pointer
- Notes:
  - inline seems to be `obsolete`
    - disassembly code in gdb with 'layout asm'
    - compiler in-lines in release build automagically
  - performance debug : release = 2 : 1 (release build needs half of debug's execution time)
  - rr debug
    - [Debugging with rr: Start at the End](https://www.youtube.com/watch?v=S6EQiSu_zNI&t=373s&pp=ygUTcnIgc3RhcnQgYXQgdGhlIGVuZA%3D%3D)
    - [rr Time-Traveling Debugger](https://www.youtube.com/watch?v=eOrpuc89baE)
  - GDB:
    - [GDB Documentation](https://www.sourceware.org/gdb/documentation/)
    - [GDB Getting Started](https://developers.redhat.com/articles/the-gdb-developers-gnu-debugger-tutorial-part-1-getting-started-with-the-debugger)
    - [Printf Style Debugging using GDB, Part 1](https://developers.redhat.com/articles/2021/10/05/printf-style-debugging-using-gdb-part-1)
    - [Printf Style Debugging using GDB, Part 2](https://developers.redhat.com/articles/2021/10/13/printf-style-debugging-using-gdb-part-2)
    - [Printf Style Debugging using GDB, Part 3](https://developers.redhat.com/articles/2021/12/09/printf-style-debugging-using-gdb-part-3)
    - [Debug Info](https://developers.redhat.com/articles/2022/01/10/gdb-developers-gnu-debugger-tutorial-part-2-all-about-debuginfo#)
    - [Learn How to use Breakpoints](https://developers.redhat.com/articles/2022/11/08/introduction-debug-events-learn-how-use-breakpoints#what_is_a_breakpoint_)
  - Performance: By introducing u,v coords in hit_record performance goes from 1:23m to 1:49m !!!
