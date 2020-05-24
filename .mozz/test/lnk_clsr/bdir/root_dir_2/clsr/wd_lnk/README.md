# FT_LS
Template repo for 42/21 school C-projects

## Install
For simple instalation run this command
```bash
make -C .mozz proj=PROJ_NAME
```
Where `PROJ_NAME` will be subordinate everywhere as the name of the project, including for executable in main Makefile

## Uninstall
```bash
make -C .mozz proj=PROJ_NAME
```

### Features
Sh script to build projrct using your **`Makefile`** and attache **`main.c`** with output **`a.out`**
```bash
[PROJ_NAME]_build
```
Sh script for check file with **`norminate`**
```bash
[PROJ_NAME]_norm [file]
```
Sh scrip to check executable with **`valgrind`** for memmory leaks. Try to execute **`a.out`**.
```bash
[PROJ_NAME]_valg
```
