# simul_furuta

Quanser Rotary Inverted Pendulum simulator

* Version 1, January 2020

----
## Authors

* Francesco Petracci (petracci.francesco@gmail.com)
* Simone Silenzi  (s.silenzi1@gmail.com)

License: GPL 3.0

----
## Instructions

### Prerequisites

* Quad-core processor
* GNU GCC
* Allegro 4 libraries
* CMake 3.1+

### Compiling

To compile the library the first time, enter the main `simul_furuta` folder
(from now identified with `simul_furuta/`) and type:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

this produces the executable `simul_furuta/build/simul_furuta`.

Before doing that, make sure you have already installed
the Allegro library, version 4 (http://liballeg.org/download.html). On
Ubuntu systems, you can install it with

```
  sudo apt-get install liballegro4-dev
```

Once you compiled the sources, remember to become **super-user**,
otherwise Linux will not allow you to create real-time tasks!
