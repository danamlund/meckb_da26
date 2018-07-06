/* Copyright 2018 dan amlund
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DA26_H
#define DA26_H

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k27, \
      k10, k11, k12, k13, k14, k15, k16, k17, k18, \
        k20, k21, k22, k23, k24, k25, k26 \
) \
{ \
  { k00, k01, k02, k03, k04, k05, k06, k07,   k08 }, \
  { k10, k11, k12, k13, k14, k15, k16, k17,   k18 }, \
  { k20, k21, k22, k23, k24, k25, k26, KC_NO, k27 } \
}

#endif
