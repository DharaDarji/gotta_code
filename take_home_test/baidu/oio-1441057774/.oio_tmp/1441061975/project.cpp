#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Glob {
 public:
  vector<string> Match(const string& pattern, const vector<string>& filenames) const {
    // IMPLEMENT ME
    vector<string> output;

	// DP table of n+1 x m+1
	for(int file = 0; file < (int)filenames.size(); file++) {
			vector<vector<bool>> opt(pattern.size()+2, vector<bool>(filenames[file].size()+2, false));
			opt[0][0] = true;
			int i,j;
			//Init table
			// 0 length string but we have pattern
			// If our previous' previous true AND current is * (as * can eliminate everything)
			for(i=2; i < (int)pattern.size()+1; i++) {
				opt[i][0] = opt[i-2][0] and pattern[i - 1] == '*';
			}

			for(i=0; i < (int)pattern.size() + 1; i++) {
				for(j=0; j < (int)filenames[file].size() + 1; j++) {
					// 1) If its NOT *; easy one - update diagonally; if current is same or ? =? true
					opt[i][j] = opt[i-1][j-1] and (filenames[file][j] == pattern[i] or pattern[i] == '?');
				
					//2) If its *, i-1 and j match, vertical [i-1][j] or horizontal [i][j-1]
					opt[i][j] = opt[i-1][j] or opt[i][j-1];
				}
			}
			i = (int)pattern.size()+1;
			j = (int)filenames[file].size() + 1;
			if(opt[i][j]) {
				// If it match
				output.push_back(filenames[file]);
			}
	}
    return output;
  }
};

bool vector_equal(const vector<string>& expected, const vector<string>& actual) {
  if (expected.size() != actual.size()) {
    return false;
  }
  for (size_t i = 0; i < expected.size(); ++i) {
    if (expected[i] != actual[i]) {
      return false;
    }
  }
  return true;
}

#ifndef __main__
#define __main__

int main() {
  // Should return true
  cout << vector_equal(
      { "abcd", "dabc", "abc" },
      Glob().Match("?abc*", { "abcd", "dabc", "abc", "efabc", "eadd" })) << endl;
  // Should return true
  cout << vector_equal(
      { "abcd", "dabc", "abc" },
      Glob().Match("?a**c*", { "abcd", "dabc", "abc", "efabc", "eadd" })) << endl;
}

#endif
