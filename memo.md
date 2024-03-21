# Memo
Just stuff to remember from the process.


## Setting c++ version

It seems like the real problem was to use gnu++ instead of c++ when setting version.
Annoying...

This was not the problem: (
When compiling with c++17 on esp32 i got a strange error in a file called 
portmacro.h.

I found [this page](https://community.platformio.org/t/static-assert-asserting-when-true/24654/4)
that talks about it.

The fix seem to be to specify the exact version of the platform
)

## Venv

```
sudo apt install python3-venv 
```


