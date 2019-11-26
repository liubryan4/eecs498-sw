#ifndef MULT_ARRAY_CPP
#define MULT_ARRAY_CPP

#include <cmath>
#include "util.cpp"
#include "filters_buffer.cpp"
using namespace std;

int32_t filter[filter_height][filter_width];
uint32_t batch_index_buffer[max_sentences][words_per_sentence];
uint32_t active_sentences[sentences_per_mult][words_per_sentence];
uint32_t sec_counter_storage[sentences_per_mult];
int32_t comb_data = 0;
int32_t partial_mults[embedding_size];

void get_batch(string & filename) {
    ifstream file;
    file.open(filename);
    int32_t val;
    for (uint32_t i = 0 ; i < max_sentences ; ++i) {
        for (uint32_t j = 0 ; j < words_per_sentence ; ++j) {
            cin >> val;
            batch_index_buffer[i][j] = val;
        }
    }
}

void multiply_array() {

}

void run_batch(string & filename) {
    get_batch(filename); //state 3'b010
    for (uint32_t i = 0 ; i < max_filters ; ++i) {
        read_filter(i, filter); //state 3'b011
        for (uint32_t j = 0 ; j < max_sentences ; j += sentences_per_mult) {
            int num_sentences = min(sentences_per_mult, max_sentences-j);
            // load <=4 sentences into active buffer
            for (uint32_t k = 0 ; k < num_sentences ; ++k) {
                memcpy(active_sentences + k*sentence_size,
                            batch_index_buffer + j*sentence_size,
                            sentence_size);
                sec_counter_storage[k] = j+k;
            }
            // WHY ARE YOU MOVING VEC_IN TO VEC_STORAGE?
            // purpose of invalid_read in parent.sv?
            // rename active_index_to_cache to active_index_to_emb?
            // rename vec_in in mult_array to embedded_word
            // what is the point of addr_out in mult_array.sv?
            

            // multiply word
            comb_data = 0;
            for (uint32_t k = 0 ; k < filter_height ; ++k) {
                for (uint32_t l = 0 ; l < embedding_size ; ++l) {
                    partial_mults[l] = embedded_word[l] * filter[k][l];
                    comb_data += partial_mults[l];
                }
    }
}
#endif
