#include <cstdlib>
#include "mnist.hpp"


MNIST::MNIST(std::string dpath){
    training_labels = load_labels(dpath+files[0]);
    training_data = load_images(dpath+files[1]);
    testing_labels = load_labels(dpath+files[2]);
    testing_data = load_images(dpath+files[3]);
    number_test_images = testing_labels->size();
    number_training_images = testing_labels->size();
    
}

MNIST::~MNIST(){
    printf("destructor called\n");
}

std::vector<unsigned char> *MNIST::load_labels(std::string fn){

    std::ifstream fp;
    int hdr_size = 2;
    unsigned char *buf, *labels;
    std::int32_t magic, num_items;
    std::vector<unsigned char> *ans = new std::vector<unsigned char>;

    buf = (unsigned char *) malloc(hdr_size*sizeof(std::int32_t));

    fp.open(fn, std::ios::in | std::ios::binary);

    fp.read((char *) buf, hdr_size*sizeof(std::int32_t));

    magic = (buf[0]<<(3*8))^(buf[1]<<(2*8))^(buf[2]<<8)^buf[3];
    num_items = (buf[4]<<(3*8))^(buf[5]<<(2*8))^(buf[6]<<8)^buf[7];

    labels = (unsigned char *) malloc(num_items*sizeof(unsigned char));

    fp.read((char *) labels, num_items*sizeof(unsigned char));

    fp.close();

    for(int i = 0; i < num_items; i++ ){
        ans->push_back(labels[i]);
    }
    
    printf("Filename: %s\n", fn.c_str());
    printf("Magic Number:  %#010x\n", magic);
    printf("Number of Items:  %d\n", num_items);
    
    free(buf);
    free(labels);
    return ans;
}

std::vector<unsigned char> * MNIST::load_images(std::string fn){
    std::ifstream fp;
    int hdr_size=4;
    unsigned char *buf, *data;
    std::int32_t magic, num_items, nrows, ncols;
    std::vector<unsigned char> *ans = new std::vector<unsigned char>;

    buf = (unsigned char *) malloc(hdr_size*sizeof(std::int32_t));

    fp.open(fn, std::ios::in | std::ios::binary);

    fp.read((char *) buf, hdr_size*sizeof(std::int32_t));

    magic = (buf[0]<<(3*8))^(buf[1]<<(2*8))^(buf[2]<<8)^buf[3];
    num_items = (buf[4]<<(3*8))^(buf[5]<<(2*8))^(buf[6]<<8)^buf[7];
    nrows = (buf[8]<<(3*8))^(buf[9]<<(2*8))^(buf[10]<<8)^buf[11];
    ncols = (buf[12]<<(3*8))^(buf[13]<<(2*8))^(buf[14]<<8)^buf[15];

    data = (unsigned char *) malloc(nrows*ncols*num_items*sizeof(unsigned char));

    fp.read((char *) data, num_items*nrows*ncols*sizeof(unsigned char));
    
    fp.close();
    
    printf("Filename: %s\n", fn.c_str());
    printf("Magic Number:  %#010x\n", magic);
    printf("Number of Items:  %d\n", num_items);
    printf("Image Dimension: %dx%d\n", nrows,ncols);

    for(int i = 0; i < num_items*ncols*nrows; i++){
        ans->push_back(data[i]);
    }

    image_size["rows"] = nrows;
    image_size["cols"] = ncols;

    free(buf);
    free(data);
    return ans;    
}

std::vector<unsigned char> * MNIST::get_testing_labels(){
    return testing_labels;
}

std::vector<unsigned char> * MNIST::get_training_labels(){
    return training_labels;
}

std::vector<unsigned char> * MNIST::get_testing_images(){
    return testing_data;
}

std::vector<unsigned char> * MNIST::get_training_images(){
    return training_data;
}

