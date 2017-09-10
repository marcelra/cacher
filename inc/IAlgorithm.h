#ifndef IALGORITHM_H
#define IALGORITHM_H

#include <string>

/// TODO: rename to AlgorithmBase


class IAlgorithm
{
   public:
      virtual ~IAlgorithm() {}



   public:
      virtual const std::string getName() const = 0;
};



#endif // IALGORITHM_H
