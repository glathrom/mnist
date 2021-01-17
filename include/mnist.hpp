#ifndef __MNIST_H
#define __MNIST_H

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>



class MNIST {
    
    private:
        std::vector<unsigned char> *training_labels;
        std::vector<unsigned char> *testing_labels;
        std::vector<unsigned char> *training_data;
        std::vector<unsigned char> *testing_data;
        std::vector<unsigned char> *load_labels(std::string fn);
        std::vector<unsigned char> *load_images(std::string fn);
    
    public:
        MNIST(std::string dpath);
        ~MNIST();

        std::string files[4] = {
                                 "train-labels-idx1-ubyte",
                                 "train-images-idx3-ubyte",
                                 "t10k-labels-idx1-ubyte",
                                 "t10k-images-idx3-ubyte",
                               };
        std::vector<unsigned char> *get_training_labels();
        std::vector<unsigned char> *get_testing_labels();
        std::vector<unsigned char> *get_training_images();
        std::vector<unsigned char> *get_testing_images();
        int number_test_images;
        int number_training_images;
        std::unordered_map<std::string, int> image_size;
        
};

#endif
