# GTK

https://openhome.cc/Gossip/GTKGossip/GTKUnderUbuntu.html

```
$ sudo apt-get install build-essential
$ sudo apt-get install libgtk2.0-dev
$ pkg-config --cflags --libs gtk+-2.0
```

## 在 win10 的 bash 底下執行的結果。

```
ccckmit@DESKTOP-96FRN6B:/mnt/d/Dropbox/code/c/linux/gtk$ gcc helloGtk.c -Wall -ansi -o helloGtk.o `pkg-config --cflags --libs gtk+-2.0`
ccckmit@DESKTOP-96FRN6B:/mnt/d/Dropbox/code/c/linux/gtk$ ./helloGtk.o

(helloGtk.o:9721): Gtk-WARNING **: cannot open display:
```