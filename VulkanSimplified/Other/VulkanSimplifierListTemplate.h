#pragma once

#include "../Include/Common/ListObjectID.h"
#include "ListObjectTemplate.h"

namespace VulkanSimplified
{
	constexpr size_t listTemplateDefaultReserve = 0x10;

	template <class T>
	class ListTemplate
	{
	protected:
		IDType _nextID;
		IDType _vectorID;
		std::vector<ListObjectTemplate<T>> _list;
		std::vector<size_t> _deletedList;

		IDType GetNextId()
		{
			IDType ret = _nextID;
			if (_nextID == std::numeric_limits<IDType>::max())
				throw std::runtime_error("ListTemplate Error: Id system overflowed!");

			_nextID++;
			return ret;
		}

	public:
		ListTemplate(size_t reserve = 0)
		{
			_nextID = std::numeric_limits<IDType>::lowest();
			_vectorID = std::numeric_limits<IDType>::lowest();

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

		ListTemplate(const ListTemplate<T>&) noexcept = delete;
		ListTemplate(ListTemplate<T>&&) noexcept = default;

		ListTemplate<T>& operator=(const ListTemplate<T>&) noexcept = delete;
		ListTemplate<T>& operator=(ListTemplate<T>&&) noexcept = default;

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

		ListObjectID<T> AddUniqueObject(const T& value, size_t add = 0)
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
					_list[pos].ReplaceValue(ListObjectID<T>(GetNextId(), _vectorID), value);
					_deletedList.pop_back();
					return _list[pos].GetObjectID();
				}
				else
				{
					CheckCapacity(add);

					_list.emplace_back(ListObjectID<T>(GetNextId(), _vectorID), value);
					return _list.back().GetObjectID();
				}
			}
		}

		ListObjectID<T> AddUniqueObject(T&& value, size_t add = 0)
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
					_list[pos].ReplaceValue(ListObjectID<T>(GetNextId(), _vectorID), std::move(value));
					_deletedList.pop_back();
					return _list[pos].GetObjectID();
				}
				else
				{
					CheckCapacity(add);

					_list.emplace_back(ListObjectID<T>(GetNextId(), _vectorID), std::move(value));
					return _list.back().GetObjectID();
				}
			}
		}

		ListObjectID<T> AddObject(const T& value, size_t add = 0)
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(ListObjectID<T>(GetNextId(), _vectorID), value);
				_deletedList.pop_back();
				return _list[pos].GetObjectID();
			}
			else
			{
				CheckCapacity(add);

				_list.emplace_back(ListObjectID<T>(GetNextId(), _vectorID), value);
				return _list.back().GetObjectID();
			}
		}

		ListObjectID<T> AddObject(T&& value, size_t add = 0)
		{
			if (!_deletedList.empty())
			{
				size_t pos = _deletedList.back();
				_list[pos].ReplaceValue(ListObjectID<T>(GetNextId(), _vectorID), std::move(value));
				_deletedList.pop_back();
				return _list[pos].GetObjectID();
			}
			else
			{
				CheckCapacity(add);

				_list.emplace_back(ListObjectID<T>(GetNextId(), _vectorID), std::move(value));
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
			if (_deletedList.empty())
				return;

			std::vector<ListObjectTemplate<T>> tempList;

			if (addToReserved)
			{
				size_t fullres = GetUsedSize() + reserve;

				if (fullres < reserve)
					throw std::runtime_error("ListTemplate ShrinkToFit Error: reservation amount overflowed!");

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

			_list = std::move(tempList);
			_deletedList.clear();
			_deletedList.shrink_to_fit();
			_deletedList.reserve(_list.capacity());
		}

		std::optional<T>& GetObjectOptional(ListObjectID<T> objectID)
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObjectOptional();
		}

		const std::optional<T>& GetConstObjectOptional(ListObjectID<T> objectID) const
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetConstObject Error: Program tried to get non-existent object!");

			return it->GetConstObjectOptional();
		}

		std::optional<T> GetObjectOptionalCopy(ListObjectID<T> objectID) const
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

		T GetObjectCopy(ListObjectID<T> objectID) const
		{
			auto it = std::find(_list.begin(), _list.end(), objectID);

			if (it == _list.end())
				throw std::runtime_error("ListTemplate GetObject Error: Program tried to get non-existent object!");

			return it->GetObjectCopy();
		}

		std::vector<T> GetObjectListCopy(const std::vector<ListObjectID<T>>& objectsIDList) const
		{
			std::vector<T> ret;

			ret.resize(objectsIDList.size());

			size_t filledlist = 0;

			for (auto& object : _list)
			{
				for (size_t i = 0; i < objectsIDList.size(); ++i)
				{
					if (objectsIDList[i] == object)
					{
						ret[i] = object.GetObjectCopy();
						filledlist++;

						if (filledlist == ret.size())
							break;
					}
				}
			}

			return ret;
		}

		size_t GetSize() const { return _list.size(); }
		size_t GetUsedSize() const
		{
			size_t ret = _list.size() - _deletedList.size();

			if (ret > _list.size())
				throw std::runtime_error("ListTemplate GetUsedSize Error: returned value underflowed!");

			return ret;
		}

		size_t GetCapacity() const { return _list.capacity(); }
		size_t GetUnusedCapacity() const
		{
			size_t ret = _list.capacity() - _list.size();

			if (ret > _list.capacity())
				throw std::runtime_error("ListTemplate GetUnusedCapacity Error: returned value underflowed!");

			return ret;
		}

		size_t GetUnusedAndDeletedCapacity() const
		{
			size_t ret = GetUnusedCapacity() + _deletedList.size();

			if (ret < _deletedList.size())
				throw std::runtime_error("ListTemplate GetUnusedAndDeletedCapacity Error: returned value overflowed!");

			return ret;
		}

		void Reset(size_t reserve = 0)
		{
			_list.clear();
			_deletedList.clear();

			if (_vectorID == std::numeric_limits<IDType>::max())
				throw std::runtime_error("ListTemplate Reset Error: vector ID overflow!");

			_vectorID++;

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