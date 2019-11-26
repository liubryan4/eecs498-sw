#include "embedded_buffer.cpp"
#include "filters_buffer.cpp"
#include "mult_array.cpp"
#include "util.cpp"
using namespace std;

int main(int argc, char ** argv) {
    string embedded_fname = argv[1];
    string filters_fname = argv[2];
    string sentences = argv[3];
    string output_fname = argv[4];
    write_embeddings(embedded_fname);
    write_filters(filters_fname);
    run_batch(sentences, output_fname);
    return 0;
}
