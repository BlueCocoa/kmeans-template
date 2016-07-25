# K-means template
A simple K-means algorithm template in C++

Tested on macOS

### Installation
```$sudo make install```

### Usage

	#include <algorithm>
	#include <cstdlib>
	#include <iostream>
	#include <iterator>
	#include <vector>
	#include "kmeans.hpp"
	
	using namespace std;
	
	int main(int argc, const char * argv[]) {
	    vector<double> data;
	    
	    for (int i = 0; i < 10; i++) {
	        data.emplace_back(233 + random() % 10);
	        data.emplace_back(233 - random() % 10);
	    }
	    for (int i = 0; i < 10; i++) {
	        data.emplace_back(2333 + random() % 10);
	        data.emplace_back(2333 - random() % 10);
	    }
	    for (int i = 0; i < 10; i++) {
	        data.emplace_back(23333 + random() % 10);
	        data.emplace_back(23333 - random() % 10);
	    }
	    
	    vector<double> result = llama::ML::kmeans<double>(3, 2, data, [&](const std::vector<std::pair<double, uint32_t>>& data) -> double {
	        double total = 0, count = 0;
	
	        for_each(data.cbegin(), data.cend(), [&total, &count](const std::pair<double, uint32_t>& point){
	            total += point.first;
	            count += point.second;
	        });
	        return total/count;
	    }, [&](const double& first, const double& second) -> double {
	        double dis = first - second;
	        return dis < 0 ? -dis : dis;
	    });
	    
	    copy(result.cbegin(), result.cend(), ostream_iterator<double>(cout, " "));
	    cout<<'\n';
	    return 0;
	}

### Screenshots

![macOS](https://raw.githubusercontent.com/BlueCocoa/kmeans-template/master/screenshot.png)

