#ifndef DEPENDENCYLISTBASE_H
#define DEPENDENCYLISTBASE_H

#include "IBinarySerializable.h"
#include "IComparable.h"

#include <vector>
#include <string>

class IAlgorithm;


class DependencyListBase : public IBinarySerializable, public IComparable
{
   public:
      enum DependencyType
      {
         undefined,
         parDouble,
         parInt,
         parString,
         identifiable
      };

   public:
      DependencyListBase();
      virtual ~DependencyListBase() {}

   public:
      void setName(const std::string& name);

   public:
      bool operator==(const IComparable& other) const;

   public:
      BinaryBlob toBinaryBlob() const;
      void fromBinaryBlob(BinaryBlob& blob);

   public:
      DependencyListBase& addDependency(const IComparable& dependency);

   private:
      std::string                      m_name;
      std::vector<const IComparable*>  m_dependencies;

};

#endif // DEPENDENCYLISTBASE_H
