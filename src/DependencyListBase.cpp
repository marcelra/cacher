#include "DependencyListBase.h"

#include "Parameter.h"
#include "IIdentifiable.h"

#include <cassert>



DependencyListBase::DependencyListBase() :
   m_name()
{}

DependencyListBase& DependencyListBase::addDependency(const IComparable& dependency)
{
   m_dependencies.push_back(&dependency);
}

bool DependencyListBase::operator==(const IComparable& other) const
{
   const DependencyListBase& cmp = dynamic_cast<const DependencyListBase&>(other);
   if (!&cmp)
   {
      return false;
   }

   if (m_dependencies.size() != cmp.m_dependencies.size()) {
      return false;
   }

   for (size_t iDep = 0; iDep < m_dependencies.size(); ++iDep)
   {
      if (m_dependencies[iDep] != cmp.m_dependencies[iDep])
      {
         return false;
      }
   }

   return true;
}

void DependencyListBase::setName(const std::string& name)
{
   m_name = name;
}


BinaryBlob DependencyListBase::toBinaryBlob() const
{
   assert(false);
//    BinaryBlob blob(0);
//
//    for (size_t iDep = 0; iDep < m_dependencies.size(); ++iDep)
//    {
//       const IComparable* dep = m_dependencies[iDep];
//       DependencyType typeCode = undefined;
//       if (dynamic_cast<const Parameter<double>*>(dep))
//       {
//          typeCode = parDouble;
//       }
//       else if (dynamic_cast<const Parameter<int>*>(dep))
//       {
//          typeCode = parInt;
//       }
//       else if (dynamic_cast<const Parameter<std::string>*>(dep))
//       {
//          typeCode = parString;
//       }
//       else if (dynamic_cast<const IIdentifiable*>(dep))
//       {
//          typeCode = identifiable;
//       }
//       assert(typeCode != undefined);
//
//       char typeCodeByte = typeCode;
//       blob.append(&typeCodeByte, 1);
//
//       const IBinarySerializable* serializable = dynamic_cast<const IBinarySerializable*>(dep);
//       assert(serializable);
//
//       BinaryBlob&& depBlob = serializable->toBinaryBlob();
//       blob.append(depBlob);
//    }
//
//    return blob;
}


void DependencyListBase::fromBinaryBlob(BinaryBlob& blob)
{
   assert(false);
}
