/*
  CCStockfish, a UCI chess playing engine derived from Glaurung 2.1
  Copyright (C) 2004-2022 The CCStockfish developers (see AUTHORS file)

  CCStockfish is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  CCStockfish is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef EVALUATE_H_INCLUDED
#define EVALUATE_H_INCLUDED

#include <string>
#include <optional>

#include "types.h"

namespace CCStockfish {

class Position;

namespace Eval {

  std::string trace(Position& pos);
  Value evaluate(const Position& pos, int* complexity = nullptr);

  extern std::string currentEvalFileName;

  // The default net name MUST follow the format nn-[SHA256 first 12 digits].nnue
  // for the build process (profile-build and fishtest) to work. Do not change the
  // name of the macro, as it is used in the Makefile.
  #define EvalFileDefaultName   "entry.nnue"

  namespace NNUE {

    std::string trace(Position& pos);
    Value evaluate(const Position& pos, int* complexity = nullptr);

    void init();
    void verify();

    bool load_eval(std::string name, std::istream& stream);
    bool save_eval(std::ostream& stream);
    bool save_eval(const std::optional<std::string>& filename);

  } // namespace NNUE

} // namespace Eval

} // namespace CCStockfish

#endif // #ifndef EVALUATE_H_INCLUDED
