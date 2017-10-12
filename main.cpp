/* 
 * File:   main.cpp
 * Author: artur
 *
 * Created on 13 październik 2012, 20:28
 */

#include <cstdlib>
#include <stdio.h>

using namespace std;

struct perceptron {
    float input_zero;
    float *input[3];
    float weight[3];
    int inputLen;
    float output;

    void init(float *in1, float *in2) {
        input_zero = 1;
        inputLen = 3;

        input[0] = &input_zero;
        input[1] = in1;
        input[2] = in2;

        weight[0] = 0;
        weight[1] = 0;
        weight[2] = 0;
    }

    void calculate() {
        output = 0;
        for (int i = 0; i < inputLen; ++i) {
            output += *input[i] * weight[i];
        }
        output = output > 0 ? 1 : -1;
    }

    void correctWeight(float goodOutput) {
        for (int i = 0; i < inputLen; ++i) {
            weight[i] += *input[i] * goodOutput;
        }
    }

    void dumpWeight() {
        for (int i = 0; i < inputLen; ++i) {
            printf("(%.2f)", weight[i]);
        }
        printf("\n");
    }
};

/*
 * 
 */
int main(int argc, char** argv) {

    float test[7][3] ={
        {2, 1, 1},
        {2, 2, 1},
        {0, 6, 1},
        {-2, 10, -1},
        {-2, 0, -1},
        {0, 0, -1},
        {4, -20, -1}
    };
    
    
    
    int testLen = 7;

    float in1 = 0;
    float in2 = 0;
    float outGood = 0;

    struct perceptron p;
    p.init(&in1, &in2);

    for (int i = 0; i < 1000; ++i) {
        bool fErr = false;
        for (int j = 0; j < testLen; ++j) {
            in1 = test[j][0];
            in2 = test[j][1];
            outGood = test[j][2];

            p.calculate();
            printf("%f\t%f\n", p.output, outGood);
            float err = outGood - p.output;
            if (err) {
                fErr = true;
                printf("err\n");
                p.correctWeight(outGood);
            }
        }
        if (!fErr) {
            printf("find solution after %d epochs\n", i);
            p.dumpWeight();
            break;
        }
    }
    return 0;
}

