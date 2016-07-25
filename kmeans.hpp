//
//  kmeans.hpp
//  kmeans
//
//  Created by BlueCocoa on 2016/7/25.
//  Copyright © 2016年 BlueCocoa. All rights reserved.
//

#ifndef KMEANS_H
#define KMEANS_H

#include <algorithm>
#include <float.h>
#include <functional>
#include <map>
#include <vector>
#include <time.h>

namespace llama {
    namespace ML {
        /**
         *  @brief K-means algorithm
         *
         *  @param k        Number of clusters
         *  @param min_diff Minimum difference
         *  @param data     Data to cluster
         *  @param center   Custom center calcualation
         *  @param distance Custom distance calculation
         */
        template <class _Element>
        std::vector<_Element> kmeans(ssize_t k, double min_diff, const std::vector<_Element>& data, const std::function<_Element(const std::vector<std::pair<_Element, uint32_t>>& data)>& center, const std::function<double(const _Element& first, const _Element& second)>& distance);
        
        /**
         *  @brief K-means algorithm
         *
         *  @param k        Number of clusters
         *  @param min_diff Minimum difference
         *  @param data     Data (with count) to cluster
         *  @param center   Custom center calcualation
         *  @param distance Custom distance calculation
         */
        template <class _Element>
        std::vector<_Element> kmeans(ssize_t k, double min_diff, const std::vector<std::pair<_Element, uint32_t>>& data, const std::function<_Element(const std::vector<std::pair<_Element, uint32_t>>& data)>& center, const std::function<double(const _Element& first, const _Element& second)>& distance);
        
        template <class _Element>
        std::vector<_Element> kmeans(ssize_t k, double min_diff, const std::vector<_Element>& data, const std::function<_Element(const std::vector<std::pair<_Element, uint32_t>>& data)>& center, const std::function<double(const _Element& first, const _Element& second)>& distance) {
            using ElementCount  = std::pair<_Element, uint32_t>;
            std::vector<ElementCount> elements;
            std::for_each(data.cbegin(), data.cend(), [&](const _Element& element) {
                elements.emplace_back(element, 1);
            });
            return kmeans<_Element>(k, min_diff, elements, center, distance);
        }
        
        template <class _Element>
        std::vector<_Element> kmeans(ssize_t k, double min_diff, const std::vector<std::pair<_Element, uint32_t>>& data, const std::function<_Element(const std::vector<std::pair<_Element, uint32_t>>& data)>& center, const std::function<double(const _Element& first, const _Element& second)>& distance) {
            using ElementCount  = std::pair<_Element, uint32_t>;
            using Cluster       = std::vector<_Element>;
            using ClusterPoint  = std::map<uint32_t, std::vector<ElementCount>>;
            
            Cluster clusters;
            uint32_t randmax = static_cast<uint32_t>(data.size());
            
            for (uint32_t i = 0; i < k; i++) {
                auto iter = data.cbegin();
                for (uint32_t t = 0; t < arc4random() % randmax; t++, iter++);
                clusters.emplace_back(iter->first);
            }
            
            while (1) {
                ClusterPoint points;
                
                std::for_each(data.cbegin(), data.cend(), [&](const std::pair<_Element, uint32_t>& point) {
                    double smallestDistance = DBL_MAX;
                    double dis;
                    uint32_t smallestIndex;
                    for (uint32_t i = 0; i < k; i++) {
                        dis = distance(point.first, clusters[i]);
                        
                        if (dis < smallestDistance) {
                            smallestDistance = dis;
                            smallestIndex = i;
                        }
                    }
                    points[smallestIndex].emplace_back(point);
                });
                
                double diff = 0;
                for (uint32_t i = 0; i < k; i++) {
                    _Element oldCenter = clusters[i];
                    _Element newCenter = center(points[i]);
                    clusters[i] = newCenter;
                    double dis = distance(oldCenter, newCenter);
                    diff = std::max(diff, dis);
                }
                
                if (diff < min_diff) {
                    break;
                }
            }
            
            return clusters;
        }
    }
}

#endif /* KMEANS_H */
