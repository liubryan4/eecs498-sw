#ifndef FILTERS_BUFFER_CPP
#define FILTERS_BUFFER_CPP

#include <vector>
#include "util.cpp"
using namespace std;

vector<vector<vector<int32_t>>> filter_storage;

void inline read_filter(uint32_t id, vector<vector<int32_t>> & data_out) {
    data_out = filter_storage[id];
}

void inline write_filters(string fname) {
    ifstream file;
    file.open(fname);
    int32_t val;
    // transpose the input matrix
    file >> max_filters >> filter_width >> filter_height;
    cout << max_filters << ' ' << filter_height << ' ' << filter_width << endl;
    filter_storage.resize(max_filters);
    for (uint32_t i = 0 ; i < max_filters ; ++i) {
        filter_storage[i].resize(filter_height);
        for (uint32_t j = 0 ; j < filter_height ; ++j) {
            filter_storage[i][j].resize(filter_width);
        }
        for (uint32_t j = 0 ; j < filter_width ; ++j) {
            for (uint32_t k = 0 ; k < filter_height ; ++k) {
                file >> val;
                filter_storage[i][k][j] = val;
            }
        }
    }
}

#endif
