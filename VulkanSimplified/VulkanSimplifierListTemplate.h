#pragma once

namespace VulkanSimplified
{
	using IDType = uint64_t;

	template<class T>
	class ListObjectTemplate
	{
		IDType _objectID;
		std::optional<T> _object;

		void ThrowOnHasValue()
		{
			if (_object.has_value())
				throw std::runtime_error("ListObject Error: Program tried to replace existing value");
		}

	public:

		ListObjectTemplate(IDType objectID, const T& object)
		{
			_objectID = objectID;
			_object = object;
		}

		ListObjectTemplate(IDType objectID, T&& object)
		{
			_objectID = objectID;
			_object = std::move(object);
		}

		void ReplaceValue(const T& object)
		{
			ThrowOnHasValue();

			_object = object;
		}

		void ReplaceValue(T&& object)
		{
			ThrowOnHasValue();

			_object = std::move(object);
		}

		IDType GetObjectID() { return _objectID; }

		std::optional<T>& GetObject() { return _object; }
		const std::optional<T>& GetConstObject() { return _object; }
		std::optional<T> GetObjectCopy() { return _object; }

		bool HasValue() { return _object.has_value(); }

		void DeleteObject() { _object.reset(); }

		bool operator==(bool has_value) { return _object.has_value() == has_value; }
		bool operator==(IDType ID) { return ID == _objectID; }
	};

	template <class T>
	class ListTemplate
	{
		IDType _lastID;
		IDType _nextID;
		std::vector<ListObjectTemplate<T>> _list;
		std::vector<size_t> _deletedList;

		uint64_t GetAndIncrementID()
		{
			_lastID = _nextID;
			_nextID++;

			if (_nextID == std::numeric_limits<IDType>::min() && _lastID == std::numeric_limits<IDType>::max())
				throw std::runtime_error("ListTemplate ID overflow error");
		}

	public:

		ListTemplate(size_t reserve = 0)
		{
			_lastID = 0;
			_nextID = 0;
			_list.reserve(reserve);
			_deletedList.reserve(reserve);
		}

		void ReserveAdditional(size_t add)
		{
			_list.reserve(_list.capacity() + add);
			_deletedList.reserve(_list.capacity() + add);
		}

		void CheckCapacity(size_t add = 0)
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

		IDType AddObject(const T& value, size_t add = 0)
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(value);
				_deletedList.pop_back();
				return _list[pos].GetObjectID();
			}
			else
			{
				CheckCapacity(add);

				_list.emplace_back(GetAndIncrementID(), value);
				return _list.back().GetObjectID();
			}
		}

		IDType AddObject(T&& value, size_t add = 0)
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(std::move(value));
				_deletedList.pop_back();
				return _list[pos].GetObjectID();
			}
			else
			{
				CheckCapacity(add);

				_list.emplace_back(GetAndIncrementID(), std::move(value));
				return _list.back().GetObjectID();
			}
		}

		bool RemoveObject(IDType objectID, bool throwOnIDNotFound = true)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
			{
				if (throwOnIDNotFound)
					throw std::runtime_error("ListTemplate: Program tried to delete a non-existent entry in a list!");
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
				return true;
			}
		}

		void ShrinkToFit(size_t reserve = 0, bool addToReserved = true)
		{
			auto it = std::find(_list.begin(), _list.end(), false);

			if (it == _list.end())
				return;

			std::vector<ListObjectTemplate<T>> tempList;

			if (addToReserved)
			{
				tempList.reserve(_list.size() + reserve);
			}
			else
			{
				if (reserve > _list.size())
				{
					tempList.reserve(reserve);
				}
				else
				{
					tempList.reserve(_list.size());
				}
			}

			for (auto& object : _list)
			{
				if (object.HasValue())
				{
					if constexpr (std::is_move_constructible<ListObjectTemplate<T>>::value)
					{
						tempList.push_back(std::move(object));
					}
					else
					{
						tempList.push_back(object);
					}
				}
			}

			_list = std::move(tempList);
			_deletedList.clear();
		}

		std::optional<T>& GetObject(IDType objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObject();
		}

		const std::optional<T>& GetConstObject(IDType objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetConstObject Error: Program tried to get non-existent object!");

			return it->GetConstObject();
		}

		std::optional<T> GetObjectCopy(IDType objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObjectCopy Error: Program tried to get non-existent object!");

			return it->GetObjectCopy();
		}
	};
}