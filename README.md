# tpt-inf224-tp1

![Télécom ParisTech][tpt]

INF 224 - Paradygmes de programmation

TP n° 1

[tpt]: https://www.telecom-paristech.fr/fileadmin/maq14/img/logo.png

# Building and Running

## Build the program

```
make
```

## Build the documentation

```
make doc
```

## Download the media files

```
make media
```

## Run the program

```
./tp1
```

```
make run
```

## Open the documentation

```
chromium-browser doc/html/index.html
```

## Clean build files

```
make clean
```

```
make cleandist
```

## Create release archive

```
make release
```

# Notes about the practical

## Step 4

The `open` method in `Multimedia` will be virtual, which makes it impossible to instantiate `Multimedia` objects.

## Step 5

Polymorphism is used to make the treatment independant of the subclass. Destructors of polymorphic classes must be virtual.
