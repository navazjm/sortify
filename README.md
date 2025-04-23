# Sortify

> 🚧 WIP: Currently tested only on ARM macOS.

## Table of Contents
- [Quick Start](#quick-start)
- [Overview](#overview)
- [Install](#install)
    - [Install From Source](#install-from-source)
- [Contributing](#contributing)
- [License](#license)

## Quick Start

### Step 1: Get Sortify binary file on your system. Checkout how to [install](#install) Sortify below.

_More detailed usage steps will be added as development progresses._

## Overview

Sortify is a simple, lightweight C application that visualizes popular sorting
algorithms in real time. Built using [alfredbaudisch/raylib-cimgui](https://github.com/alfredbaudisch/raylib-cimgui),
the program provides an interactive way to explore, learn, and understand the
inner workings of classic sorting techniques.

Whether you're a student, educator, or just a curious developer, this visualizer
makes it easy to see how data moves and transforms during each step of a sorting process.

### Supported Algorithms

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort

## Install

### Install From Source

1. Clone the repo:

```sh 
git clone https://github.com/navazjm/sortify.git
```

2. Navigate into the project directory:

```sh 
cd sortify
```

#### MacOS & Linux

Either run the install script or manually build with CMake

##### Script

1. Run the install script 

```sh 
./scripts/install.sh
```

> 💡 Note: The install script runs the commands found in the following CMake section.

##### CMake  

1. Configure the project and generate build files:

```sh 
cmake -S . -B build/release
```

2. Build and install the binary:

```sh 
sudo make install -C build/release
```

> 💡 Note: sudo is used to move the sortify binary to /usr/local/bin/, allowing you to run sortify from anywhere.

## Contributing 

Want to contribute to Sortify? Awesome — we’d love your input ♥ 

If you have a feature request, start a [discussion](https://github.com/navazjm/sortify/discussions),
and we can work together to incorporate it into Sortify! 

Encountered a defect? Please report it under [issues](https://github.com/navazjm/sortify/issues).
Be sure to include detailed information to help us address the issue effectively. 

Want to implement a feature request or fix a defect? Checkout our [contributing guide](./docs/contributing.md).

## License

Sortify is licensed under [MIT](./LICENSE)
