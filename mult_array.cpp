#ifndef MULT_ARRAY_CPP
#define MULT_ARRAY_CPP

#include <cmath>
#include <iostream>
#include "util.cpp"
#include "embedded_buffer.cpp"
#include "filters_buffer.cpp"
using namespace std;

int32_t filter[filter_height][filter_width];
uint32_t batch_index_buffer[max_sentences][words_per_sentence];
int32_t output_buffer[filter_height];
int32_t embedded_line[embedding_size];
int32_t result;

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

void multiply_array_first(uint32_t sentence_num, ofstream & of) {
    int32_t comb_data = 0;
    result = 0;
    for (uint32_t i = 0 ; i < filter_height ; ++i) {
        read_embeddings(&batch_index_buffer[sentence_num][i], embedded_line);
        for (uint32_t j = 0 ; j < filter_width ; ++j) {
            comb_data += embedded_line[j] * filter[i][j]
        }
        result += comb_data;
        output_buffer[i] = comb_data;
    }
    cout << result << endl;
}

void multiply_array(ofstream & of) {
    int32_t comb_data = 0;
    for (uint32_t i = 0 ; i < filter_width ; ++i) {
        comb_data += embedded_line[i] * filter[filter_height-2][j];
    }
    result -= output_buffer[0];
    for (uint32_t i = 0 ; i < filter_height-1 ; ++i) {
        output_buffer[i] = output_buffer[i+1];
    }
    output_buffer[filter_height-1] = comb_data;
    result += comb_data
    cout << result << endl;
}

// WHY ARE YOU MOVING VEC_IN TO VEC_STORAGE?
// purpose of invalid_read in parent.sv?
// rename active_index_to_cache to active_index_to_emb?
// rename vec_in in mult_array to embedded_word
// what is the point of addr_out in mult_array.sv?
void run_batch(string & batch_fname, string & res_fname) {
    get_batch(batch_fname); //state 3'b010
    ofstream output;
    output.open(res_fname);
    for (uint32_t i = 0 ; i < max_filters ; ++i) {
        read_filter(i, filter); //state 3'b011
        memset(output_buffer, 0, sizeof(int32_t)*filter_height);
        for (uint32_t j = 0 ; j < max_sentences ; j += sentences_per_mult) {
            output << "sentence " << j << endl;
            multiply_array_first(j, output);
            for (uint32_t k = filter_height ; k < words_per_sentence ; ++k) {
                read_embeddings(&batch_index_buffer[j][k], embedded_line);
                multiply_array(output);
            }
            output << endl;
        }
    }
}

#endif
