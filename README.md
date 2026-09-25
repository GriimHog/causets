# causets

Numerical exploration of causal set quantum gravity: Poisson sprinkling,
the Myrheim-Meyer dimension estimator, and (in progress) the
Benincasa-Dowker-Glaser discrete action, in C++.

## What is this

Causal sets are one of the contemporary methods employed in a quest to develop a good theory of Quantum Gravity (underqualified to know what 'good' would mean here) fundamentally based on the idea of constructing continuum space-times starting with the fundamental notion of causality embodied in the structure of causal sets. These are in a sense a statistically 'nice' discretization of the space-time continuum leaving only the causal structure of its partially-ordered set and its size and building the dynamics on it, eventually giving back the continuum space-time dynamics under the continuum approximation. (For More info try this instead: Prof.Surya's Living Riviews arXiv:1903.11544)

This is a small project undertaken to understand and explore the numerical aspects of causal set quantum gravity using a simple example in C++ by reprodu . Aspects like Poisson sprinkling, estimation of the Myrheim-Meyer dimension , and (in progress) the Benicasa-Dowker-Glaser discrete action are implemented in small dimensions (2,(and hopefully) 3, 4). 

**This repository aims to build a easily accessible and reproducible C++ build to accomplish the above numerical physics tasks.**

## Status / Scope

**This project reproduces known results purely for educational purposes of a personal learning exercise. Don't go thinking it has any bit of novelty here. :) **

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

## Build
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

No external dependencies beyond a C++17 compiler and CMake 3.16+.
Python (numpy, matplotlib) is used separately for plotting scripts under
`scripts/` — see that directory for setup once added (means not present yet).

## Results

Sprinkling N points (Poisson-distributed, mean rho*V) into a 2d causal
diamond via light-cone coordinates, and estimating the dimension from
the ordering fraction r = 2R/(N(N-1)) via Meyer's relation

    r(d) = Gamma(d+1) Gamma(d/2) / (2 Gamma(3d/2))

inverted numerically by bisection. Over 20 independent sprinklings at
density ρ = 5000:

    r    = 0.500139 ± 0.500139
    d_MM = 1.99963  ± 0.0116437

consistent with the input dimension of 2, expected much ? :|.

<!-- TODO: fill in as each milestone completes. Include the actual numbers,
not placeholder text. Example shape for the 2d Myrheim-Meyer result:

### Myrheim-Meyer dimension in 2d Minkowski space

Sprinkling N points (Poisson-distributed, mean rho*V) into a 2d causal
diamond via light-cone coordinates, and estimating the dimension from
the ordering fraction r = 2R/(N(N-1)) via Meyer's relation

    r(d) = Gamma(d+1) Gamma(d/2) / (2 Gamma(3d/2))

inverted numerically by bisection. Over N independent sprinklings at
density rho = ...:

    r    = <mean> +/- <stdev>
    d_MM = <dmm>  +/- <stddmm>

consistent with the input dimension of 2, as expected.

As a sanity check, r(d=2) evaluates to <value> and inverting r=0.5
exactly returns d=<value>, confirming the Gamma-function expression and
bisection routine are consistent independent of sprinkled data.

-->

## Repository structure

```
src/sprinkle.hpp/.cpp   - Poisson sprinkling into a causal diamond
src/causet.hpp/.cpp     - causal matrix construction, ordering fraction
src/dimension.hpp/.cpp  - Myrheim-Meyer dimension estimator (bisection)
src/main.cpp            - orchestration (magic happens here :) )
```

<!-- Update as files are added, e.g. action.hpp/.cpp, tests/. -->

## Limitations

<!-- TODO: be specific and honest. What haven't you done, what are you
unsure about, what would a domain expert ask about that isn't addressed
yet? E.g., right now: only 2d is implemented; error propagation on d_MM
uses a simple +/- sigma_r -> d shift rather than a full statistical
treatment; no BDG action yet; no unit tests yet. -->

## References

- J. Myrheim, "Statistical geometry" (1978)
- D. Meyer, PhD thesis, MIT (1988)
- D. Benincasa, F. Dowker, "The Scalar Curvature of a Causal Set,"
  arXiv:1001.2725
- (main)S. Surya, "The causal set approach to quantum gravity," Living Reviews
  in Relativity, arXiv:1903.11544
<!-- Add further references as later milestones pull in new papers,
e.g. Surya arXiv:1110.6244 for the MCMC stretch goal. -->

## License

MIT
