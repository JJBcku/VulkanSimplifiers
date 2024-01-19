#pragma once

namespace VulkanSimplified
{
	template<class T>
	class ListObjectID
	{
		uint64_t id;

	public:
		ListObjectID() { id = std::numeric_limits<decltype(id)>::min(); }
		ListObjectID(const ListObjectID& other) = default;
		ListObjectID(ListObjectID&& other) noexcept(false)
		{
			id = other.id++;

			if (id == std::numeric_limits<decltype(id)>::max() && other.id == std::numeric_limits<decltype(id)>::min())
				throw std::runtime_error("ListTemplate ID overflow error");
		}

		ListObjectID<T>& operator=(const ListObjectID<T>& other) = default;
		ListObjectID<T>& operator=(ListObjectID<T>&&) = delete;

		bool operator==(const ListObjectID<T>& other) const { return id == other.id; }
		std::strong_ordering operator<=>(const ListObjectID<T>&) const = default;
	};

	template<class T>
	class ListObjectTemplate
	{
		ListObjectID<T> _objectID;
		std::optional<T> _object;

		void ThrowOnHasValue()
		{
			if (_object.has_value())
				throw std::runtime_error("ListObject Error: Program tried to replace existing value");
		}

	public:

		ListObjectTemplate(ListObjectID<T>&& objectID, const T& object) : _objectID(std::move(objectID)), _object(object)
		{
		}

		ListObjectTemplate(ListObjectID<T>&& objectID, T&& object) : _objectID(std::move(objectID)), _object(std::move(object))
		{
		}

		ListObjectTemplate(const ListObjectTemplate<T>&) = default;
		ListObjectTemplate(ListObjectTemplate<T>&& other)
		{
			_objectID = other._objectID;
			_object = other._object;
		}

		ListObjectTemplate<T>& operator=(const ListObjectTemplate<T>&) = default;
		ListObjectTemplate<T>& operator=(ListObjectTemplate<T>&& other)
		{
			_objectID = other._objectID;
			_object = other._object;
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

		const ListObjectID<T> GetObjectID() { return _objectID; }

		std::optional<T>& GetObject() { return _object; }
		const std::optional<T>& GetConstObject() { return _object; }
		std::optional<T> GetObjectCopy() { return _object; }

		bool HasValue() { return _object.has_value(); }

		void DeleteObject() { _object.reset(); }

		bool operator==(bool has_value) const { return _object.has_value() == has_value; }
		bool operator==(const ListObjectID<T>& ID) const { return ID == _objectID; }
	};

	template <class T>
	class ListTemplate
	{
		ListObjectID<T> _nextID;
		std::vector<ListObjectTemplate<T>> _list;
		std::vector<size_t> _deletedList;

	public:

		ListTemplate(size_t reserve = 0) : _nextID()
		{
			_list.reserve(reserve);
			_deletedList.reserve(reserve);
		}

		ListTemplate(const ListTemplate<T>&) = delete;
		ListTemplate(ListTemplate<T>&&) = delete;

		ListTemplate<T>& operator=(const ListTemplate<T>&) = delete;
		ListTemplate<T>& operator=(ListTemplate<T>&&) = delete;

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

		const ListObjectID<T> AddObject(const T& value, size_t add = 0)
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

				_list.emplace_back(std::move(_nextID), value);
				return _list.back().GetObjectID();
			}
		}

		const ListObjectID<T> AddObject(T&& value, size_t add = 0)
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

				_list.emplace_back(std::move(_nextID), std::move(value));
				return _list.back().GetObjectID();
			}
		}

		bool RemoveObject(ListObjectID<T> objectID, bool throwOnIDNotFound = true)
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

		std::optional<T>& GetObject(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObject();
		}

		const std::optional<T>& GetConstObject(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetConstObject Error: Program tried to get non-existent object!");

			return it->GetConstObject();
		}

		std::optional<T> GetObjectCopy(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObjectCopy Error: Program tried to get non-existent object!");

			return it->GetObjectCopy();
		}

		size_t GetSize() const { return _list.size(); }
		size_t GetUsedSize() const { assert(_list.size() - _deletedList.size() <= _list.size()); return _list.size() - _deletedList.size(); }
		size_t GetCapacity() const { return _list.capacity(); }
		size_t GetUnusedCapacity() const { assert( _list.capacity() - _list.size() <= _list.capacity()); return _list.capacity() - _list.size(); }
		size_t GetUnusedAndDeletedCapacity() const { assert( GetUnusedCapacity() + _deletedList.size() >= _deletedList.size()); return GetUnusedCapacity() + _deletedList.size(); }
	};
}