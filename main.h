#include <glog/logging.h>
#include <mutex>
#include <string>
#include <iostream>

class GlogSeverity : public google::LogSink {
 public:
  GlogSeverity(const std::string& filename) : 
    log_filepath_(FLAGS_log_dir + "/" + filename)) { // std::filesystem::operator/
      out_.open(log_filepath_.c_str());
      assert(out_.is_open());
  }

  void send(
    google::LogSeverity severity,
    const char* full_filename,
    const char* base_filename,
    int line,
    const struct ::tm *tm_time,
    const char* message,
    size_t message_len
  ) override {
    std::string str_message = 
      google::LogSink::ToString(
        severity,
        base_filename,
        line,
        tm_time,
        message,
        message_len
      );
    {
      std::unique_lock lock(write_file_mutex_);
      out_ << str_message;
    }
  }

  ~GlogSeverity() override {};

 private:
  std::mutex write_file_mutex_;
  std::string log_filepath_;
  std::ofstream out_;
};

void GLOG(const std::string& message, google::LogSink* sink) {
  google::AddLogSink(sink);
  LOG(INFO) << message;
  google::RemoveLogSink(sink);
}
