// Copyright (c) 2018-2023 Margarita Colberg
// SPDX-License-Identifier: BSD-3-Clause

#include "solvent.h"

// initial positions of all solvent particles
void init_pos_sol(std::vector<Vec3> &pos, std::vector<Vec3> &pos_sol,
                  const Box &box, Random &mt, const Param &p) {
  const unsigned int nbeads = pos.size();
  const unsigned int nsol = pos_sol.size();
  std::uniform_real_distribution<> uniform_sol(0.0, box.l);

  if (pos_sol.size() < 1)
    return;

  uint64_t tries = 0;
  unsigned int i = 0;

  while (i < nsol) {
    if (!(tries++ < p.tries)) {
      throw std::logic_error(
          "Number of tries exceeded while placing solvent particle in box");
    }

    double x = uniform_sol(mt);
    double y = uniform_sol(mt);
    double z = uniform_sol(mt);

    // declare a variable to check if there is an overlap of
    // a solvent particle and a bead
    bool overlap = false;

    for (unsigned int j = 0; j < nbeads; j++) {
      double dx = x - pos[j].x;
      double dy = y - pos[j].y;
      double dz = z - pos[j].z;
      box.mindist(dx, dy, dz);

      // check if a solvent particle overlaps with a bead
      if ((dx * dx + dy * dy + dz * dz) < p.sigma_sb2) {
        // if there is an overlap,
        overlap = true;
        // exit without checking the other distances
        break;
      }
    }

    for (unsigned int j = 0; j < i; j++) {
      double dx = x - pos_sol[j].x;
      double dy = y - pos_sol[j].y;
      double dz = z - pos_sol[j].z;
      box.mindist(dx, dy, dz);

      if ((dx * dx + dy * dy + dz * dz) < p.sigma_ss2) {
        overlap = true;
        break;
      }
    }

    if (overlap)
      continue;

    // store only the x-, y- and z-coordinates whose solvent
    // particle does not overlap with a bead
    pos_sol[i].x = x;
    pos_sol[i].y = y;
    pos_sol[i].z = z;
    i++;
    tries = 0;
  }
}
