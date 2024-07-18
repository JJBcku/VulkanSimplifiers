export module ListTemplates.IterativeUnsortedList;

export import ListTemplates.UnsortedList;
import ListTemplates.Common.Object;
import ListTemplates.IDObject;
import std;

export template<class T>
class IterativeUnsortedList : public UnsortedList<T>
{
public:
	IterativeUnsortedList(size_t reserve) : UnsortedList<T>(reserve) {}

	std::optional<T>& GetObjectOptional(size_t index)
	{
		if (index >= UnsortedList<T>::_list.size())
			throw std::runtime_error("IterativeUnsortedList::GetObjectOptional Error: Program tried to read data from outside of the list!");

		return UnsortedList<T>::_list[index].GetObjectOptional();
	}

	const std::optional<T>& GetConstObjectOptional(size_t index) const
	{
		if (index >= UnsortedList<T>::_list.size())
			throw std::runtime_error("IterativeUnsortedList::GetObjectOptional Error: Program tried to read data from outside of the list!");

		return UnsortedList<T>::_list[index].GetConstObjectOptional();
	}

	std::optional<T> GetObjectOptionalCopy(size_t index) const
	{
		if (index >= UnsortedList<T>::_list.size())
			throw std::runtime_error("IterativeUnsortedList::GetObjectOptional Error: Program tried to read data from outside of the list!");

		return UnsortedList<T>::_list[index].GetObjectOptionalCopy();
	}

	T& GetObject(size_t index)
	{
		if (index >= UnsortedList<T>::_list.size())
			throw std::runtime_error("IterativeUnsortedList::GetObject Error: Program tried to read data from outside of the list!");

		return UnsortedList<T>::_list[index].GetObject();
	}

	const T& GetConstObject(size_t index) const
	{
		if (index >= UnsortedList<T>::_list.size())
			throw std::runtime_error("IterativeUnsortedList::GetConstObject Error: Program tried to read data from outside of the list!");

		return UnsortedList<T>::_list[index].GetConstObject();
	}

	T GetObjectCopy(size_t index) const
	{
		if (index >= UnsortedList<T>::_list.size())
			throw std::runtime_error("IterativeUnsortedList::GetObjectCopy Error: Program tried to read data from outside of the list!");

		return UnsortedList<T>::_list[index].GetObjectCopy();
	}

protected:

};