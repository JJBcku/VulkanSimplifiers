export module ListTemplates.OrderIndependentDeletionStack;

import std;
export import ListTemplates.IDObject;
import ListTemplates.Common.Object;

constexpr size_t listTemplateDefaultReserve = 0x10;

export template<class T>
class OrderIndependentDeletionStack
{
public:
	OrderIndependentDeletionStack(size_t reserve)
	{
		_nextID = std::numeric_limits<IDType>::lowest();
		_vectorID = std::numeric_limits<IDType>::lowest();

		if (reserve != 0)
		{
			_list.reserve(reserve);
			_deletedList.reserve(reserve);
			_additionOrder.reserve(reserve);
		}
		else
		{
			_list.reserve(listTemplateDefaultReserve);
			_deletedList.reserve(listTemplateDefaultReserve);
			_additionOrder.reserve(listTemplateDefaultReserve);
		}
	}

	~OrderIndependentDeletionStack()
	{

	}

	OrderIndependentDeletionStack(const OrderIndependentDeletionStack&) noexcept = delete;
	OrderIndependentDeletionStack(OrderIndependentDeletionStack&&) noexcept = default;

	OrderIndependentDeletionStack& operator=(const OrderIndependentDeletionStack&) noexcept = delete;
	OrderIndependentDeletionStack& operator=(OrderIndependentDeletionStack&&) noexcept = default;

	IDObject<T> AddUniqueObject(const T& value, size_t add)
	{
		auto found = std::find(_list.cbegin(), _list.cend(), value);

		if (found != _list.cend())
		{
			return found->GetObjectID();
		}
		else
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(IDObject<T>(GetNextId(), _vectorID), value);
				_deletedList.pop_back();
				auto ID = _list[pos].GetObjectID();
				_additionOrder.push_back(ID);
				return ID;
			}
			else
			{
				CheckCapacity(add);

				_list.emplace_back(IDObject<T>(GetNextId(), _vectorID), value);
				auto ID = _list.back().GetObjectID();
				_additionOrder.push_back(ID);
				return ID;
			}
		}
	}

	IDObject<T> AddUniqueObject(T&& value, size_t add)
	{
		auto found = std::find(_list.cbegin(), _list.cend(), value);

		if (found != _list.cend())
		{
			return found->GetObjectID();
		}
		else
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(IDObject<T>(GetNextId(), _vectorID), std::move(value));
				_deletedList.pop_back();
				auto ID = _list[pos].GetObjectID();
				_additionOrder.push_back(ID);
				return ID;
			}
			else
			{
				CheckCapacity(add);

				_list.emplace_back(IDObject<T>(GetNextId(), _vectorID), std::move(value));
				auto ID = _list.back().GetObjectID();
				_additionOrder.push_back(ID);
				return ID;
			}
		}
	}

	IDObject<T> AddObject(const T& value, size_t add)
	{
		if (!_deletedList.empty())
		{
			size_t pos = _deletedList.back();
			_list[pos].ReplaceValue(IDObject<T>(GetNextId(), _vectorID), value);
			_deletedList.pop_back();
			auto ID = _list[pos].GetObjectID();
			_additionOrder.push_back(ID);
			return ID;
		}
		else
		{
			CheckCapacity(add);

			_list.emplace_back(IDObject<T>(GetNextId(), _vectorID), value);
			auto ID = _list.back().GetObjectID();
			_additionOrder.push_back(ID);
			return ID;
		}
	}

	IDObject<T> AddObject(T&& value, size_t add)
	{
		if (!_deletedList.empty())
		{
			size_t pos = _deletedList.back();
			_list[pos].ReplaceValue(IDObject<T>(GetNextId(), _vectorID), std::move(value));
			_deletedList.pop_back();
			auto ID = _list[pos].GetObjectID();
			_additionOrder.push_back(ID);
			return ID;
		}
		else
		{
			CheckCapacity(add);

			_list.emplace_back(IDObject<T>(GetNextId(), _vectorID), std::move(value));
			auto ID = _list.back().GetObjectID();
			_additionOrder.push_back(ID);
			return ID;
		}
	}

	bool RemoveObject(IDObject<T> objectID, bool throwOnIDNotFound)
	{
		auto it = std::find(_list.begin(), _list.end(), objectID);

		if (it == _list.cend())
		{
			if (throwOnIDNotFound)
				throw std::runtime_error("OrderIndependentDeletionStack: Program tried to delete a non-existent entry in a list!");
			else
				return false;
		}
		else
		{
			if (it->HasValue())
			{
				it->DeleteObject();
				_deletedList.push_back(static_cast<size_t>(std::distance(_list.begin(), it)));
			}

			auto orderIt = std::find(_additionOrder.begin(), _additionOrder.end(), objectID);

			if (orderIt != _additionOrder.cend())
			{
				_additionOrder.erase(orderIt);
			}
			else if (throwOnIDNotFound)
			{
				throw std::runtime_error("OrderIndependentDeletionStack: Program tried to delete a non-existent entry in an additon order list!");
			}

			return true;
		}
	}

	size_t GetSize() const { return _list.size(); }
	size_t GetUsedSize() const { return _additionOrder.size(); }
	size_t GetCapacity() const { return _list.capacity(); }
	size_t GetUnusedCapacity() const { return GetCapacity() - GetSize(); }
	size_t GetUnusedAndDeletedCapacity() const { return GetCapacity() - GetUsedSize(); }

	void ShrinkToFit(size_t reserve, bool addToReserved)
	{
		if (_deletedList.empty())
			return;

		std::vector<ListObject<T>> tempList;

		if (addToReserved)
		{
			size_t fullres = GetUsedSize() + reserve;

			if (fullres < reserve)
				throw std::runtime_error("UnsortedList ShrinkToFit Error: reservation amount overflowed!");

			tempList.reserve(fullres);
		}
		else
		{
			if (reserve > GetUsedSize())
			{
				tempList.reserve(reserve);
			}
			else
			{
				tempList.reserve(GetUsedSize());
			}
		}

		for (auto& object : _list)
		{
			if (object.HasValue())
			{
				if constexpr (std::is_move_constructible<T>::value)
				{
					tempList.push_back(std::move(object));
				}
				else
				{
					tempList.push_back(object);
				}
			}
		}

		if (tempList.capacity() == 0)
			tempList.reserve(listTemplateDefaultReserve);

		_list = std::move(tempList);
		_deletedList.clear();
		_deletedList.shrink_to_fit();
		_deletedList.reserve(_list.capacity());

		_additionOrder.shrink_to_fit();
		_additionOrder.reserve(_list.capacity());
	}

	T& GetObject(size_t position)
	{
		if (position >= _additionOrder.size())
			throw std::runtime_error("OrderIndependentDeletionStack GetObject Error: Program tried to read data from outside the addition order list!");

		auto& ID = _additionOrder[(_additionOrder.size() - position) - 1];

		auto it = std::find(_list.begin(), _list.end(), ID);

		if (it != _list.cend())
		{
			return it->GetObject();
		}
		else
		{
			throw std::runtime_error("OrderIndependentDeletionStack GetObject Error: An ID from the addition list does not exist in the object list!");
		}
	}

	const T& GetConstObject(size_t position) const
	{
		if (position >= _additionOrder.size())
			throw std::runtime_error("OrderIndependentDeletionStack GetConstObject Error: Program tried to read data from outside the addition order list!");

		auto& ID = _additionOrder[(_additionOrder.size() - position) - 1];

		auto it = std::find(_list.begin(), _list.end(), ID);

		if (it != _list.cend())
		{
			return it->GetConstObject();
		}
		else
		{
			throw std::runtime_error("OrderIndependentDeletionStack GetConstObject Error: An ID from the addition list does not exist in the object list!");
		}
	}

	T GetObjectCopy(size_t position)
	{
		if (position >= _additionOrder.size())
			throw std::runtime_error("OrderIndependentDeletionStack GetObjectCopy Error: Program tried to read data from outside the addition order list!");

		auto& ID = _additionOrder[(_additionOrder.size() - position) - 1];

		auto it = std::find(_list.begin(), _list.end(), ID);

		if (it != _list.cend())
		{
			return it->GetObjectCopy();
		}
		else
		{
			throw std::runtime_error("OrderIndependentDeletionStack GetObjectCopy Error: An ID from the addition list does not exist in the object list!");
		}
	}

	void Reset(size_t reserve)
	{
		_list.clear();
		_deletedList.clear();
		_additionOrder.clear();

		_list.shrink_to_fit();
		_deletedList.shrink_to_fit();
		_additionOrder.shrink_to_fit();

		if (_vectorID == std::numeric_limits<IDType>::max())
			throw std::runtime_error("UnsortedList Reset Error: vector ID overflow!");

		_vectorID++;

		if (reserve != 0)
		{
			_list.reserve(reserve);
			_deletedList.reserve(reserve);
			_additionOrder.reserve(reserve);
		}
		else
		{
			_list.reserve(listTemplateDefaultReserve);
			_deletedList.reserve(listTemplateDefaultReserve);
			_additionOrder.reserve(listTemplateDefaultReserve);
		}
	}


private:
	IDType _nextID;
	IDType _vectorID;
	std::vector<ListObject<T>> _list;
	std::vector<size_t> _deletedList;
	std::vector<IDObject<T>> _additionOrder;
	char padding[16 - (sizeof(_additionOrder) % 8)];

	IDType GetNextId()
	{
		IDType ret = _nextID;
		if (_nextID == std::numeric_limits<IDType>::max())
			throw std::runtime_error("OrderIndependentDeletionStack Error: Id system overflowed!");

		_nextID++;
		return ret;
	}

	void ReserveAdditional(size_t add)
	{
		auto size = _list.capacity();

		_list.reserve(size + add);
		_deletedList.reserve(size + add);
		_additionOrder.reserve(size + add);
	}

	void CheckCapacity(size_t add)
	{
		if (_list.capacity() == _list.size())
		{
			if (add == 0)
			{
				ReserveAdditional(_list.capacity());
			}
			else
			{
				ReserveAdditional(add);
			}
		}
	}
};