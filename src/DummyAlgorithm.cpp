#include "DummyAlgorithm.h"

#include "Parameter.h"


DummyAlgorithm::DependencyList::DependencyList(double x, int y)
{
   addDependency(Parameter<double>(x));
   addDependency(Parameter<int>(y));
}


DummyAlgorithm::DummyAlgorithm(const std::string& name, const DependencyList& dependencies) :
   m_name(name),
   m_dependencyList(dependencies)
{
   m_dependencyList.setName(name);
}



DummyAlgorithm::~DummyAlgorithm()
{}



const std::string DummyAlgorithm::getName() const
{
   return m_name;
}
