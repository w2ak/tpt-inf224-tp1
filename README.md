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

## Step 6

To avoid encapsulation problems, the problem was solved as follows:
* `setChapters([...],n)` copies the array instead of just getting the pointer
* `getChapter(i)` gives only the length of one chapter. It is given by value and not reference.

## Step 7

In the code, almost every object field is correctly destroyed when an object is destroyed. The only problematic field is the chapter array in `Movie` objects, which has to be created and should then be destroyed when a Movie object is destroyed or when the chapters list is changed.

Therefore, if you change the code of `Movie`, copy a `Movie` object then destroy one of theese two objects, you will destroy the chapter list in the second object that you did not destroyed. Furthermore you will probably have a segmentation fault when trying to destroy the second `Movie` object and destroying the chapters list a second time.

## Step 8

Template specialization was used to create `Group<X>` for `X` a subclass of `Multimedia`.
We have to create this class as a subclass of `list<X*>` and not `list<X>` for two reasons:
* Multimedia objects can be members of multiple groups.
* `list<Multimedia>` is virtual and cannot be instantiated. This would not allow us to create groups of Videos and Pictures in the same group.

### Step 8.1

Template specialization was not needed. We do not need the program to work if someones tries to use `Group<X>` for `X` not a subclass of `Multimedia`.

### Step 8.2

Added a few corrections. By using `const` it is possible to tell the compiler when something should not be (or will not be) modified.

## Step 9

Shared pointers allow memory to be managed correctly. `Group` is now a list of shared pointers. This way, even though groups can share `Multimedia` objects, these objects are only deleted when they are not used anymore.
