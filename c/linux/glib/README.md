# glib

* https://www.linuxhelp.com/how-to-install-glib-2-0-on-ubuntu-17-04/

```
$ sudo apt-get install glib2.0 -y
```

* https://askubuntu.com/questions/108814/glib-h-no-such-file-or-directory-error-despite-installing-libglib2-0-dev

```
$ gcc hashtable.c -Wall -o hashtable `pkg-config --cflags --libs glib-2.0`
$ ./hashtable
```