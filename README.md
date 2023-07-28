[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/luk036/primal-dual-approx-cpp)
[![Build Status](https://travis-ci.org/luk036/primal-dual-approx-cpp.svg?branch=main)](https://travis-ci.org/luk036/primal-dual-approx-cpp)
[![Documentation Status](https://readthedocs.org/projects/primal-dual-approx-cpp/badge/?version=latest)](https://primal-dual-approx-cpp.readthedocs.io/en/latest/?badge=latest)
[![codecov](https://codecov.io/gh/luk036/primal-dual-approx-cpp/branch/main/graph/badge.svg?token=4VLEGh1zBI)](https://codecov.io/gh/luk036/primal-dual-approx-cpp)
[![CodeFactor](https://www.codefactor.io/repository/github/luk036/primal-dual-approx-cpp/badge)](https://www.codefactor.io/repository/github/luk036/primal-dual-approx-cpp)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/63f43fb5c7034f4d863c5a86dd0cba1e)](https://app.codacy.com/app/luk036/primal-dual-approx-cpp?utm_source=github.com&utm_medium=referral&utm_content=luk036/primal-dual-approx-cpp&utm_campaign=Badge_Grade_Dashboard)
[![Documentation](https://img.shields.io/badge/Documentation-latest-blue.svg)](https://luk036.github.io/doc/primal-dual-approx-cpp/index.html)

<p align="center">
  <img src="./primal-dual-algorithmic-paradigm-ying-yang.svg"/>
</p>

# ☯ primal-dual-approx-cpp

Primal-dual Approximation Algorithms C++ Code

## Highlights

-   Direct port from [Python version](https://github.com/luk036/primal-dual-approx-py)
-   Work for C++20/17/14.
-   Support multi-level bi-partitioning and K-way partitioning
-   Special handle two-pin nets (and three-pin nets).

## Installation and Run

To run in gitpod.io:

    ./envconfig.sh  # first time when gitpod image is built

To build with Ninja:

    mkdir build && cd build
    cmake -GNinja ..
    ninja all

To run CTest:

    ninja test
