//
// Created by creeper on 10/10/24.
//

#ifndef MINILOG_INCLUDE_MINILOG_PROPERTIES_H
#define MINILOG_INCLUDE_MINILOG_PROPERTIES_H
namespace minilog {

struct RAII {
  RAII() = default;
  RAII(RAII&&) = delete;
};

}
#endif //MINILOG_INCLUDE_MINILOG_PROPERTIES_H
