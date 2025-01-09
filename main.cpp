#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "file_reader.h"
#include "product.h"

// Function to print the menu
void print_menu() {
    std::cout << "1. Display all products in a category.\n";
    std::cout << "2. Display all products costing more than 100.\n";
    std::cout << "3. Sort products.\n";
    std::cout << "4. Exit.\n";
    std::cout << "Enter your choice: ";
}

// Function to print products filtered by category
void print_products_by_category(const std::vector<product> &products, const std::string &category) {
    for (const auto &product : products) {
        if (product.category == category) {
            std::cout << product.name << " - " << product.category << " - " << product.cost << " - " << product.quantity << std::endl;
        }
    }
}

// Function to print products with cost above a threshold
void print_products_above_cost(const std::vector<product> &products, double costThreshold) {
    for (const auto &product : products) {
        if (product.cost > costThreshold) {
            std::cout << product.name << " - " << product.category << " - " << product.cost << " - " << product.quantity << std::endl;
        }
    }
}

// Comparison function for sorting by quantity (descending)
bool compare_by_quantity_descending(const product &a, const product &b) {
    return b.quantity < a.quantity;
}

// Comparison function for sorting by category and cost
bool compare_by_category_and_cost(const product &a, const product &b) {
    if (a.category == b.category) {
        return a.cost < b.cost;
    }
    return a.category < b.category;
}

// Merge function for merge sort
void merge(std::vector<product>& products, size_t left, size_t mid, size_t right, bool (*compare)(const product&, const product&)) {
    std::vector<product> leftArr(products.begin() + left, products.begin() + mid + 1);
    std::vector<product> rightArr(products.begin() + mid + 1, products.begin() + right + 1);

    size_t i = 0, j = 0, k = left;
    while (i < leftArr.size() && j < rightArr.size()) {
        if (!compare(rightArr[j], leftArr[i])) {
            products[k++] = leftArr[i++];
        } else {
            products[k++] = rightArr[j++];
        }
    }

    while (i < leftArr.size()) {
        products[k++] = leftArr[i++];
    }
    while (j < rightArr.size()) {
        products[k++] = rightArr[j++];
    }
}

// Merge sort function
void merge_sort(std::vector<product>& products, size_t left, size_t right, bool (*compare)(const product&, const product&)) {
    if (left < right) {
        size_t mid = left + (right - left) / 2;
        merge_sort(products, left, mid, compare);
        merge_sort(products, mid + 1, right, compare);
        merge(products, left, mid, right, compare);
    }
}

// Selection sort function
void selection_sort(std::vector<product> &products, bool (*compare)(const product&, const product&)) {
    size_t size = products.size();
    for (size_t i = 0; i < size - 1; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < size; ++j) {
            if (compare(products[j], products[min_index])) {
                min_index = j;
            }
        }
        std::swap(products[i], products[min_index]);
    }
}

int main() {
    std::vector<product> products;
    file_reader::read("products.txt", products);

    int choice;

    do {
        print_menu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string category;
                std::cout << "Enter category: ";
                std::cin >> category;
                print_products_by_category(products, category);
                break;
            }
            case 2: {
                print_products_above_cost(products, 100.0);
                break;
            }
            case 3: {
                int sort_method, compare_criteria;
                std::cout << "Choose sort method (1 - Selection Sort, 2 - Merge Sort): ";
                std::cin >> sort_method;
                std::cout << "Choose compare criteria (1 - Quantity Descending, 2 - Category and Cost): ";
                std::cin >> compare_criteria;

                auto compare = compare_criteria == 1 ? compare_by_quantity_descending : compare_by_category_and_cost;
                if (sort_method == 1) {
                    selection_sort(products, compare);
                } else {
                    merge_sort(products, 0, products.size() - 1, compare);
                }

                std::cout << "Sorted products:\n";
                for (const auto &product : products) {
                    std::cout << product.name << " - " << product.category << " - " << product.cost << " - " << product.quantity << std::endl;
                }
                break;
            }
            case 4:
                std::cout << "Exiting program." << std::endl;
            break;
            default:
                std::cout << "Invalid choice, try again." << std::endl;
        }

    } while (choice != 4);

    return 0;
}