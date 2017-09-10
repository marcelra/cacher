#ifndef DUMMYALGORITHM_H
#define DUMMYALGORITHM_H


#include "IAlgorithm.h"
#include "DependencyListBase.h"

#include <string>


class DummyAlgorithm : public IAlgorithm
{
   public:
      class DependencyList : public DependencyListBase
      {
         public:
            DependencyList(double x, int y);
      };

   public:
      DummyAlgorithm(const std::string& name, const DependencyList& dependencies);
      ~DummyAlgorithm();

   public:
      const std::string getName() const;

   private:
      std::string       m_name;
      DependencyList    m_dependencyList;
};

#endif // DUMMYALGORITHM_H
