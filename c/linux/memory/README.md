# memory management

## mcheck

* [mcheck和mtrace使用方法](http://taotaocoder.blog.163.com/blog/static/200228274201182811405396/)


## Valgrind

* [C語言的記憶體洩漏(Memory Leak)偵測 - Valgrind](http://blog.yslin.tw/2014/03/c-valgrind.html)
  * <invalidAccess.c>
  * <memoryLeak.c>

## 在 win10 的 ubuntu linux 中測試

似乎 valgrind 失敗了，有問題！

```
ccckmit@DESKTOP-96FRN6B:/mnt/d/Dropbox/code/c/linux/memory$ valgrind --leak-check=full./memoryLeak.o
--13086:0:aspacem   -1: ANON 0038000000-00383d1fff 4005888 r-x-- SmFixed d=0x000 i=286099  o=0       (0) m=0 /usr/lib/valgrind/memcheck-amd64-linux
--13086:0:aspacem  Valgrind: FATAL: aspacem assertion failed:
--13086:0:aspacem    segment_is_sane
--13086:0:aspacem    at m_aspacemgr/aspacemgr-linux.c:1502 (add_segment)
--13086:0:aspacem  Exiting now.
```

應該是像這樣才對

```
==59095== Memcheck, a memory error detector
==59095== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
==59095== Using Valgrind-3.9.0 and LibVEX; rerun with -h for copyright info
==59095== Command: ./mem_test
==59095==
==59095==
==59095== HEAP SUMMARY:
==59095==     in use at exit: 10 bytes in 1 blocks
==59095==   total heap usage: 1 allocs, 0 frees, 10 bytes allocated
==59095==
==59095== 10 bytes in 1 blocks are definitely lost in loss record 1 of 1
==59095==    at 0x4C2C857: malloc (vg_replace_malloc.c:291)
==59095==    by 0x400505: func (mem_test.c:5)
==59095==    by 0x400514: main (mem_test.c:10)
==59095==
==59095== LEAK SUMMARY:
==59095==    definitely lost: 10 bytes in 1 blocks
==59095==    indirectly lost: 0 bytes in 0 blocks
==59095==      possibly lost: 0 bytes in 0 blocks
==59095==    still reachable: 0 bytes in 0 blocks
==59095==         suppressed: 0 bytes in 0 blocks
==59095==
==59095== For counts of detected and suppressed errors, rerun with: -v
==59095== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
