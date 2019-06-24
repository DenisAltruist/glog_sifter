#include <glog/logging.h>
#include <string>
#include "main.h"

int main() {
  GlogSeverity sev1("path1");
  GlogSeverity sev2("path2");
  GLOG("kek", &sev1); // will write "kek" to file "logs_folder/path1" with usual log string prefix (timestamp, code line etc.)
  GLOG("cheburek", &sev2); // will write "cheburek" to file "logs_folder/path2"
  return 0;
}
