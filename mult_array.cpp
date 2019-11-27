#ifndef MULT_ARRAY_CPP
#define MULT_ARRAY_CPP

#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include "util.cpp"
#include "embedded_buffer.cpp"
#include "filters_buffer.cpp"
using namespace std;

vector<vector<uint32_t>> batch_index_buffer;

void get_batch(string & filename) {
    ifstream file;
    file.open(filename);
    file >> max_sentences >> words_per_sentence;
    cout << max_sentences << ' ' << words_per_sentence << endl;
    batch_index_buffer.resize(max_sentences);
    int32_t val;
    for (uint32_t i = 0 ; i < max_sentences ; ++i) {
        batch_index_buffer[i].resize(words_per_sentence);
        for (uint32_t j = 0 ; j < words_per_sentence ; ++j) {
            file >> val;
            batch_index_buffer[i][j] = val;
        }
    }
}

void multiply_array_first(vector<vector<int32_t>> & filter, vector<int32_t> & output_buffer,
                            uint32_t sentence_num, int32_t result, ofstream & of) {
    vector<int32_t> embedded_line;
    for (uint32_t i = 0 ; i < filter_height ; ++i) {
        int32_t comb_data = 0;
        read_embeddings(batch_index_buffer[sentence_num][i], embedded_line);
        for (uint32_t j = 0 ; j < filter_width ; ++j) {
            comb_data += embedded_line[j] * filter[i][j];
        }
        result += comb_data;
        output_buffer[i] = comb_data;
    }
    of << "    " << result << endl;
    cout << "    " << result << endl;
}

void multiply_array(vector<vector<int32_t>> & filter, vector<int32_t> & embedded_line,
                    vector<int32_t> & output_buffer, int32_t result, ofstream & of) {
    int32_t comb_data = 0;
    for (uint32_t i = 0 ; i < filter_width ; ++i) {
        comb_data += embedded_line[i] * filter[filter_height-2][i];
    }
    result -= output_buffer[0];
    for (uint32_t i = 0 ; i < filter_height-1 ; ++i) {
        output_buffer[i] = output_buffer[i+1];
    }
    output_buffer[filter_height-1] = comb_data;
    result += comb_data;
    of << "    " << result << endl;
    cout << "    " << result << endl;
}

void run_batch(string & batch_fname, string & res_fname) {
    get_batch(batch_fname); //state 3'b010
    ofstream output_stream;
    output_stream.open(res_fname);

    vector<vector<int32_t>> filter;
    vector<int32_t> embedded_line;
    vector<int32_t> output_buffer(filter_height, 0);
    int32_t result = 0;
    for (uint32_t i = 6 ; i < 7 ; ++i) {
        output_stream << "sentence " << i << endl;
        cout << "sentence " << i << endl;
        for (uint32_t j = 0 ; j < 1 ; ++j) {
            output_stream << "  filter " << j << endl;
            cout << "  filter " << j << endl;
            read_filter(j, filter); //state 3'b011
            output_buffer.clear();
            result = 0;
            multiply_array_first(filter, output_buffer, i, result, output_stream);
            for (uint32_t k = filter_height ; k < words_per_sentence ; ++k) {
                read_embeddings(batch_index_buffer[i][k], embedded_line);
                multiply_array(filter, embedded_line, output_buffer, result, output_stream);
            }
            output_stream << endl;
        }
    }
}

#endif
