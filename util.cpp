#ifndef UTIL_CPP
#define UTIL_CPP

#include <math.h>

using uint32_t = u_int32_t;

// embedding matrix constants
const uint32_t max_unique_words = 4000;
const double log_max_unique_words = log2(max_unique_words);
const uint32_t embedding_size = 300;
const uint32_t emb_line_size = sizeof(uint32_t) * embedding_size;

// filter constants
const uint32_t max_filters = 120;
const double log_max_filters = log2(max_filters);
const uint32_t filter_height = 4;
const uint32_t filter_width = 300;
const uint32_t filter_line_size = sizoef(int32_t) * filter_width;

// batch constants
const uint32_t max_sentences = 256;
const uint32_t words_per_sentence = 50;
const uint32_t sentences_per_mult = 4;
const uint32_t sentence_size = sizeof(int32_t) * words_per_sentence;

#endif
