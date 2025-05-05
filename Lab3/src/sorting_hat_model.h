#pragma once
#include <cstdarg>
namespace Eloquent {
    namespace ML {
        namespace Port {
            class DecisionTree {
                public:
                    /**
                    * Predict class for features vector
                    */
                    int predict(float *x) {
                        if (x[0] <= 3.5) {
                            if (x[0] <= 2.5) {
                                if (x[0] <= 1.5) {
                                    return 0;
                                }

                                else {
                                    return 3;
                                }
                            }

                            else {
                                return 1;
                            }
                        }

                        else {
                            return 2;
                        }
                    }

                protected:
                };
            }
        }
    }