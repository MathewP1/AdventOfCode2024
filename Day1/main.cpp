#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

int main() {
  std::ifstream input_file("input.txt");
  if (!input_file.is_open()) {
    std::cout << "File not open!" << std::endl;
    return 1;
  }

  std::vector<int> list1, list2;

  std::string line;
  while (std::getline(input_file, line)) {
    std::istringstream iss(line);
    int a, b;
    iss >> a >> b;
    list1.push_back(a);
    list2.push_back(b);
  }

  std::sort(list1.begin(), list1.end());
  std::sort(list2.begin(), list2.end());

  int sum = 0;
  for (int i = 0; i < list1.size(); i++) {
    sum += std::abs(list1[i] - list2[i]);
  }

  std::cout << "Part 1: " << sum << std::endl;

  // Part 2

  // map of numer -> occurence count
  std::unordered_map<int, int> list2_map;
  for (auto i : list2) {
    auto it = list2_map.find(i);
    if (it == list2_map.end()) {
      list2_map.emplace(i, 1);
    } else {
      it->second += 1;
    }
  }
  int score = 0;
  for (auto i : list1) {
    score += i * list2_map[i];
  }
  std::cout << "Part 2: " << score << std::endl;
  return 0;
}
