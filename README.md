# causets

Numerical exploration of causal set quantum gravity: Poisson sprinkling,
the Myrheim-Meyer dimension estimator, and (in progress) the
Benincasa-Dowker-Glaser discrete action, in C++.

## What is this

Causal sets are one of the contemporary methods employed in a quest to develop a good theory of quantum gravity (underqualified to know what 'good' would mean here) fundamentally based on the idea of constructing continuum space-times starting with the fundamental notion of causality embodied in the structure of causal sets. These are, in a sense, a statistically 'nice' discretization of the space-time continuum, leaving only the causal structure of its partially ordered set and its size and building the dynamics on it, eventually giving back the continuum space-time dynamics under the continuum approximation. (For more info, try this instead: Prof. Surya's Living Reviews [arXiv:1903.11544](https://arxiv.org/abs/1903.11544).)

This is a small project undertaken to understand and explore the numerical aspects of causal set quantum gravity using a simple example in C++. Aspects like Poisson sprinkling, estimation of the Myrheim-Meyer dimension, and (in progress) the Benincasa-Dowker-Glaser discrete action are implemented in small dimensions (2, and hopefully 3, 4). 

This repository aims to build an easily accessible and reproducible C++ build to accomplish the above numerical physics tasks.

## Status / Scope

**This project reproduces known results purely for educational purposes of a personal learning exercise.**

Implemented:
- Poisson sprinkling into a 2d causal diamond (light-cone coordinates)
- Causal matrix construction and ordering fraction
- Myrheim-Meyer dimension estimator (Myrheim 1978; Meyer 1988), inverted
  numerically via bisection

Planned:
- Sprinkling into 3d and 4d Minkowski diamonds
- Order intervals / link counting (bitset + popcount)
- Benincasa-Dowker-Glaser discrete action (Benincasa & Dowker 2010)
- (Stretch) Metropolis MCMC over 2d orders, looking for the continuum /
  non-continuum transition (Surya 2011, arXiv:1110.6244)

## Build (Linux :))
In terminal or such
```bash
git clone <your-repo-url>
cd causets
mkdir build && cd build
chmod +x build.sh
chmod +x run.sh
source build.sh
source run.sh
``` 
**First time onwards only the the last two lines need to be executed from the causets folder.**

No external dependencies beyond a C++17 compiler and CMake 3.16+.
Python (numpy, matplotlib) is used separately for plotting scripts under
`scripts/` — see that directory for setup once added (means not present yet).

## Build (Windows :()

### Option A: Visual Studio (MSVC)

Requires [Visual Studio](https://visualstudio.microsoft.com/) (Community
edition is fine) with the "Desktop development with C++" workload
installed, which includes both the MSVC compiler and CMake support.

From a "Developer Command Prompt for VS" (search for it in the Start
menu — this ensures the compiler is on your PATH):

```cmd
git clone <your-repo-url>
cd causets
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

The executable will be at `build\Release\causets.exe`. Adjust the
generator string if you have a different Visual Studio version (e.g.
`"Visual Studio 16 2019"`); run `cmake --help` to list generators
available on your machine.

Alternatively, if you have the CMake extension in VS Code, you can open
the repo folder directly, select a kit (MSVC), and build via the
CMake Tools sidebar without touching the command line.

### Option B: WSL (Windows Subsystem for Linux :|)

If you have [WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
set up (Ubuntu is the default distribution), the Linux build
instructions above apply unchanged inside your WSL terminal:

```bash
sudo apt update && sudo apt install build-essential cmake git
git clone <your-repo-url>
cd causets
mkdir build && cd build
chmod +x build.sh
chmod +x run.sh
source build.sh
source run.sh
```

This is the more consistent option if you also plan to use the Python
plotting scripts, since the whole toolchain (compiler, CMake, Python
venv) behaves identically to a native Linux setup.

**Windows build via MSVC is provided but not yet tested on this project; please open an issue if you hit problems.**

## Results

Sprinkling N points (Poisson-distributed, mean rho*V) into a 2d causal
diamond via light-cone coordinates, and estimating the dimension from
the ordering fraction r = 2R/(N(N-1)) via Meyer's relation

    r(d) = Gamma(d+1) Gamma(d/2) / (2 Gamma(3d/2))

inverted numerically by bisection. Over 20 independent sprinklings at
density ρ = 5000:

    r    = 0.500139 ± 0.500139
    d_MM = 1.99963  ± 0.0116437

consistent with the input dimension of 2, expected much ? :/.

More to follow



## Repository structure

```
src/sprinkle.hpp/.cpp   - Poisson sprinkling into a causal diamond
src/causet.hpp/.cpp     - causal matrix construction, ordering fraction
src/dimension.hpp/.cpp  - Myrheim-Meyer dimension estimator (bisection)
src/main.cpp            - orchestration (magic happens here :) )
```



## Limitations

Still Discovering :)

## References

- J. Myrheim, "Statistical geometry" (1978)
- D. Meyer, PhD thesis, MIT (1988)
- D. Benincasa, F. Dowker, "The Scalar Curvature of a Causal Set,"
  arXiv:1001.2725
- (main)S. Surya, "The causal set approach to quantum gravity," Living Reviews
  in Relativity, arXiv:1903.11544

## License

MIT
