#pragma once

namespace VulkanSimplified
{
	using IDType = uint64_t;

	template<class T>
	class ListObjectID
	{
		IDType _id;

	public:
		ListObjectID(IDType id) { _id = id; }
		ListObjectID(const ListObjectID& other) = default;
		ListObjectID(ListObjectID&& other) noexcept = default;

		ListObjectID<T>& operator=(const ListObjectID<T>& other) = default;
		ListObjectID<T>& operator=(ListObjectID<T>&&) = default;

		bool operator==(const ListObjectID<T>& other) const = default;
		std::strong_ordering operator<=>(const ListObjectID<T>&) const = default;
	};

	template<class T>
	class ListObjectTemplate
	{
		ListObjectID<T> _objectID;
		std::optional<T> _object;
		char _padding[16 - (sizeof(_object) % 8)];

		void ThrowOnHasValue()
		{
			if (_object.has_value())
				throw std::runtime_error("ListObject Error: Program tried to replace existing value");
		}

	public:

		ListObjectTemplate(const ListObjectID<T>& objectID, const T& object) noexcept : _objectID(objectID), _object(object)
		{
			memset(_padding, 0, sizeof(_padding));
		}

		ListObjectTemplate(const ListObjectID<T>& objectID, T&& object) noexcept : _objectID(objectID), _object(std::move(object))
		{
			memset(_padding, 0, sizeof(_padding));
		}

		ListObjectTemplate(const ListObjectTemplate<T>& other) noexcept : _objectID(other._objectID), _object(other._object)
		{
			memset(_padding, 0, sizeof(_padding));
		}

		ListObjectTemplate(ListObjectTemplate<T>&& other) noexcept : _objectID(std::move(other._objectID)), _object(std::move(other._object))
		{
			memset(_padding, 0, sizeof(_padding));
		}

		ListObjectTemplate<T>& operator=(const ListObjectTemplate<T>& other)
		{
			_objectID = other._objectID;
			_object = other._object;
		}

		ListObjectTemplate<T>& operator=(ListObjectTemplate<T>&& other)
		{
			_objectID = std::move(other._objectID);
			_object = std::move(other._object);
		}

		void ReplaceValue(const ListObjectID<T>& objectID, const T& object)
		{
			ThrowOnHasValue();

			_object = object;
			_objectID = objectID;
		}

		void ReplaceValue(const ListObjectID<T>& objectID, T&& object)
		{
			ThrowOnHasValue();

			_object = std::move(object);
			_objectID = objectID;
		}

		ListObjectID<T> GetObjectID() const { return _objectID; }

		std::optional<T>& GetObjectOptional() { return _object; }
		const std::optional<T>& GetConstObjectOptional() const { return _object; }
		std::optional<T> GetObjectOptionalCopy() { return _object; }

		T& GetObject() { assert(_object.has_value()); return _object.value(); }
		const T& GetConstObject() const { assert(_object.has_value()); return _object.value(); }
		T GetObjectCopy() { assert(_object.has_value()); return _object.value(); }

		bool HasValue() { return _object.has_value(); }

		void DeleteObject() { _object.reset(); }

		bool operator==(bool has_value) const { return _object.has_value() == has_value; }
		bool operator==(const ListObjectID<T>& ID) const { return ID == _objectID; }

		std::strong_ordering operator<=>(const ListObjectTemplate<T>&) const noexcept = default;
		bool operator==(const ListObjectTemplate<T>&) const noexcept = default;

		bool operator==(const T& other) const noexcept
		{
			if (!_object.has_value())
			{
				return false;
			}
			else
			{
				return _object.value() == other;
			}
		}

		bool operator==(const std::optional<T>& other) const noexcept
		{
			return _object == other;
		}
	};

	constexpr size_t listTemplateDefaultReserve = 0x10;

	template <class T>
	class ListTemplate
	{
		IDType _nextID, _lastID;
		std::vector<ListObjectTemplate<T>> _list;
		std::vector<size_t> _deletedList;

		IDType GetNextId()
		{
			if (_nextID == std::numeric_limits<IDType>::lowest() && _lastID != _nextID)
				throw std::runtime_error("ListTemplate Error: Id system overflowed!");

			_lastID = _nextID;
			_nextID++;
			return _lastID;
		}

	public:

		ListTemplate(size_t reserve = 0)
		{
			_nextID = std::numeric_limits<IDType>::lowest();
			_lastID = _nextID;

			if (reserve != 0)
			{
				_list.reserve(reserve);
				_deletedList.reserve(reserve);
			}
			else
			{
				_list.reserve(listTemplateDefaultReserve);
				_deletedList.reserve(listTemplateDefaultReserve);
			}
		}

		~ListTemplate()
		{
			Reset();
		}

		ListTemplate(const ListTemplate<T>&) = delete;
		ListTemplate(ListTemplate<T>&&) = default;

		ListTemplate<T>& operator=(const ListTemplate<T>&) = delete;
		ListTemplate<T>& operator=(ListTemplate<T>&&) = default;

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

		const ListObjectID<T> AddUniqueObject(const T& value, size_t add = 0)
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
					_list[pos].ReplaceValue(GetNextId(), value);
					_deletedList.pop_back();
					return _list[pos].GetObjectID();
				}
				else
				{
					CheckCapacity(add);

					_list.emplace_back(GetNextId(), value);
					return _list.back().GetObjectID();
				}
			}
		}

		const ListObjectID<T> AddUniqueObject(T&& value, size_t add = 0)
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
					_list[pos].ReplaceValue(GetNextId(), std::move(value));
					_deletedList.pop_back();
					return _list[pos].GetObjectID();
				}
				else
				{
					CheckCapacity(add);

					_list.emplace_back(GetNextId(), std::move(value));
					return _list.back().GetObjectID();
				}
			}
		}

		const ListObjectID<T> AddObject(const T& value, size_t add = 0)
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(GetNextId(), value);
				_deletedList.pop_back();
				return _list[pos].GetObjectID();
			}
			else
			{
				CheckCapacity(add);

				_list.emplace_back(GetNextId(), value);
				return _list.back().GetObjectID();
			}
		}

		const ListObjectID<T> AddObject(T&& value, size_t add = 0)
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(GetNextId(), std::move(value));
				_deletedList.pop_back();
				return _list[pos].GetObjectID();
			}
			else
			{
				CheckCapacity(add);

				_list.emplace_back(GetNextId(), std::move(value));
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

		std::optional<T>& GetObjectOptional(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObjectOptional();
		}

		const std::optional<T>& GetConstObjectOptional(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetConstObject Error: Program tried to get non-existent object!");

			return it->GetConstObjectOptional();
		}

		std::optional<T> GetObjectOptionalCopy(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObjectCopy Error: Program tried to get non-existent object!");

			return it->GetObjectOptionalCopy();
		}

		T& GetObject(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObject();
		}

		const T& GetConstObject(ListObjectID<T> objectID) const
		{
			auto it = std::find(_list.cbegin(), _list.cend(), objectID);

			if (it == _list.cend())
				throw std::runtime_error("ListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetConstObject();
		}

		T GetObjectCopy(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObjectCopy();
		}

		size_t GetSize() const { return _list.size(); }
		size_t GetUsedSize() const { assert(_list.size() - _deletedList.size() <= _list.size()); return _list.size() - _deletedList.size(); }
		size_t GetCapacity() const { return _list.capacity(); }
		size_t GetUnusedCapacity() const { assert( _list.capacity() - _list.size() <= _list.capacity()); return _list.capacity() - _list.size(); }
		size_t GetUnusedAndDeletedCapacity() const { assert( GetUnusedCapacity() + _deletedList.size() >= _deletedList.size()); return GetUnusedCapacity() + _deletedList.size(); }

		void Reset(size_t reserve = 0)
		{
			_list.clear();
			_deletedList.clear();

			if (reserve != 0)
			{
				_list.reserve(reserve);
				_deletedList.reserve(reserve);
			}
			else
			{
				_list.reserve(listTemplateDefaultReserve);
				_deletedList.reserve(listTemplateDefaultReserve);
			}
		}
	};
}