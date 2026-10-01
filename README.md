# causets

Numerical exploration of causal set quantum gravity: Poisson sprinkling,
the Myrheim-Meyer dimension estimator, and (in progress) the
Benincasa-Dowker-Glaser discrete action, in C++.

## What is this

Causal sets are one of the contemporary methods employed in a quest to develop a good theory of quantum gravity fundamentally based on the idea of constructing continuum space-times starting with the fundamental notion of causality embodied in the structure of causal sets. These are, in a sense, a statistically 'nice' discretization of the space-time continuum, leaving only the causal structure of its partially ordered set and its size and building the dynamics on it, eventually giving back the continuum space-time dynamics under the continuum approximation. (For more info, try this instead: Prof. Surya's Living Reviews [arXiv:1903.11544](https://arxiv.org/abs/1903.11544).)

This is a small project undertaken to understand and explore the numerical aspects of causal set quantum gravity using a simple example in C++. Aspects like Poisson sprinkling, estimation of the Myrheim-Meyer dimension, and (in progress) the Benincasa-Dowker-Glaser discrete action are implemented in small dimensions (2, and hopefully 3, 4). 

This repository aims to build an easily accessible and reproducible C++ build to accomplish the above numerical physics tasks.

## Status / Scope

**This project reproduces known results purely for educational purposes of a personal learning exercise.**

Implemented:
- Poisson sprinkling into a 2d causal diamond (light-cone coordinates)
- Causal matrix construction and ordering fraction
- Myrheim-Meyer dimension estimator (Myrheim 1978; Meyer 1988), inverted
  numerically via bisection
- Order intervals / link counting (bitset + popcount)

Planned:
- Sprinkling into 3d and 4d Minkowski diamonds
- Benincasa-Dowker-Glaser discrete action (Benincasa & Dowker 2010)
- (Stretch) Metropolis MCMC over 2d orders, looking for the continuum /
  non-continuum transition (Surya 2011, arXiv:1110.6244)

## Build (Linux :) )
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

## Build (Windows :( )

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

### Option B: WSL (Windows Subsystem for Linux :| )

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

    r = 0.498732 ± 0.00460209
    d_MM = 2.00338 ± 0.0122988

consistent with the dimension of 2, expected much ? :/ .

### Order interval counting: naive vs. bitset+popcount

Counting the order interval size |I(x,y)| for every related pair
(needed for N_0, N_1, N_2, ... and ultimately the BDG action) is
naively O(N^3). A bitset-packed representation of the causal matrix
(64 elements per 64-bit word), combined with AND + __builtin_popcountll,
reduces the constant factor by roughly 64x while leaving the underlying
O(N^3) complexity unchanged.

Verified exact agreement between the naive (`ord_intrv`) and fast
(`ord_intrv_fast`) implementations across N ~ 1000-8000 (see
tests/test_causet.cpp and the correctness check in main.cpp).

| N    | Naive runtime | Bitset runtime | Speedup |
|------|---------------|-----------------|---------|
| 1002 | 0.185 s       | 0.014 s         | 13.2x   |
| 1926 | 1.40 s        | 0.086 s         | 16.3x   |
| 3919 | 17.6 s        | 0.673 s         | 26.2x   |
| 7925 | 146.0 s       | 5.07 s          | 28.8x   |

The speedup increases with N and approaches the theoretical ~64x
ceiling as fixed per-call overhead becomes negligible relative to the
O(N) per-pair inner loop being replaced by an O(N/64) one.

More to follow

## Repository structure

```
src/sprinkle.hpp/.cpp   - Poisson sprinkling into a causal diamond
src/causet.hpp/.cpp     - causal matrix construction, ordering fraction, order interval calculation
src/dimension.hpp/.cpp  - Myrheim-Meyer dimension estimator (bisection)
src/main.cpp            - orchestration (magic happens here :) )
tests/test_causet.cpp	- unit tests: hand-built 4-element causet checks, naive vs. bitset interval-count cross-validation
```

## Limitations

- Only implements 2D yet.
- As of yet has O(N^3) complexity (although reduced somewhat using bitset optimization).

More to be added as I move forward.

## References

- J. Myrheim, "Statistical geometry" (1978)
- D. Meyer, PhD thesis, MIT (1988)
- D. Benincasa, F. Dowker, "The Scalar Curvature of a Causal Set,"
  arXiv:1001.2725
- (main)S. Surya, "The causal set approach to quantum gravity," Living Reviews
  in Relativity, arXiv:1903.11544

## License

MIT
