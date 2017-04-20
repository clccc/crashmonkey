#ifndef RANDOM_PERMUTER_H
#define RANDOM_PERMUTER_H

#include <random>
#include <vector>

#include "Permuter.h"
#include "../utils/utils.h"

namespace fs_testing {
namespace permuter {

struct epoch_op {
  fs_testing::utils::disk_write write;
};

struct epoch {
  unsigned int length;
  bool has_barrier;
  struct epoch_op barrier_op;
  std::vector<struct epoch_op> ops;
};

class RandomPermuter : public Permuter {
 public:
  RandomPermuter();
  RandomPermuter(std::vector<fs_testing::utils::disk_write> *data);
  virtual void set_data(std::vector<fs_testing::utils::disk_write> *data);
  virtual bool permute(std::vector<fs_testing::utils::disk_write> *res);

 private:
  void init_data_vector(std::vector<fs_testing::utils::disk_write> *data);
  void permute_epoch(std::vector<fs_testing::utils::disk_write> *res,
      const int start_index, epoch& epoch);
  unsigned int log_length;
  std::vector<struct epoch> epochs;
  std::mt19937 rand;
  // TODO(ashmrtn): Add some sort of hash_set or something that tracks the
  // permutations already completed so that we don't repeat stuff. It's probably
  // easiest to hash something like the deltas of the bios relative to where
  // they were in the original or something like that.
};

}  // namespace permuter
}  // namespace fs_testing

#endif
