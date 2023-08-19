// Copyright (c) 2018-2023 Margarita Colberg
// SPDX-License-Identifier: BSD-3-Clause

#ifndef HARD_SOLVENT_H
#define HARD_SOLVENT_H

#include "hardspheres.h"

#if NDEBUG
#define LOG_DEBUG(x)
#else
#define LOG_DEBUG(x) std::cout << __FILE__ << ":" << __LINE__ << ": " << x << std::endl
#endif

void init_pos_sol(std::vector<Vec3>& pos, std::vector<Vec3>& pos_sol, const Box& box, Random& mt, const Param& p);

#endif
