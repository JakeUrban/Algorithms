#!/usr/bin/env python3
import math


def calc_dist(p1, p2):
    return math.sqrt((p1[0]-p2[0])**2+(p1[1]-p2[1])**2)


def pick_cluster(name, xy, centers):
    min_dist = float("inf")
    min_idx = 0
    for idx, center in enumerate(centers):
        dist = calc_dist(xy, center)
        if dist < min_dist:
            min_dist = dist
            min_idx = idx
    return min_idx


def k_means(k, data, centers):
    assigned_to = {}
    change = True
    num_iter = 0
    while change:
        num_changes = 0
        for key, val in data.items():
            new_cluster = pick_cluster(key, val, centers)
            if key not in assigned_to.keys() or new_cluster != assigned_to[key]:
                num_changes += 1
            assigned_to[key] = new_cluster
        for idx, mean in enumerate(centers):
            x_cluster_sum = 0
            y_cluster_sum = 0
            num_items = 0
            for key, val in assigned_to.items():
                if assigned_to[key] == idx:
                    x_cluster_sum += data[key][0]
                    y_cluster_sum += data[key][1]
                    num_items += 1
            new_mean_x = x_cluster_sum/num_items
            new_mean_y = y_cluster_sum/num_items
            centers[idx] = (new_mean_x, new_mean_y)
        if num_changes == 0:
            change = False
        if num_iter == 0:
            for center in centers:
                print(center)
        num_iter += 1
    return centers, assigned_to


def main():
    k = 3
    data = {'A1': (3, 10), 'A2': (4, 6), 'A3': (9, 5),
            'B1': (3, 8), 'B2': (8, 5), 'B3': (6, 6),
            'C1': (2, 3), 'C2': (5, 7), 'C3': (6, 8)}
    centers = [data['A1'], data['B1'], data['C1']]
    centers, clusters = k_means(k, data, centers)
    for idx, center in enumerate(centers):
        print("In cluster: " + str(idx) + " with center: " + str(center))
        for key, val in clusters.items():
            if val == idx:
                print(key)


if __name__ == '__main__':
    main()
