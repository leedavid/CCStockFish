/*
  Stockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2022 The Stockfish developers (see AUTHORS file)

  Stockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Stockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//Definition of input features HalfKAv2_hm of NNUE evaluation function

#ifndef NNUE_FEATURES_HALF_KA_V2_HM_H_INCLUDED
#define NNUE_FEATURES_HALF_KA_V2_HM_H_INCLUDED

#include "../nnue_common.h"

#include "../../evaluate.h"
#include "../../misc.h"

namespace CCStockfish {
  struct StateInfo;
}

namespace CCStockfish::Eval::NNUE::Features {

  // Feature HalfKAv2_hm: Combination of the position of own king and the position of pieces.
  class HalfKAv2_hm {

    // Index of a feature for a given king position and another piece on some square
    template<Color Perspective>
    static IndexType make_index(Square s, Piece pc, Square ksq);

   public:
    // Feature name
    static constexpr const char* Name = "HalfKAv2_hm";

    // Hash value embedded in the evaluation file
    static constexpr std::uint32_t HashValue = 0x7f234cb8u;

    // Number of feature dimensions
    static constexpr IndexType Dimensions = 9 * static_cast<IndexType>(90*13);

    static constexpr int _Orient[COLOR_NB][SQUARE_NB] = {
      {   0,  1,  2,  3,  4,  5,  6,  7,  8,
          9, 10, 11, 12, 13, 14, 15, 16, 17,
         18, 19, 20, 21, 22, 23, 24, 25, 26,
         27, 28, 29, 30, 31, 32, 33, 34, 35,
         36, 37, 38, 39, 40, 41, 42, 43, 44,
         45, 46, 47, 48, 49, 50, 51, 52, 53,
         54, 55, 56, 57, 58, 59, 60, 61, 62,
         63, 64, 65, 66, 67, 68, 69, 70, 71,
         72, 73, 74, 75, 76, 77, 78, 79, 80,
         81, 82, 83, 84, 85, 86, 87, 88, 89,  },

      {  81, 82, 83, 84, 85, 86, 87, 88, 89,
         72, 73, 74, 75, 76, 77, 78, 79, 80,
         63, 64, 65, 66, 67, 68, 69, 70, 71,
         54, 55, 56, 57, 58, 59, 60, 61, 62,
         45, 46, 47, 48, 49, 50, 51, 52, 53,
         36, 37, 38, 39, 40, 41, 42, 43, 44,
         27, 28, 29, 30, 31, 32, 33, 34, 35,
         18, 19, 20, 21, 22, 23, 24, 25, 26,
          9, 10, 11, 12, 13, 14, 15, 16, 17,
          0,  1,  2,  3,  4,  5,  6,  7,  8,  }
    };

    // Maximum number of simultaneously active features.
    static constexpr IndexType MaxActiveDimensions = 32;
    using IndexList = ValueList<IndexType, MaxActiveDimensions>;

    // Get a list of indices for active features
    template<Color Perspective>
    static void append_active_indices(
      const Position& pos,
      IndexList& active);

    // Get a list of indices for recently changed features
    template<Color Perspective>
    static void append_changed_indices(
      Square ksq,
      const DirtyPiece& dp,
      IndexList& removed,
      IndexList& added
    );

    // Returns the cost of updating one perspective, the most costly one.
    // Assumes no refresh needed.
    static int update_cost(const StateInfo* st);
    static int refresh_cost(const Position& pos);

    // Returns whether the change stored in this StateInfo means that
    // a full accumulator refresh is required.
    static bool requires_refresh(const StateInfo* st, Color perspective);
  };

}  // namespace Stockfish::Eval::NNUE::Features

#endif // #ifndef NNUE_FEATURES_HALF_KA_V2_HM_H_INCLUDED
