#pragma once

#include <array>
#include <vector>
#include "syntax/token.h"
#include "misc/iterable.h"

namespace ionir::testing
{
inline Token bootstrapToken(int id);

inline TokenStream bootstrapTokenStream(int amountOfItems = 1);

template <unsigned int N>
inline void compareTokenSets(std::array<Token, N> expected, std::vector<Token> actual);
} // namespace ionir::testing
