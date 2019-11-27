#ifndef UTIL_CPP
#define UTIL_CPP

#include <math.h>

using uint32_t = u_int32_t;

// embedding matrix constants
uint32_t max_unique_words = 4000;
uint32_t embedding_size = 300;

// filter constants
uint32_t max_filters = 120;
uint32_t filter_height = 4;
uint32_t filter_width = 300;

// batch constants
uint32_t max_sentences = 256;
uint32_t words_per_sentence = 50;

#endif
