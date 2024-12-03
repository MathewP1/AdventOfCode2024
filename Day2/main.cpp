#include <fstream>
#include <iostream>
#include <array>
#include <sstream>
#include <string>

int check_sign(int num) {
  if (num > 0) return 1;
  if (num < 0) return -1;
  else return 0;
}


bool is_level_safe(const std::array<int, 10> &levels, int len) {
  int last_diff_sign;
  for (int i = 1; i < len; i++) {
      int diff = levels[i] - levels[i-1];
      if (std::abs(diff) < 1 || std::abs(diff) > 3) {
        return false;
      }
      int diff_sign = check_sign(diff);
      if (i > 1 && (diff_sign == 0 || diff_sign != last_diff_sign)) {
        return false;
      }
      last_diff_sign = diff_sign;
  }
  return true;
}

int main() {
  std::ifstream input_file("input.txt");
  if (!input_file.is_open()) {
    std::cout << "File not open!" << std::endl;
    return 1;
  }
 
  
  int safe_count = 0;
  int skip_safe_count = 0;
  std::string line;
  while (std::getline(input_file, line)) {
    std::istringstream iss(line);
    std::array<int, 10> levels;
    int cnt = 0;
    while (iss >> levels[cnt]){
      cnt++;
    }
    safe_count += 1;
    int last_diff_sign;
    for (int i = 1; i < cnt; i++) {
      int diff = levels[i] - levels[i-1];
      if (std::abs(diff) < 1 || std::abs(diff) > 3) {
        safe_count -= 1;
        break;
       }
      int diff_sign = check_sign(diff);
      if (i > 1 && (diff_sign == 0 || diff_sign != last_diff_sign)) {
        safe_count -= 1;
        break;
      }
      last_diff_sign = diff_sign;
    }

    std::array<int, 10> levels_skipped;
    for (int i = 0; i < cnt; i++) { // i marks which level is skipped
      // copy up to i
      if (i != 0) {
        std::copy(levels.begin(), levels.begin() + i, levels_skipped.begin());
      }
      // copy from i+1 to cnt
      std::copy(levels.begin()+i+1, levels.begin()+cnt, levels_skipped.begin() + i);
      if (is_level_safe(levels_skipped, cnt-1)) {
        skip_safe_count += 1;
        break;
      }
    }
  }

  std::cout << "Part 1: " << safe_count << std::endl;
  std::cout << "Part 2: " << skip_safe_count  << std::endl;


}

