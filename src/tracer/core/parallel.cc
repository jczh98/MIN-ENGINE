// MIT License
// 
// Copyright (c) 2018-2019, neverfelly <neverfelly@gmail.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include <thread>
#include <utility>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <deque>
#include "parallel.h"

namespace min::tracer {

class ParallelForContext {
 public:
  ParallelForContext() noexcept :
      workers_(GetCoreNumber()),
      shutdown_(false),
      active_workers_(0) {
    for (int i = 0; i < workers_.size(); i++) {
      workers_[i] = std::thread([=]() {
        uint32_t thread_id = i;
        std::unique_lock<std::mutex> lock(task_mutex_);
        while (!shutdown_) {
          if (queue_.empty()) {
            std::unique_lock<std::mutex> main_lock(main_mutex_);
            main_waiting_.notify_one();
          } else {
            active_workers_++;
            auto worker = queue_.front();
            queue_.pop_front();
            lock.unlock();
            for (int64_t index = worker.first; index < worker.second; index++) {
              work_func_(index, thread_id);
            }
            lock.lock();
            active_workers_--;
          }
        }
      });
    }
  }
  ~ParallelForContext() {
    shutdown_ = true;
    task_waiting_.notify_all();
    for (auto &worker : workers_) {
      if (worker.joinable()) {
        worker.join();
      }
    }
  }
  void ParallelFor(int64_t begin, int64_t end, WorkFunc func, size_t work_size) {
    {
      std::unique_lock<std::mutex> lock(task_mutex_);
      work_func_ = std::move(func);
      while (begin < end) {
        auto l = begin;
        auto h = std::min<size_t>(end, begin + work_size);
        queue_.emplace_back(l, h);
        begin += work_size;
      }
      task_waiting_.notify_all();
    }
    {
      std::unique_lock<std::mutex> lock(main_mutex_);
      main_waiting_.wait(lock);
    }
  }
 private:
  std::vector<std::thread> workers_;
  std::mutex task_mutex_, main_mutex_;
  std::condition_variable main_waiting_, task_waiting_;
  std::atomic<bool> shutdown_;
  std::deque<std::pair<int64_t, int64_t>> queue_;
  std::atomic<uint32_t> active_workers_;
  WorkFunc work_func_;
};

static size_t core_number = std::thread::hardware_concurrency();
static ParallelForContext parallel_for_context;

size_t GetCoreNumber() { return core_number; }

void SetCoreNumber(size_t n) { core_number = n; }

void ParallelFor(int64_t begin, int64_t end, WorkFunc func, size_t work_size) {
  parallel_for_context.ParallelFor(begin, end, std::move(func), work_size);
}

}
