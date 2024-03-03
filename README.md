## Monte carlo methods in physics course
Folders contain neccessary files with description and simple gnuplot script generating images.

## Overall information about programs:
* bernoulli_distribution - calculates expected values and variance of Bernoulli distribution.
* correlated_distribution_2D - generates 2D random distributions in circle and elipse along with covariance matrix.
* random_generator_1D - generates 1D random distributions for given pdf using 3 methods. 
* simple_integration - calculates the common area of 2 overlapping 2D random distributions.
* systematic_and_stratified_integration - calculates the value of given integral using 3 methods.
* diffusion_process - simulates the diffusion process and diffusion coefficients.

## Compilation and run
All codes can be compiled with the provided Makefile by using the `make` command in terminal. Use `make clean` to delete object files, dependencies and executive file, `make cleanod` cleans only dependencies and object files. Run program by typing `./output` for Linux or `./output.exe` for Windows. In order to create plots, run `plot.p` in Gnuplot - `load 'plot.p'`.

## Requirements
### Windows
* g++ v11.2.0
* Make v4.3
* Gnuplot v5.4 patchlevel 5
### Linux
* g++ v.9.4
* Make v4.2.1
* Gnuplot v5.4 patchlevel 1
