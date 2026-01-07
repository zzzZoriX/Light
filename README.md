# Light

## What is it?
### Light is a memory sanitizer for C/C++ code. It checks your code to find memory leaks, potential segmentation faults, and addressing errors

## How it use?
### 1. Open the command line
### 2. Enter: light check
### 3. List all the files you want to check

# Examples

## Test example 1:
### input.cpp:
``` C++
int main() {
    int* test_ptr = new int;

    return 0;
}
```

### result output:
``` cmd
light check -cpp input.cpp

potencial memory leak on line 2:
2   int* test_ptr = new int;
memory is not freed

possible solution:
2   int* test_ptr = new int;
3   delete test_ptr;
```

## Test example 2:
### input.cpp:
``` C++
int main() {
    int* test_ptr = new int;

//  some work with "test_ptr"

    delete test_ptr;

    int new_var = *test_ptr;

    return 0;
}
```

### result output:
``` cmd
light check -cpp input.cpp

Segmentation fault on line 8:
8   int new_var = *test_ptr;
is pointer to NULL

posible solution:
8   ~~int new_var = *test_ptr;~~
```

## Test example 3:
### input.cpp:
``` C++
int main() {
    int array[3] = {1, 2, 3};
    int fourth_elem = array[3];

    return 0;
}
```

### result output:
``` cmd
light check -cpp input.cpp

index out of range on line 3:
3   int fourth_elem = array[3];
an array size is 3, index 3 is out of range

possible solution:
3   int fourth_elem = array[2];
```


# Other info

## Light's commands:
### 1. check <input> ...
Checks the input file(s) for any memory errors, as shown in the test examples

### 2. version
Shows the current version of the Light API

## Light's flags
### 1. -cpp 
Tells Light that the input file is a C++ file, which means Light will also check new/delete keywords

### 2. -Nleak
tells Light's that memory leaks don't need to be checked

### 3. -Nsegs
tells Light's that potential segmentation faults don't need to be checked

### 4. -Naddr
tells Light's that address errors don't need to be checked

### P.S.: Flags 2-4 are used to speed up checking by skipping unnecessary checks